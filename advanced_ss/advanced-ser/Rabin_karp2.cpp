#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Rabin-Karp with double hashing to reduce collision probability
vector<int> rabinKarp(const string& text, const string& pat) {
    int n = text.size();
    int m = pat.size();
    
    if (m == 0) return {};
    if (n < m) return {};

    // Two large primes (better collision resistance)
    const ll MOD1 = 1000000007LL;
    const ll MOD2 = 1000000009LL;
    const ll BASE = 131;           // common choice (can be 29, 131, 137, etc.)

    // Precompute powers of base
    vector<ll> pow1(m + 1, 1);
    vector<ll> pow2(m + 1, 1);
    for (int i = 1; i <= m; ++i) {
        pow1[i] = pow1[i-1] * BASE % MOD1;
        pow2[i] = pow2[i-1] * BASE % MOD2;
    }

    // Hash of pattern
    ll hashPat1 = 0;
    ll hashPat2 = 0;
    for (int i = 0; i < m; ++i) {
        hashPat1 = (hashPat1 * BASE + text[i]) % MOD1;
        hashPat2 = (hashPat2 * BASE + text[i]) % MOD2;
    }

    // Hash of first window in text
    ll hashWin1 = 0;
    ll hashWin2 = 0;
    for (int i = 0; i < m; ++i) {
        hashWin1 = (hashWin1 * BASE + text[i]) % MOD1;
        hashWin2 = (hashWin2 * BASE + text[i]) % MOD2;
    }

    vector<int> occurrences;

    for (int i = 0; i <= n - m; ++i) {
        // If both hashes match → very high probability it's a real match
        if (hashWin1 == hashPat1 && hashWin2 == hashPat2) {
            // Optional: verify exactly (recommended in production)
            bool match = true;
            for (int j = 0; j < m; ++j) {
                if (text[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                occurrences.push_back(i);
            }
        }

        // Roll the window (remove left char, add right char)
        if (i < n - m) {
            // Remove leftmost character
            hashWin1 = (hashWin1 - (ll)text[i] * pow1[m-1] % MOD1 + MOD1) % MOD1;
            hashWin2 = (hashWin2 - (ll)text[i] * pow2[m-1] % MOD2 + MOD2) % MOD2;

            // Add new rightmost character
            hashWin1 = (hashWin1 * BASE + text[i + m]) % MOD1;
            hashWin2 = (hashWin2 * BASE + text[i + m]) % MOD2;
        }
    }

    return occurrences;
}

int main() {
    string text, pat;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter pattern: ";
    getline(cin, pat);

    vector<int> res = rabinKarp(text, pat);

    if (res.empty()) {
        cout << "Pattern not found.\n";
    } else {
        cout << "Pattern found at starting indices: ";
        for (int pos : res) {
            cout << pos << " ";
        }
        cout << "\n";
    }

    return 0;
}