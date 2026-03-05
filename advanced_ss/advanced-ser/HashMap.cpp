
// #include <iostream>
// #include <string>
// #include <cstddef>
// #include <cstdint>
// #include <functional>
// #include <optional>
// #include <stdexcept>
// #include <utility>
// #include <vector>

// template <class K, class V,
//           class Hash = std::hash<K>,
//           class KeyEqual = std::equal_to<K>>
// class HashMap {
// public:
//   HashMap(std::size_t initial_capacity = 16, float max_load_factor = 0.70f)
//       : max_load_factor_(max_load_factor) {
//     if (max_load_factor_ <= 0.0f || max_load_factor_ >= 0.95f)
//       throw std::invalid_argument("max_load_factor must be in (0, 0.95).");
//     rehash(nextPow2(std::max<std::size_t>(initial_capacity, 8)));
//   }

//   std::size_t size() const noexcept { return size_; }
//   std::size_t capacity() const noexcept { return table_.size(); }
//   float load_factor() const noexcept {
//     return table_.empty() ? 0.0f : static_cast<float>(size_) / table_.size();
//   }

//   void max_load_factor(float lf) {
//     if (lf <= 0.0f || lf >= 0.95f)
//       throw std::invalid_argument("max_load_factor must be in (0, 0.95).");
//     max_load_factor_ = lf;
//     maybeGrow();
//   }

//   // Insert or assign. Returns true if inserted new key, false if updated existing.
//   bool insert_or_assign(const K& key, const V& value) {
//     maybeGrow();

//     std::size_t first_tombstone = npos;
//     std::size_t idx = indexFor(key);

//     for (std::size_t probe = 0; probe < table_.size(); ++probe) {
//       Slot& s = table_[idx];

//       if (s.state == State::Empty) {
//         // Prefer earlier tombstone if found
//         std::size_t target = (first_tombstone != npos) ? first_tombstone : idx;
//         placeAt(target, key, value);
//         return true;
//       }

//       if (s.state == State::Tombstone) {
//         if (first_tombstone == npos) first_tombstone = idx;
//       } else if (eq_(s.key, key)) {
//         // Found existing
//         s.value = value;
//         return false;
//       }

//       idx = (idx + 1) & (table_.size() - 1);
//     }

//     // Table should never be completely full due to load-factor control,
//     // but handle defensively.
//     rehash(table_.size() * 2);
//     return insert_or_assign(key, value);
//   }

//   // Convenience: insert only (no overwrite). Returns true if inserted.
//   bool insert(const K& key, const V& value) {
//     auto found = find(key);
//     if (found) return false;
//     insert_or_assign(key, value);
//     return true;
//   }

//   // Find value pointer (mutable). nullptr if not found.
//   V* find(const K& key) noexcept {
//     if (table_.empty()) return nullptr;

//     std::size_t idx = indexFor(key);
//     for (std::size_t probe = 0; probe < table_.size(); ++probe) {
//       Slot& s = table_[idx];

//       if (s.state == State::Empty) return nullptr; // stop early
//       if (s.state == State::Filled && eq_(s.key, key)) return &s.value;

//       idx = (idx + 1) & (table_.size() - 1);
//     }
//     return nullptr;
//   }

//   // Find value pointer (const). nullptr if not found.
//   const V* find(const K& key) const noexcept {
//     return const_cast<HashMap*>(this)->find(key);
//   }

//   // Erase key. Returns true if erased.
//   bool erase(const K& key) noexcept {
//     if (table_.empty()) return false;

//     std::size_t idx = indexFor(key);
//     for (std::size_t probe = 0; probe < table_.size(); ++probe) {
//       Slot& s = table_[idx];

//       if (s.state == State::Empty) return false;
//       if (s.state == State::Filled && eq_(s.key, key)) {
//         s.state = State::Tombstone;
//         --size_;
//         ++tombstones_;
//         maybeRebuild(); // clean up tombstones if they grow too much
//         return true;
//       }
//       idx = (idx + 1) & (table_.size() - 1);
//     }
//     return false;
//   }

