#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <stdexcept>

template <typename K, typename V, int ORDER = 4>
class BPlusTree {
  static_assert(ORDER >= 3, "ORDER should be >= 3 for a meaningful B+ tree.");

  struct Node {
    bool isLeaf = false;
    Node* parent = nullptr;
    std::vector<K> keys;
    virtual ~Node() = default;
  };

  struct InternalNode : Node {
    std::vector<Node*> children; // size = keys.size() + 1
    InternalNode() { this->isLeaf = false; }
  };

  struct LeafNode : Node {
    std::vector<V> values;       // same size as keys
    LeafNode* next = nullptr;    // linked list of leaves
    LeafNode() { this->isLeaf = true; }
  };

public:
  BPlusTree() = default;
  ~BPlusTree() { destroy(root_); }

  // Insert or update (if key already exists).
  void insert(const K& key, const V& value) {
    if (!root_) {
      auto* leaf = new LeafNode();
      leaf->keys.push_back(key);
      leaf->values.push_back(value);
      root_ = leaf;
      return;
    }

    LeafNode* leaf = findLeaf(key);
    auto it = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
    std::size_t pos = static_cast<std::size_t>(it - leaf->keys.begin());

    // Update if exists
    if (it != leaf->keys.end() && *it == key) {
      leaf->values[pos] = value;
      return;
    }

    // Insert into leaf
    leaf->keys.insert(leaf->keys.begin() + static_cast<long>(pos), key);
    leaf->values.insert(leaf->values.begin() + static_cast<long>(pos), value);

    if (static_cast<int>(leaf->keys.size()) >= ORDER) {
      splitLeaf(leaf);
    }
  }

  // Exact lookup
  std::optional<V> find(const K& key) const {
    if (!root_) return std::nullopt;
    LeafNode* leaf = findLeafConst(key);

    auto it = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
    if (it == leaf->keys.end() || *it != key) return std::nullopt;

    std::size_t pos = static_cast<std::size_t>(it - leaf->keys.begin());
    return leaf->values[pos];
  }

  // Range scan [lo, hi] inclusive
  std::vector<std::pair<K, V>> rangeQuery(const K& lo, const K& hi) const {
    std::vector<std::pair<K, V>> out;
    if (!root_ || lo > hi) return out;

    LeafNode* leaf = findLeafConst(lo);
    while (leaf) {
      for (std::size_t i = 0; i < leaf->keys.size(); ++i) {
        const K& k = leaf->keys[i];
        if (k < lo) continue;
        if (k > hi) return out;
        out.emplace_back(k, leaf->values[i]);
      }
      leaf = leaf->next;
    }
    return out;
  }

  // Debug print (level-order-ish for small trees)
  void printLeaves() const {
    if (!root_) {
      std::cout << "(empty)\n";
      return;
    }
    const LeafNode* leaf = leftMostLeaf();
    while (leaf) {
      std::cout << "[";
      for (std::size_t i = 0; i < leaf->keys.size(); ++i) {
        std::cout << leaf->keys[i];
        if (i + 1 < leaf->keys.size()) std::cout << " ";
      }
      std::cout << "] -> ";
      leaf = leaf->next;
    }
    std::cout << "null\n";
  }

private:
  Node* root_ = nullptr;

  // --- Utilities ---
  static void destroy(Node* n) {
    if (!n) return;
    if (!n->isLeaf) {
      auto* in = static_cast<InternalNode*>(n);
      for (Node* c : in->children) destroy(c);
    }
    delete n;
  }

  LeafNode* leftMostLeaf() const {
    Node* cur = root_;
    while (cur && !cur->isLeaf) {
      cur = static_cast<InternalNode*>(cur)->children.front();
    }
    return static_cast<LeafNode*>(cur);
  }

  LeafNode* findLeaf(const K& key) {
    Node* cur = root_;
    while (!cur->isLeaf) {
      auto* in = static_cast<InternalNode*>(cur);
      // first index where key < in->keys[i]  => go children[i]
      std::size_t i = static_cast<std::size_t>(
          std::upper_bound(in->keys.begin(), in->keys.end(), key) - in->keys.begin());
      cur = in->children[i];
    }
    return static_cast<LeafNode*>(cur);
  }

