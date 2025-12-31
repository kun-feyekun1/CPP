#include <iostream>
using namespace std;

void computeLPS(char pat[], int m, int lps[]) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char txt[], char pat[]) {
    int i = 0, j = 0;
    int n = 0, m = 0;

    while (txt[n]) n++;
    while (pat[m]) m++;

    int lps[m];
    computeLPS(pat, m, lps);

    while (i < n) {
        if (txt[i] == pat[j]) {
            i++; j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < n && txt[i] != pat[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char txt[] = "ABABDABACDABABCABAB";
    char pat[] = "ABABCABAB";

    KMPSearch(txt, pat);
    return 0;
}
