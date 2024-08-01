#include <iostream>
#include <vector>

const int SIZE = 9;

class Sudoku {
private:

    std::vector<std::vector<int>> sudoku{SIZE, std::vector<int>{SIZE}};

public:

    Sudoku(std::vector<std::vector<int>> s): sudoku(s) {
    }

    bool isValid() const {
        for (int row = 0; row != SIZE; ++row) {
            for (int col = 0; col != SIZE; ++col) {
                if (sudoku[row][col] != 0) {
                    if (!isValid(row, col, sudoku[row][col])) {
                        std::cout << "\nCell in row " << row + 1 << " column " << col + 1 << " is invalid.\n"; 
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool isValid(const int row, const int col, const int num) const {
        // Check the row and the column
        for (int rowcol = 0; rowcol != SIZE; ++rowcol) {
            // Only check cells within the same row and column (excluding the current cell)
            if ((rowcol != col && sudoku[row][rowcol] == num) || (rowcol != row && sudoku[rowcol][col] == num)) {
                return false;
            }
        }

        // Find the upper left cell of the square the current cell belongs to
        int upperRow = (row / 3) * 3;
        int leftCol = (col / 3) * 3;
        // Check the square
        for (int row = upperRow; row != upperRow + 3; ++row) {
            for (int col = leftCol; col != leftCol + 3; ++col) {
                // Only check cells within the same square (excluding the current cell)
                if (row != row && col != col && sudoku[row][col] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    bool findEmptyCell(int& curRow, int& curCol) const {
        for (int row = curRow; row != SIZE; ++row) {
            for (int col = curCol; col != SIZE; ++col) {
                if (sudoku[row][col] == 0) {
                    curRow = row;
                    curCol = col;
                    return true;
                }
            }
        }

        return false;
    }
    
    bool solve() {

        // First check whetner the sudoku is initially filled correctly
        if (!isValid()) {
            return false;
        }

        int row = 0, col = 0;

        // Searching for the next empty cell
        if (!findEmptyCell(row, col)) {
            return true;
        } else {
            // Go through numbers 1 - 9
            for (int num = 1; num != SIZE + 1; ++num) {
                if (isValid(row, col, num)) {
                    sudoku[row][col] = num;

                    // Solve for the next empty cells recursively
                    if (solve()) {
                        return true;
                    } else {
                        // Backtrack to try next number
                        sudoku[row][col] = 0;
                    }
                }
            }
        }

        return false;
    }

    void print() const {
        for (int row = 0; row != SIZE; ++row) {
            for (int col = 0; col != SIZE; ++col) {
                if (sudoku[row][col] == 0) {
                    std::cout << " *";
                } else {
                    std::cout << " " << sudoku[row][col];
                }
                
                if (col == 2 || col == 5) {
                    std::cout << " |";
                }
            }
            std::cout << "\n";
            if (row == 2 || row == 5) {
                std::cout << "------- ------- -------\n";
            }
        }
    }
    
};


int main() {
    // Input your sudoku problem here, leave empty cells as zeros
    Sudoku s({
        {1, 0, 0,   0, 0, 0,   0, 0, 0},
        {0, 0, 0,   0, 0, 0,   0, 0, 0},
        {0, 0, 1,   0, 0, 0,   0, 0, 0},

        {0, 0, 0,   0, 0, 0,   0, 0, 0},
        {0, 0, 0,   0, 0, 0,   0, 0, 0},
        {0, 0, 0,   0, 0, 0,   0, 0, 0},

        {0, 0, 0,   0, 0, 0,   0, 0, 0},
        {0, 0, 0,   0, 0, 0,   0, 0, 0},
        {0, 0, 0,   0, 0, 0,   0, 0, 0}
    });
    
    s.print();

    if (s.solve()) {
        std::cout << "\nSudoku solved! Here's a solution:\n\n";
        s.print();
    } else {
        std::cout << "\nNo viable solutions found.\n";
    }

    std::cout << "\nPress Enter to exit..";
    std::getchar();

    return 0;
}