  LeafNode* findLeafConst(const K& key) const {
    Node* cur = root_;
    while (!cur->isLeaf) {
      auto* in = static_cast<InternalNode*>(cur);
      std::size_t i = static_cast<std::size_t>(
          std::upper_bound(in->keys.begin(), in->keys.end(), key) - in->keys.begin());
      cur = in->children[i];
    }
    return static_cast<LeafNode*>(cur);
  }

  // --- Splits ---
  void splitLeaf(LeafNode* leaf) {
    // Split into (left=leaf) and (right=newLeaf)
    auto* newLeaf = new LeafNode();
    newLeaf->parent = leaf->parent;

    const int total = static_cast<int>(leaf->keys.size());
    const int split = total / 2; // typical

    // Move second half to new leaf
    newLeaf->keys.assign(leaf->keys.begin() + split, leaf->keys.end());
    newLeaf->values.assign(leaf->values.begin() + split, leaf->values.end());

    leaf->keys.resize(split);
    leaf->values.resize(split);

    // Link leaves
    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    // Promote smallest key in new leaf to parent
    const K promoteKey = newLeaf->keys.front();
    insertIntoParent(leaf, promoteKey, newLeaf);
  }

  void splitInternal(InternalNode* in) {
    auto* newIn = new InternalNode();
    newIn->parent = in->parent;

    const int totalKeys = static_cast<int>(in->keys.size());
    const int mid = totalKeys / 2;

    // promote key = in->keys[mid]
    const K promoteKey = in->keys[mid];

    // Right side keys go to newIn (keys after mid)
    newIn->keys.assign(in->keys.begin() + mid + 1, in->keys.end());
    in->keys.resize(mid);

    // Children: left keeps first mid+1 children, right gets the rest
    // (because internal: children = keys+1)
    newIn->children.assign(in->children.begin() + (mid + 1), in->children.end());
    in->children.resize(mid + 1);

    // Fix parent pointers
    for (Node* c : newIn->children) c->parent = newIn;

    insertIntoParent(in, promoteKey, newIn);
  }

  void insertIntoParent(Node* left, const K& key, Node* right) {
    // If left was root, create new root
    if (left == root_) {
      auto* newRoot = new InternalNode();
      newRoot->keys.push_back(key);
      newRoot->children.push_back(left);
      newRoot->children.push_back(right);
      left->parent = newRoot;
      right->parent = newRoot;
      root_ = newRoot;
      return;
    }

    auto* parent = static_cast<InternalNode*>(left->parent);

    // Find where 'left' is in parent's children
    auto itChild = std::find(parent->children.begin(), parent->children.end(), left);
    if (itChild == parent->children.end()) {
      throw std::logic_error("Parent does not contain left child pointer.");
    }
    std::size_t leftIndex = static_cast<std::size_t>(itChild - parent->children.begin());

    // Insert key into parent->keys at position leftIndex
    parent->keys.insert(parent->keys.begin() + static_cast<long>(leftIndex), key);

    // Insert right child just after left in children
    parent->children.insert(parent->children.begin() + static_cast<long>(leftIndex + 1), right);
    right->parent = parent;

    if (static_cast<int>(parent->keys.size()) >= ORDER) {
      splitInternal(parent);
    }
  }
};

// -------------------- Demo --------------------
int main() {
  BPlusTree<int, std::string, 4> idx; // ORDER=4 (small for demo)

  idx.insert(10, "ten");
  idx.insert(20, "twenty");
  idx.insert(5, "five");
  idx.insert(6, "six");
  idx.insert(12, "twelve");
  idx.insert(30, "thirty");
  idx.insert(7, "seven");
  idx.insert(17, "seventeen");

  std::cout << "Leaves: ";
  idx.printLeaves();

  if (auto v = idx.find(12)) {
    std::cout << "find(12) = " << *v << "\n";
  } else {
    std::cout << "find(12) not found\n";
  }

  std::cout << "rangeQuery(6..20):\n";
  for (auto& [k, v] : idx.rangeQuery(6, 20)) {
    std::cout << "  " << k << " -> " << v << "\n";
  }
}