#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

struct BigObject
{
    int id;
    std::string name;
    std::string address;
    std::string description;
};

// 2) Growable contiguous store (no std::vector)
// - returns stable handles (indices)
template <class T>
class ObjectStore
{
public:
    using Handle = std::size_t;
    explicit ObjectStore(std::size_t initial_cap = 16)
    {
        if (initial_cap < 1)
            initial_cap = 1;
        cap_ = initial_cap;
        data_ = new T[cap_];
    }
    ~ObjectStore() { delete[] data_; }
    ObjectStore(const ObjectStore &) = delete;
    ObjectStore &operator=(const ObjectStore &) = delete;
    ObjectStore(ObjectStore &&other) noexcept : data_(other.data_), size_(other.size_), cap_(other.cap_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.cap_ = 0;
    }
    ObjectStore &operator=(ObjectStore &&other) noexcept
    {
        if (this == &other)
            return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        cap_ = other.cap_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.cap_ = 0;
        return *this;
    }
    template <class... Args>
    Handle emplace(Args &&...args)
    {
        if (size_ == cap_)
            grow();
        data_[size_] = T{std::forward<Args>(args)...};
        return size_++;
    }
    T &get(Handle h)
    {
        if (h >= size_)
            throw std::out_of_range("ObjectStore handle out of range");
        return data_[h];
    }
    const T &get(Handle h) const
    {
        if (h >= size_)
            throw std::out_of_range("ObjectStore handle out of range");
        return data_[h];
    }
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return cap_; }

private:
    T *data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t cap_ = 0;
    void grow()
    {
        std::size_t new_cap = cap_ * 2;
        T *new_data = new T[new_cap];
        // Move/copy elements
        for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        cap_ = new_cap;
    }
};
// ======================================================
// 3) Hash table storing key -> Handle (index into store)
// Open addressing + linear probing + tombstones
// No std::vector, uses raw dynamic array with RAII.
// ======================================================
template <class K, class Handle, class Hash = std::hash<K>, class KeyEqual = std::equal_to<K>>
class HashIndex
{
public:
    explicit HashIndex(std::size_t initial_capacity = 16, float max_load = 0.70f) : max_load_(max_load)
    {
        if (max_load_ <= 0.0f || max_load_ >= 0.95f)
            throw std::invalid_argument("max_load must be in (0, 0.95)");
        cap_ = roundUpPow2(initial_capacity < 8 ? 8 : initial_capacity);
        table_ = new Slot[cap_];
    }
    ~HashIndex() { delete[] table_; }
    HashIndex(const HashIndex &) = delete;
    HashIndex &operator=(const HashIndex &) = delete;
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return cap_; }
    float load_factor() const noexcept { return cap_ ? static_cast<float>(size_) / static_cast<float>(cap_) : 0.0f; }
    // Insert new or update existing. Returns true if inserted new, false if updated.
    bool insert_or_assign(const K &key, Handle h)
    {
        maybeGrowOrRebuild();
        std::size_t first_tomb = npos;
        std::size_t idx = indexFor(key);
        for (std::size_t probe = 0; probe < cap_; ++probe)
        {
            Slot &s = table_[idx];
            if (s.state == State::Empty)
            {
                const std::size_t target = (first_tomb != npos) ? first_tomb : idx;
                place(target, key, h);
                return true;
            }
            if (s.state == State::Tombstone)
            {
                if (first_tomb == npos)
                    first_tomb = idx;
            }
            else if (eq_(s.key, key))
            {
                s.handle = h;
                // update
                return false;
            }
            idx = (idx + 1) & (cap_ - 1);
        }
        // Defensive: if table is too crowded (shouldn't happen),                        rehash
        bigger.rehash(cap_ * 2);
        return insert_or_assign(key, h);
    }
    // Find handle by key. Returns nullptr if not found.
    const Handle *find(const K &key) const noexcept
    {
        if (!table_)
            return nullptr;
        std::size_t idx = indexFor(key);
        for (std::size_t probe = 0; probe < cap_; ++probe)
        {
            const Slot &s = table_[idx];
            if (s.state == State::Empty)
                return nullptr;
            // stop early
            if (s.state == State::Filled && eq_(s.key, key))
                return &s.handle;
            idx = (idx + 1) & (cap_ - 1);
        }
        return nullptr;
    }
    // Erase key (tombstone). Returns true if erased.
    bool erase(const K &key) noexcept
    {
        std::size_t idx = indexFor(key);
        for (std::size_t probe = 0; probe < cap_; ++probe)
        {
            Slot &s = table_[idx];
            if (s.state == State::Empty)
                return false;
            if (s.state == State::Filled && eq_(s.key, key))
            {
                s.state = State::Tombstone;
                --size_;
                ++tombs_;
                maybeGrowOrRebuild();
                // rebuild if too many tombstones
                return true;
            }
            idx = (idx + 1) & (cap_ - 1);
        }
        return false;
    }