//   // operator[] like std::unordered_map: inserts default if missing
//   V& operator[](const K& key) {
//     if (V* p = find(key)) return *p;
//     insert_or_assign(key, V{});
//     return *find(key); // now it must exist
//   }

//   // Reserve to hold at least n elements without resizing.
//   void reserve(std::size_t n) {
//     std::size_t needed = static_cast<std::size_t>(n / max_load_factor_) + 1;
//     if (needed > table_.size()) rehash(nextPow2(needed));
//   }

// private:
//   enum class State : std::uint8_t { Empty, Filled, Tombstone };

//   struct Slot {
//     State state = State::Empty;
//     // Stored directly for simplicity; for very heavy objects you’d consider
//     // std::optional<K/V> or small-buffer tricks.
//     K key{};
//     V value{};
//   };

//   static constexpr std::size_t npos = static_cast<std::size_t>(-1);

//   std::vector<Slot> table_;
//   std::size_t size_ = 0;
//   std::size_t tombstones_ = 0;
//   float max_load_factor_;

//   Hash hasher_;
//   KeyEqual eq_;

//   // --- Hashing: std::hash + mix to reduce poor hash patterns (esp. integers) ---
//   std::size_t mixedHash(const K& key) const noexcept {
//     std::size_t h = hasher_(key);
//     // splitmix64-style mixing (works fine even on 32-bit size_t, still helps)
//     std::uint64_t x = static_cast<std::uint64_t>(h);
//     x += 0x9e3779b97f4a7c15ULL;
//     x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
//     x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
//     x = x ^ (x >> 31);
//     return static_cast<std::size_t>(x);
//   }

//   std::size_t indexFor(const K& key) const noexcept {
//     // capacity is always power of two, so we can use & mask
//     return mixedHash(key) & (table_.size() - 1);
//   }

//   void placeAt(std::size_t idx, const K& key, const V& value) {
//     Slot& s = table_[idx];
//     if (s.state == State::Tombstone) {
//       // Reusing tombstone
//       --tombstones_;
//     }
//     s.key = key;
//     s.value = value;
//     s.state = State::Filled;
//     ++size_;
//   }

//   void maybeGrow() {
//     if (table_.empty()) {
//       rehash(16);
//       return;
//     }
//     // Note: we include tombstones in "occupied-ness" pressure,
//     // because tombstones slow probing.
//     std::size_t used = size_ + tombstones_;
//     float used_lf = static_cast<float>(used) / table_.size();
//     if (used_lf > max_load_factor_) {
//       rehash(table_.size() * 2);
//     }
//   }

//   void maybeRebuild() {
//     // If too many tombstones relative to real elements, rebuild same size.
//     // This is common in real implementations.
//     if (tombstones_ > size_ && tombstones_ > 8) {
//       rehash(table_.size());
//     }
//   }

//   void rehash(std::size_t new_cap) {
//     new_cap = nextPow2(std::max<std::size_t>(new_cap, 8));

//     std::vector<Slot> old = std::move(table_);
//     table_.assign(new_cap, Slot{});
//     size_ = 0;
//     tombstones_ = 0;

//     for (auto& s : old) {
//       if (s.state == State::Filled) {
//         // reinsert into new table
//         insert_or_assign(s.key, s.value);
//       }
//     }
//   }

//   static std::size_t nextPow2(std::size_t n) {
//     // round up to power of two
//     if (n <= 1) return 1;
//     std::size_t p = 1;
//     while (p < n) p <<= 1;
//     return p;
//   }
// };

// int main() {
//   HashMap<int, std::string> users;

//   users.insert_or_assign(101, "Mohammed");
//   users.insert_or_assign(205, "Hassen");
//   users.insert_or_assign(330, "Addis");

//   if (auto* name = users.find(205)) {
//     std::cout << "205 -> " << *name << "\n";
//   }

//   users.erase(205);

