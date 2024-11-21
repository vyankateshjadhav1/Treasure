#include<iostream>
#include<vector>
using namespace std;

// Function to check if placing a queen at board[row][col] is safe
bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check the column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) return false;
    }

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false;
    }

    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) return false;
    }

    return true;
}

// Recursive function to solve N-Queens problem
bool solveNQueens(vector<vector<int>>& board, int row, int n) {
  
    // Base case: all queens are placed
    if (row >= n) return true;

    // Try placing a queen in all columns for the current row
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            // Place the queen
            board[row][col] = 1;

            // Recur for the next row
            if (solveNQueens(board, row + 1, n)) return true;

            // Backtrack: remove the queen
            board[row][col] = 0;
        }
    }

    // If no placement is possible, return false
    return false;
}

// Function to print the board
void printBoard(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the size of the board (N): ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));

    if (solveNQueens(board, 0, n)) {
        cout << "Solution to " << n << "-Queens problem:" << endl;
        printBoard(board, n);
    } else {
        cout << "No solution exists for " << n << "-Queens problem." << endl;
    }

    return 0;
}