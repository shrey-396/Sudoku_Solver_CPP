#include <iostream>
#include <vector>

const int SIZE = 9;

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number can be placed at a given position
bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check the row
    for (int x = 0; x < SIZE; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }
    
    // Check the column
    for (int x = 0; x < SIZE; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }
    
    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    
    return true;
}

// Function to find an empty location in the grid
bool findEmptyLocation(const std::vector<std::vector<int>>& grid, int &row, int &col) {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;
    
    // If there is no empty location, the puzzle is solved
    if (!findEmptyLocation(grid, row, col)) {
        return true;
    }
    
    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        // If placing num at grid[row][col] is safe
        if (isSafe(grid, row, col, num)) {
            // Make the tentative assignment
            grid[row][col] = num;
            
            // Return true if success, false otherwise
            if (solveSudoku(grid)) {
                return true;
            }
            
            // Failure, undo & try again
            grid[row][col] = 0;
        }
    }
    
    return false; // This triggers backtracking
}

int main() {
    // 0 represents empty cells
    std::vector<std::vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        std::cout << "No solution exists" << std::endl;
    }
    
    return 0;
}