//   std::cout << "size=" << users.size()
//             << " cap=" << users.capacity()
//             << " load=" << users.load_factor() << "\n";
// }

#include <iostream>
#include <string>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std; //  this removes almost all std::

template <class K, class V, class Hash = hash<K>, class KeyEqual = equal_to<K>>
class HashMap
{
public:
    HashMap(size_t initial_capacity = 16, float max_load_factor = 0.70f)
        : max_load_factor_(max_load_factor)
    {
        if (max_load_factor_ <= 0.0f || max_load_factor_ >= 0.95f)
            throw invalid_argument("max_load_factor must be in (0, 0.95).");
        rehash(nextPow2(max<size_t>(initial_capacity, 8)));
    }

    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return table_.size(); }
    float load_factor() const noexcept
    {
        return table_.empty() ? 0.0f : static_cast<float>(size_) / table_.size();
    }

    void max_load_factor(float lf)
    {
        if (lf <= 0.0f || lf >= 0.95f)
            throw invalid_argument("max_load_factor must be in (0, 0.95).");
        max_load_factor_ = lf;
        maybeGrow();
    }

    // Insert or assign. Returns true if inserted new key, false if updated existing.
    bool insert_or_assign(const K &key, const V &value)
    {
        maybeGrow();

        size_t first_tombstone = npos;
        size_t idx = indexFor(key);

        for (size_t probe = 0; probe < table_.size(); ++probe)
        {
            Slot &s = table_[idx];

            if (s.state == State::Empty)
            {
                // Prefer earlier tombstone if found
                size_t target = (first_tombstone != npos) ? first_tombstone : idx;
                placeAt(target, key, value);
                return true;
            }

            if (s.state == State::Tombstone)
            {
                if (first_tombstone == npos)
                    first_tombstone = idx;
            }
            else if (eq_(s.key, key))
            {
                // Found existing
                s.value = value;
                return false;
            }

            idx = (idx + 1) & (table_.size() - 1);
        }

        // Table should never be completely full due to load-factor control,
        // but handle defensively.
        rehash(table_.size() * 2);
        return insert_or_assign(key, value);
    }

    // Convenience: insert only (no overwrite). Returns true if inserted.
    bool insert(const K &key, const V &value)
    {
        auto found = find(key);
        if (found)
            return false;
        insert_or_assign(key, value);
        return true;
    }

    // Find value pointer (mutable). nullptr if not found.
    V *find(const K &key) noexcept
    {
        if (table_.empty())
            return nullptr;

        size_t idx = indexFor(key);
        for (size_t probe = 0; probe < table_.size(); ++probe)
        {
            Slot &s = table_[idx];

            if (s.state == State::Empty)
                return nullptr; // stop early
            if (s.state == State::Filled && eq_(s.key, key))
                return &s.value;

            idx = (idx + 1) & (table_.size() - 1);
        }
        return nullptr;
    }

    // Find value pointer (const). nullptr if not found.
    const V *find(const K &key) const noexcept
    {
        return const_cast<HashMap *>(this)->find(key);
    }

    // Erase key. Returns true if erased.
    bool erase(const K &key) noexcept
    {
        if (table_.empty())
            return false;

        size_t idx = indexFor(key);
        for (size_t probe = 0; probe < table_.size(); ++probe)
        {
            Slot &s = table_[idx];

            if (s.state == State::Empty)
                return false;
            if (s.state == State::Filled && eq_(s.key, key))
            {
                s.state = State::Tombstone;
                --size_;
                ++tombstones_;
                maybeRebuild(); // clean up tombstones if they grow too much
                return true;
            }
            idx = (idx + 1) & (table_.size() - 1);
        }
        return false;
    }

    // operator[] like std::unordered_map: inserts default if missing
    V &operator[](const K &key)
    {
        if (V *p = find(key))
            return *p;
        insert_or_assign(key, V{});
        return *find(key); // now it must exist
    }

    // Reserve to hold at least n elements without resizing.
    void reserve(size_t n)
    {
        size_t needed = static_cast<size_t>(n / max_load_factor_) + 1;
        if (needed > table_.size())
            rehash(nextPow2(needed));
    }