private:
    enum class State : std::uint8_t
    {
        Empty,
        Filled,
        Tombstone
    };
    struct Slot
    {
        State state = State::Empty;
        K key{};
        Handle handle{};
    };
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);
    Slot *table_ = nullptr;
    std::size_t cap_ = 0;
    std::size_t size_ = 0;
    std::size_t tombs_ = 0;
    float max_load_;
    Hash hasher_;
    KeyEqual eq_;
    // std::hash + mixing (helps for poor patterns, especially integer keys)
    std::size_t mixedHash(const K &key) const noexcept
    {
        std::size_t h = hasher_(key);
        std::uint64_t x = static_cast<std::uint64_t>(h);
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        x = x ^ (x >> 31);
        return static_cast<std::size_t>(x);
    }
    std::size_t indexFor(const K &key) const noexcept { return mixedHash(key) & (cap_ - 1); }
    void place(std::size_t idx, const K &key, Handle h)
    {
        Slot &s = table_[idx];
        if (s.state == State::Tombstone)
            --tombs_;
        s.key = key;
        s.handle = h;
        s.state = State::Filled;
        ++size_;
    }
    void maybeGrowOrRebuild()
    { // “Used” includes tombstones; tombstones slow probing.
        const std::size_t used = size_ + tombs_;
        const float used_lf = cap_ ? static_cast<float>(used) / cap_ : 1.0f;
        if (used_lf > max_load_)
        {
            rehash(cap_ * 2);
            // grow return; } // If too many tombstones, rebuild same size (common in real hash tables).
            if (tombs_ > size_ && tombs_ > 16)
            {
                rehash(cap_);
                // rebuild
                return;
            }
        }
        void rehash(std::size_t new_cap)
        {
            new_cap = roundUpPow2(new_cap < 8 ? 8 : new_cap);
            Slot *old = table_;
            std::size_t old_cap = cap_;
            table_ = new Slot[new_cap];
            cap_ = new_cap;
            size_ = 0;
            tombs_ = 0;
            for (std::size_t i = 0; i < old_cap; ++i)
            {
                if (old[i].state == State::Filled)
                {
                    insert_or_assign(old[i].key, old[i].handle);
                }
            }
            delete[] old;
        }
        static std::size_t roundUpPow2(std::size_t n)
        {
            std::size_t p = 1;
            while (p < n)
                p <<= 1;
            return p;
        }
    }; // ===============================
    // 4) Real-life demo: user profiles
    // key -> handle -> BigObject
    // ===============================
};
int main()
{
    ObjectStore<BigObject> store(2);
    // grows automatically
    HashIndex<int, ObjectStore<BigObject>::Handle> index(8, 0.70f);
    // grows + rehashes // Insert users (big objects stored contiguously in store)
    auto h1 = store.emplace(BigObject{101, "Mohammed", "Addis", "Software Engineer"});
    index.insert_or_assign(101, h1);
    auto h2 = store.emplace(BigObject{205, "Hassen", "Adama", "AI Researcher"});
    index.insert_or_assign(205, h2);
    auto h3 = store.emplace(BigObject{330, "Sara", "Bahir Dar", "Data Analyst"});
    index.insert_or_assign(330, h3);
    // Lookup by key (fast)
    if (const auto *h = index.find(205))
    {
        const BigObject &u = store.get(*h);
        std::cout << "Found 205: " << u.name << ", " << u.address << " - " << u.description << "\n";
    }
    else
    {
        std::cout << "205 not found\n";
    } // Delete (tombstone in hash index; object store keeps data for simplicity)
    index.erase(205);
    std::cout << "After erase, find(205) = " << (index.find(205) ? "yes" : "no") << "\n";
    std::cout << "Store size=" << store.size() << " cap=" << store.capacity() << "\n";
    std::cout << "Index size=" << index.size() << " cap=" << index.capacity() << " load=" << index.load_factor() << "\n";
    return 0;
}