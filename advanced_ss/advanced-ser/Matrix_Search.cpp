#include <iostream>
using namespace std;

#define ROW 4
#define COL 4

bool searchMatrix(int mat[ROW][COL], int target) {
    int i = 0, j = COL - 1;

    while (i < ROW && j >= 0) {
        if (mat[i][j] == target)
            return true;
        else if (mat[i][j] > target)
            j--;
        else
            i++;
    }
    return false;
}

int main() {
    int mat[ROW][COL] = {
        {10,20,30,40},
        {15,25,35,45},
        {27,29,37,48},
        {32,33,39,50}
    };

    cout << searchMatrix(mat, 29);
    return 0;
}