private:
    enum class State : uint8_t
    {
        Empty,
        Filled,
        Tombstone
    };

    struct Slot
    {
        State state = State::Empty;
        K key{};
        V value{};
    };

    static constexpr size_t npos = static_cast<size_t>(-1);

    vector<Slot> table_;
    size_t size_ = 0;
    size_t tombstones_ = 0;
    float max_load_factor_;

    Hash hasher_;
    KeyEqual eq_;

    // --- Hashing: std::hash + mix to reduce poor hash patterns (esp. integers) ---
    size_t mixedHash(const K &key) const noexcept
    {
        size_t h = hasher_(key);
        // splitmix64-style mixing (works fine even on 32-bit size_t, still helps)
        uint64_t x = static_cast<uint64_t>(h);
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        x = x ^ (x >> 31);
        return static_cast<size_t>(x);
    }

    size_t indexFor(const K &key) const noexcept
    {
        // capacity is always power of two, so we can use & mask
        return mixedHash(key) & (table_.size() - 1);
    }

    void placeAt(size_t idx, const K &key, const V &value)
    {
        Slot &s = table_[idx];
        if (s.state == State::Tombstone)
        {
            // Reusing tombstone
            --tombstones_;
        }
        s.key = key;
        s.value = value;
        s.state = State::Filled;
        ++size_;
    }

    void maybeGrow()
    {
        if (table_.empty())
        {
            rehash(16);
            return;
        }
        // Note: we include tombstones in "occupied-ness" pressure,
        // because tombstones slow probing.
        size_t used = size_ + tombstones_;
        float used_lf = static_cast<float>(used) / table_.size();
        if (used_lf > max_load_factor_)
        {
            rehash(table_.size() * 2);
        }
    }

    void maybeRebuild()
    {
        // If too many tombstones relative to real elements, rebuild same size.
        // This is common in real implementations.
        if (tombstones_ > size_ && tombstones_ > 8)
        {
            rehash(table_.size());
        }
    }

    void rehash(size_t new_cap)
    {
        new_cap = nextPow2(max<size_t>(new_cap, 8));

        vector<Slot> old = move(table_);
        table_.assign(new_cap, Slot{});
        size_ = 0;
        tombstones_ = 0;

        for (auto &s : old)
        {
            if (s.state == State::Filled)
            {
                // reinsert into new table
                insert_or_assign(s.key, s.value);
            }
        }
    }

    static size_t nextPow2(size_t n)
    {
        // round up to power of two
        if (n <= 1)
            return 1;
        size_t p = 1;
        while (p < n)
            p <<= 1;
        return p;
    }
};

int main()
{
    HashMap<int, string> users;

    users.insert_or_assign(101, "Mohammed");
    users.insert_or_assign(205, "Hassen");
    users.insert_or_assign(330, "Addis");

    if (auto *name = users.find(205))
    {
        cout << "205 -> " << *name << "\n";
    }

    users.erase(205);

    cout << "size=" << users.size()
         << " cap=" << users.capacity()
         << " load=" << users.load_factor() << "\n";
}

#include <iostream>
#include <string>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

// ============================
// Your HashMap (unchanged core)
// ============================
template <class K, class V, class Hash = hash<K>, class KeyEqual = equal_to<K>>
class HashMap
{
public:
    HashMap(size_t initial_capacity = 16, float max_load_factor = 0.70f)
        : max_load_factor_(max_load_factor)
    {
        if (max_load_factor_ <= 0.0f || max_load_factor_ >= 0.95f)
            throw invalid_argument("max_load_factor must be in (0, 0.95).");
        rehash(nextPow2(max<size_t>(initial_capacity, 8)));
    }

    size_t size() const noexcept { return size_; }

