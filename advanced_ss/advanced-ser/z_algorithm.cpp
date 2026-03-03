#include <iostream>
#include <vector>
using namespace std;

// Returns Z-array: z[i] = length of longest substring starting at i that matches prefix
vector<int> z_algorithm(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;

    for (int i = 1; i < n; ++i) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// Find all occurrences of pat in text using Z-algorithm
vector<int> findOccurrencesZ(const string& text, const string& pat) {
    if (pat.empty()) return {};

    string concat = pat + "$" + text;  // $ is separator not in alphabet
    vector<int> z = z_algorithm(concat);

    vector<int> positions;
    int m = pat.size();

    for (int i = m + 1; i < concat.size(); ++i) {
        if (z[i] == m) {
            positions.push_back(i - m - 1);  // starting index in original text
        }
    }

    return positions;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pat  = "ABAB";

    vector<int> res = findOccurrencesZ(text, pat);

    cout << "Z-algorithm - Pattern found at positions: ";
    for (int p : res) cout << p << " ";
    cout << "\n";

    return 0;
}