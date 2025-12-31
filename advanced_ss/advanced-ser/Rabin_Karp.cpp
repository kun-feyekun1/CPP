#include <iostream>
using namespace std;

#define d 256
#define q 101   // prime

void rabinKarp(char txt[], char pat[]) {
    int n = 0, m = 0;
    while (txt[n]) n++;
    while (pat[m]) m++;

    int h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    int p = 0, t = 0;

    for (int i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (txt[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                cout << "Pattern found at index " << i << endl;
        }

        if (i < n - m) {
            t = (d * (t - txt[i] * h) + txt[i + m]) % q;
            if (t < 0)
                t += q;
        }
    }
}

int main() {
    char txt[] = "GEEKSFORGEEKS";
    char pat[] = "GEEK";

    rabinKarp(txt, pat);
    return 0;
}
