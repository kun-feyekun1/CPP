
#include <iostream>
using namespace std;
#include <vector>
#include <string>

// Compute Longest Proper Prefix which is also Suffix (LPS / pi array)
vector<int> computeLPS(const string& pat) {
    int m = pat.size();
    vector<int> lps(m, 0);
    int len = 0;  // length of previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];  // fall back
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> KMP(const string& text, const string& pat) {
    int n = text.size();
    int m = pat.size();
    vector<int> positions;

    if (m == 0) return positions;

    vector<int> lps = computeLPS(pat);

    int i = 0;  // index for text
    int j = 0;  // index for pattern

    while (i < n) {
        if (pat[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            // Found pattern at i - j
            positions.push_back(i - j);
            j = lps[j - 1];  // continue for overlapping matches
        } else if (i < n && pat[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return positions;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pat  = "ABAB";

    vector<int> res = KMP(text, pat);

    cout << "KMP - Pattern found at positions: ";
    for (int p : res) cout << p << " ";
    cout << "\n";

    return 0;
}