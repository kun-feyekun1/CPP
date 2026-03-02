#include <bits/stdc++.h>
using namespace std;

vector<int> S = {3, 5, 6, 7};
int target = 15;
int n;

vector<int> current;
int solutionCount = 0;

void findSubsets(int start, int sumSoFar) {
    if (sumSoFar == target) {
        solutionCount++;
        cout << "Subset " << solutionCount << ": ";
        for (int x : current) cout << x << " ";
        cout << "\n";
        return;
    }

    if (sumSoFar > target) return;

    for (int i = start; i < n; ++i) {
        // Include S[i]
        current.push_back(S[i]);
        findSubsets(i + 1, sumSoFar + S[i]);  // move to next index (no reuse)
        current.pop_back();                    // backtrack

        // Optional: skip duplicates if array had duplicates (not needed here)
    }
}

int main() {
    n = S.size();
    sort(S.begin(), S.end());  // helps with pruning & presentation

    cout << "Subsets that sum to " << target << ":\n";
    findSubsets(0, 0);

    cout << "\nTotal subsets found: " << solutionCount << "\n";

    return 0;
}