    bool insert_or_assign(const K &key, const V &value)
    {
        maybeGrow();

        size_t first_tombstone = npos;
        size_t idx = indexFor(key);

        for (size_t probe = 0; probe < table_.size(); ++probe)
        {
            Slot &s = table_[idx];

            if (s.state == State::Empty)
            {
                size_t target = (first_tombstone != npos) ? first_tombstone : idx;
                placeAt(target, key, value);
                return true;
            }

            if (s.state == State::Tombstone)
            {
                if (first_tombstone == npos)
                    first_tombstone = idx;
            }
            else if (eq_(s.key, key))
            {
                s.value = value;
                return false;
            }

            idx = (idx + 1) & (table_.size() - 1);
        }

        rehash(table_.size() * 2);
        return insert_or_assign(key, value);
    }

    V *find(const K &key) noexcept
    {
        if (table_.empty())
            return nullptr;

        size_t idx = indexFor(key);
        for (size_t probe = 0; probe < table_.size(); ++probe)
        {
            Slot &s = table_[idx];

            if (s.state == State::Empty)
                return nullptr;
            if (s.state == State::Filled && eq_(s.key, key))
                return &s.value;

            idx = (idx + 1) & (table_.size() - 1);
        }
        return nullptr;
    }

    bool erase(const K &key) noexcept
    {
        if (table_.empty())
            return false;

        size_t idx = indexFor(key);
        for (size_t probe = 0; probe < table_.size(); ++probe)
        {
            Slot &s = table_[idx];

            if (s.state == State::Empty)
                return false;

            if (s.state == State::Filled && eq_(s.key, key))
            {
                s.state = State::Tombstone;
                --size_;
                ++tombstones_;
                maybeRebuild();
                return true;
            }

            idx = (idx + 1) & (table_.size() - 1);
        }
        return false;
    }

private:
    enum class State : uint8_t
    {
        Empty,
        Filled,
        Tombstone
    };

    struct Slot
    {
        State state = State::Empty;
        K key{};
        V value{};
    };

    static constexpr size_t npos = static_cast<size_t>(-1);

    vector<Slot> table_;
    size_t size_ = 0;
    size_t tombstones_ = 0;
    float max_load_factor_;
    Hash hasher_;
    KeyEqual eq_;

    size_t mixedHash(const K &key) const noexcept
    {
        size_t h = hasher_(key);
        uint64_t x = static_cast<uint64_t>(h);
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        x = x ^ (x >> 31);
        return static_cast<size_t>(x);
    }

    size_t indexFor(const K &key) const noexcept
    {
        return mixedHash(key) & (table_.size() - 1);
    }

    void placeAt(size_t idx, const K &key, const V &value)
    {
        Slot &s = table_[idx];
        if (s.state == State::Tombstone)
            --tombstones_;
        s.key = key;
        s.value = value;
        s.state = State::Filled;
        ++size_;
    }

    void maybeGrow()
    {
        if (table_.empty())
        {
            rehash(16);
            return;
        }

        size_t used = size_ + tombstones_;
        float used_lf = static_cast<float>(used) / table_.size();
        if (used_lf > max_load_factor_)
            rehash(table_.size() * 2);
    }

    void maybeRebuild()
    {
        if (tombstones_ > size_ && tombstones_ > 8)
            rehash(table_.size());
    }

    void rehash(size_t new_cap)
    {
        new_cap = nextPow2(max<size_t>(new_cap, 8));

        vector<Slot> old = move(table_);
        table_.assign(new_cap, Slot{});
        size_ = 0;
        tombstones_ = 0;

        for (auto &s : old)
            if (s.state == State::Filled)
                insert_or_assign(s.key, s.value);
    }

    static size_t nextPow2(size_t n)
    {
        if (n <= 1)
            return 1;
        size_t p = 1;
        while (p < n)
            p <<= 1;
        return p;
    }
};

// ============================
// Media model we store pointers to
// ============================
struct Track
{
    int id;
    string title;
    string path;

    Track(int id_, string title_, string path_)
        : id(id_), title(std::move(title_)), path(std::move(path_)) {}
};

