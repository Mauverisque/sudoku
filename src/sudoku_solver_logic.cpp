#include "sudoku_solver_logic.h"

/**
 * @brief Detects all invalid sudoku cells.
 *
 * @param sudoku The sudoku board.
 * @return Set of <row, column> pairs of all invalid cells.
 */
unordered_int_pair_set getAllInvalidCells(const two_d_int_vector &sudoku) {
  unordered_int_pair_set all_invalid_cells{};

  for (int row = 0; row != 9; ++row) {
    for (int col = 0; col != 9; ++col) {
      if (sudoku[row][col] != 0) {
        std::vector<std::pair<int, int>> invalid_cell{
            checkIfNumIsValid(row, col, sudoku, sudoku[row][col])};
        if (invalid_cell.size() != 0) {
          all_invalid_cells.insert({invalid_cell[0]});
          all_invalid_cells.insert({invalid_cell[1]});
        }
      }
    }
  }

  return all_invalid_cells;
}

/**
 * @brief Checks whether num in r row and c column is valid.
 *
 * @param r Current row.
 * @param c Current column.
 * @param sudoku The sudoku board.
 * @param num Current number.
 * @return If current number is invalid, returns two <row, column> pairs: of the
 *         current cell and of the cell it conflicts with, otherwise returns an
 *         empty container.
 */
std::vector<std::pair<int, int>>
checkIfNumIsValid(const int r, const int c, const two_d_int_vector &sudoku,
                  const int num) {
  std::vector<std::pair<int, int>> two_invalid_cells{};

  for (int row_or_col = 0; row_or_col != 9; ++row_or_col) {
    // Check cells within the same row.
    if (sudoku[row_or_col][c] == num && row_or_col != r) {
      two_invalid_cells.push_back({r, c});
      two_invalid_cells.push_back({row_or_col, c});
      return two_invalid_cells;
    }
    // Check cells within the same column.
    if (sudoku[r][row_or_col] == num && row_or_col != c) {
      two_invalid_cells.push_back({r, c});
      two_invalid_cells.push_back({r, row_or_col});
      return two_invalid_cells;
    }
  }

  // Find the upper left cell of the square the current cell belongs to.
  int upper_row = (r / 3) * 3;
  int left_col = (c / 3) * 3;
  for (int row = upper_row; row != upper_row + 3; ++row) {
    for (int col = left_col; col != left_col + 3; ++col) {
      // Check cells within the same square.
      if (sudoku[row][col] == num && (row != r && col != c)) {
        two_invalid_cells.push_back({r, c});
        two_invalid_cells.push_back({row, col});
        return two_invalid_cells;
      }
    }
  }

  return two_invalid_cells;
}

/**
 * @brief Solves all trivial rows (rows with 8 cells filled in).
 *
 * @param sudoku
 */
void solveTrivialRows(two_d_int_vector &sudoku) {
  for (int row = 0; row != 9; ++row) {
    int sum{0};
    int coor{-1};
    for (int col = 0; col != 9; ++col) {
      sum += sudoku[row][col];
      if (sudoku[row][col] == 0) {
        if (coor != -1) {
          sum = 0;
          break;
        } else {
          coor = row * 9 + col;
        }
      }
    }
    if (sum >= 36) {
      sudoku[coor / 9][coor % 9] = 45 - sum;
    }
  }
}

/**
 * @brief Solves all trivial columns (columns with 8 cells filled in).
 *
 * @param sudoku The sudoku board.
 */
void solveTrivialColumns(two_d_int_vector &sudoku) {
  for (int col = 0; col != 9; ++col) {
    int sum{0};
    int coor{-1};
    for (int row = 0; row != 9; ++row) {
      sum += sudoku[row][col];
      if (sudoku[row][col] == 0) {
        if (coor != -1) {
          sum = 0;
          break;
        } else {
          coor = row * 9 + col;
        }
      }
    }
    if (sum >= 36) {
      sudoku[coor / 9][coor % 9] = 45 - sum;
    }
  }
}

/**
 * @brief Solves all trivial squares (squares with 8 cells filled in).
 *
 * @param sudoku The sudoku board.
 */
void solveTrivialSquares(two_d_int_vector &sudoku) {
  for (int row = 0; row != 3; ++row) {
    for (int col = 0; col != 3; ++col) {
      int upper_row = row * 3;
      int left_col = col * 3;
      int sum{0};
      int coor{-1};

      for (int r = upper_row; r != upper_row + 3; ++r) {
        for (int c = left_col; c != left_col + 3; ++c) {
          sum += sudoku[r][c];
          if (sudoku[r][c] == 0) {
            if (coor != -1) {
              sum = 0;
              break;
            } else {
              coor = r * 9 + c;
            }
          }
        }
        if (sum == 0) {
          break;
        }
        if (sum >= 36) {
          sudoku[coor / 9][coor % 9] = 45 - sum;
        }
      }
    }
  }
}
/**
 * @brief This function is a superpermutation of all trivial solving functions.
 *        Essentially guarantees that every trivial row/column/square will be
 *        solved.
 *
 * @param sudoku The sudoku board.
 */
