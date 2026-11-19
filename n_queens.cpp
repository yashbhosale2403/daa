#include <iostream>
using namespace std;

#define N 8

int solutionCount = 0;

bool isSafe(int board[N][N], int row, int col) {
    // Check the same row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }

    // Check the upper diagonal on the left side
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }

    // Check the lower diagonal on the left side
    for (int i = row + 1, j = col - 1; i < N && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }

    return true;
}

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

bool solveNQueens(int board[N][N], int col) {
    if (col == N) {
        solutionCount++;
        printBoard(board);
        return solutionCount >= 2; // Stop after 2 solutions
    }

    for (int row = 0; row < N; row++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;

            if (solveNQueens(board, col + 1)) return true;

            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int board[N][N] = {0};
    solveNQueens(board, 0);
    return 0;
}
