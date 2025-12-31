#include <iostream>
using namespace std;

#define CHAR_SIZE 256

void buildBadCharTable(char pat[], int m, int badChar[]) {
    for (int i = 0; i < CHAR_SIZE; i++)
        badChar[i] = -1;

    for (int i = 0; i < m; i++)
        badChar[(int)pat[i]] = i;
}

void boyerMooreSearch(char txt[], char pat[]) {
    int n = 0, m = 0;

    while (txt[n]) n++;
    while (pat[m]) m++;

    int badChar[CHAR_SIZE];
    buildBadCharTable(pat, m, badChar);

    int shift = 0;

    while (shift <= n - m) {
        int j = m - 1;

        // Compare from right to left
        while (j >= 0 && pat[j] == txt[shift + j])
            j--;

        if (j < 0) {
            cout << "Pattern found at index " << shift << endl;

            shift += (shift + m < n)
                     ? m - badChar[txt[shift + m]]
                     : 1;
        } else {
            int bcShift = j - badChar[txt[shift + j]];
            shift += (bcShift > 1) ? bcShift : 1;
        }
    }
}

int main() {
    char txt[] = "HERE IS A SIMPLE EXAMPLE";
    char pat[] = "EXAMPLE";

    boyerMooreSearch(txt, pat);
    return 0;
}