void solveTrivial(two_d_int_vector &sudoku) {
  solveTrivialRows(sudoku);
  solveTrivialColumns(sudoku);
  solveTrivialSquares(sudoku);
  solveTrivialRows(sudoku);
  solveTrivialColumns(sudoku);
  solveTrivialRows(sudoku);
  solveTrivialSquares(sudoku);
  solveTrivialColumns(sudoku);
  solveTrivialRows(sudoku);
}

/**
 * @brief Finds next empty cell if it exists. Moves cur_r and cur_c to it.
 *
 * @param cur_r Current row.
 * @param cur_c Current column.
 * @param sudoku The sudoku board.
 * @return true if an empty cell was found, false otherwise.
 */
bool findEmptyCell(int &cur_r, int &cur_c, const two_d_int_vector &sudoku) {
  for (int row = cur_r; row != 9; ++row) {
    for (int col = cur_c; col != 9; ++col) {
      if (sudoku[row][col] == 0) {
        cur_r = row;
        cur_c = col;
        return true;
      }
    }
  }

  return false;
}

/**
 * @brief Recursively brute forces a sudoku solution. Iterates through
 *        numbers 1 - 9 in ascending order.
 *
 * @param sudoku The sudoku board.
 * @param temp Copy of the sudoku board created for solution serching. When
 * a solution is found it will be copied to sudoku.
 * @param flag Atomic_bool flag signaling a solution being found.
 * @return true if a solution was found, false otherwise.
 */
bool solveOneToNine(two_d_int_vector &sudoku, two_d_int_vector &temp,
                    std::atomic_bool &flag) {
  int row{0};
  int col{0};

  // Search for the next empty cell, if none were found it means the the
  // solution was found.
  if (!findEmptyCell(row, col, temp) && flag == false) {
    flag = true;
    sudoku = temp;

    return true;
  } else {
    // Go through 1 - 9.
    for (int num = 1; num != 10; ++num) {
      if (flag == true) {
        break;
      }

      if (checkIfNumIsValid(row, col, temp, num).size() == 0) {
        temp[row][col] = num;

        // Solve for the next empty cells recursively.
        if (solveOneToNine(sudoku, temp, flag)) {
          return true;
        } else {
          // Backtrack to try the next number.
          temp[row][col] = 0;
        }
      }
    }
  }

  return false;
}

/**
 * @brief Recursively brute forces a sudoku solution. Iterates through
 *        numbers 1 - 9 in descending order.
 *
 * @param sudoku The sudoku board.
 * @param temp Copy of the sudoku board created for solution serching. When
 * a solution is found it will be copied to sudoku.
 * @param flag Atomic_bool flag signaling a solution being found.
 * @return true if a solution was found, false otherwise.
 */
bool solveNineToOne(two_d_int_vector &sudoku, two_d_int_vector &temp,
                    std::atomic_bool &flag) {
  int row{0};
  int col{0};

  // Search for the next empty cell, if none were found it means the the
  // solution was found.
  if (!findEmptyCell(row, col, temp) && flag == false) {
    flag = true;
    sudoku = temp;

    return true;
  } else {
    // Go through 9 - 1.
    for (int num = 9; num != 0; --num) {
      if (flag == true) {
        break;
      }

      if (checkIfNumIsValid(row, col, temp, num).size() == 0) {
        temp[row][col] = num;

        // Solve for the next empty cells recursively.
        if (solveNineToOne(sudoku, temp, flag)) {
          return true;
        } else {
          // Backtrack to try the next number.
          temp[row][col] = 0;
        }
      }
    }
  }

  return false;
}

/**
 * @brief Launches two threads to search for a solution.
 *
 * @param sudoku The sudoku board.
 * @return true if a solution was found, false otherwise.
 */
bool solve(two_d_int_vector &sudoku) {
  // Fill all trivial cells and check the sudoku for validity.
  solveTrivial(sudoku);
  if (getAllInvalidCells(sudoku).size() != 0) {
    return false;
  }

  // Create a flag to signal any of threads' completion.
  std::atomic_bool finished{false};

  // Create two copies of the sudoku for the threads.
  two_d_int_vector sudoku_copy1{sudoku};
  two_d_int_vector sudoku_copy2{sudoku};

  // Create and launch the threads.
  std::thread t1(solveOneToNine, std::ref(sudoku), std::ref(sudoku_copy1),
                 std::ref(finished));
  std::thread t2(solveNineToOne, std::ref(sudoku), std::ref(sudoku_copy2),
                 std::ref(finished));

  // Wait for both threads to finish.
  t1.join();
  t2.join();

  if (finished == true) {
    return true;
  } else {
    return false;
  }
}
