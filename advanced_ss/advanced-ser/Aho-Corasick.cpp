#include <iostream>
#include <vector>
#include <Queue>

using namespace std;

const int ALPHABET = 26;  // assuming lowercase English letters

struct AhoCorasick {
    vector<vector<int>> trie;
    vector<int> fail;
    vector<vector<int>> output;  // list of pattern indices that end at this node
    int nodes = 1;               // node 0 is root

    AhoCorasick() {
        trie.emplace_back(ALPHABET, -1);
        fail.push_back(0);
        output.emplace_back();
    }

    void insert(const string& word, int index) {
        int node = 0;
        for (char ch : word) {
            int c = ch - 'a';
            if (trie[node][c] == -1) {
                trie[node][c] = nodes++;
                trie.emplace_back(ALPHABET, -1);
                fail.push_back(0);
                output.emplace_back();
            }
            node = trie[node][c];
        }
        output[node].push_back(index);  // this node ends pattern #index
    }

    void build() {
        queue<int> q;
        // First level
        for (int c = 0; c < ALPHABET; ++c) {
            if (trie[0][c] != -1) {
                int child = trie[0][c];
                fail[child] = 0;
                q.push(child);
            }
        }

        while (!q.empty()) {
            int cur = q.front(); q.pop();

            for (int c = 0; c < ALPHABET; ++c) {
                if (trie[cur][c] != -1) {
                    int child = trie[cur][c];
                    int f = fail[cur];

                    while (f != 0 && trie[f][c] == -1) {
                        f = fail[f];
                    }
                    if (trie[f][c] != -1) {
                        f = trie[f][c];
                    }

                    fail[child] = f;
                    // Merge outputs (important!)
                    output[child].insert(output[child].end(),
                                         output[f].begin(), output[f].end());

                    q.push(child);
                }
            }
        }
    }

    // Returns list of (position, pattern_index) where pattern ends
    vector<pair<int, int>> find(const string& text, const vector<string>& patterns) {
        vector<pair<int, int>> matches;

        int state = 0;
        for (int i = 0; i < text.size(); ++i) {
            int c = text[i] - 'a';

            while (state != 0 && trie[state][c] == -1) {
                state = fail[state];
            }
            if (trie[state][c] != -1) {
                state = trie[state][c];
            }

            // All patterns that end here
            for (int idx : output[state]) {
                matches.emplace_back(i - patterns[idx].size() + 1, idx);
            }
        }

        return matches;
    }
};

int main() {
    vector<string> patterns = {"he", "she", "his", "hers"};
    string text = "ushershishe";

    AhoCorasick ac;

    for (int i = 0; i < patterns.size(); ++i) {
        ac.insert(patterns[i], i);
    }

    ac.build();

    auto results = ac.find(text, patterns);

    cout << "Aho-Corasick matches:\n";
    for (auto [pos, idx] : results) {
        cout << "Pattern \"" << patterns[idx] << "\" at position " << pos << "\n";
    }

    return 0;
}