// ============================
// Helpers
// ============================
static string toLowerCopy(string s)
{
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c)
              { return static_cast<char>(tolower(c)); });
    return s;
}

static bool isMp3File(const fs::path &p)
{
    if (!p.has_extension())
        return false;
    return toLowerCopy(p.extension().string()) == ".mp3";
}

// Launch OS default player for a path.
// (This is the simplest “real play” without external libraries.)
static void playFileWithOS(const string &filepath)
{
    // IMPORTANT: system() executes a command in a shell.
    // If you use untrusted paths, you must sanitize/escape carefully.
    // Here it’s okay for your own local folder project.

#ifdef _WIN32
    // start "" "C:\path\file.mp3"
    string cmd = "start \"\" \"" + filepath + "\"";
#elif __APPLE__
    // open "/path/file.mp3"
    string cmd = "open \"" + filepath + "\"";
#else
    // xdg-open "/path/file.mp3"
    string cmd = "xdg-open \"" + filepath + "\"";
#endif
    system(cmd.c_str());
}

// ============================
// Main program
// ============================
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <music_folder_path>\n";
        return 1;
    }

    fs::path root = fs::path(argv[1]);

    if (!fs::exists(root) || !fs::is_directory(root))
    {
        cout << "Error: path is not a valid directory: " << root.string() << "\n";
        return 1;
    }

    HashMap<int, Track *> library;
    vector<int> ids_in_order; // for listing in scan order

    int nextId = 1;

    // 1) scan folder recursively
    for (auto const &entry : fs::recursive_directory_iterator(root))
    {
        if (!entry.is_regular_file())
            continue;

        const fs::path &p = entry.path();
        if (!isMp3File(p))
            continue;

        string title = p.stem().string();           // filename without extension
        string fullpath = fs::absolute(p).string(); // full absolute path

        Track *t = new Track(nextId, title, fullpath);
        library.insert_or_assign(nextId, t);
        ids_in_order.push_back(nextId);

        ++nextId;
    }

    cout << "Scan complete. Found " << library.size() << " .mp3 files.\n\n";

    if (library.size() == 0)
        return 0;

    // 2) simple menu: list + play by ID
    while (true)
    {
        cout << "===== MUSIC LIBRARY =====\n";
        cout << "Commands:\n";
        cout << "  l            -> list tracks\n";
        cout << "  p <id>       -> play track\n";
        cout << "  d <id>       -> delete track from library (and free memory)\n";
        cout << "  q            -> quit\n";
        cout << "> ";

        string cmd;
        cin >> cmd;

        if (cmd == "q")
            break;

        if (cmd == "l")
        {
            for (int id : ids_in_order)
            {
                Track **pp = library.find(id); // because V=Track*
                if (!pp)
                    continue; // maybe deleted

                Track *t = *pp;
                cout << "[" << t->id << "] " << t->title << "\n";
            }
            cout << "\n";
        }
        else if (cmd == "p")
        {
            int id;
            cin >> id;

            Track **pp = library.find(id);
            if (!pp)
            {
                cout << "Not found: " << id << "\n\n";
                continue;
            }

            Track *t = *pp;
            cout << "Opening: " << t->path << "\n\n";
            playFileWithOS(t->path);
        }
        else if (cmd == "d")
        {
            int id;
            cin >> id;

            Track **pp = library.find(id);
            if (!pp)
            {
                cout << "Not found: " << id << "\n\n";
                continue;
            }

            delete *pp;        // free Track object
            library.erase(id); // remove from HashMap
            cout << "Deleted track " << id << " from library.\n\n";
        }
        else
        {
            cout << "Unknown command.\n\n";
        }
    }

    // 3) cleanup all remaining Track* to avoid memory leaks
    for (int id : ids_in_order)
    {
        Track **pp = library.find(id);
        if (pp)
        {
            delete *pp;
            library.erase(id);
        }
    }

    cout << "Bye!\n";
    return 0;
}