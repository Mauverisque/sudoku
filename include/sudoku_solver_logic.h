#ifndef SUDOKU_SOLVER_LOGIC_H_
#define SUDOKU_SOLVER_LOGIC_H_

#include <atomic>
#include <boost/functional/hash.hpp>
#include <thread>
#include <unordered_set>
#include <vector>

using unordered_int_pair_set =
    std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>;
using two_d_int_vector = std::vector<std::vector<int>>;

unordered_int_pair_set getAllInvalidCells(const two_d_int_vector &sudoku);
std::vector<std::pair<int, int>>
checkIfNumIsValid(const int r, const int c, const two_d_int_vector &sudoku,
                  const int num);

void solveTrivialRows(two_d_int_vector &sudoku);
void solveTrivialColumns(two_d_int_vector &sudoku);
void solveTrivialSquares(two_d_int_vector &sudoku);
void solveTrivial(two_d_int_vector &sudoku);

bool findEmptyCell(int &cur_r, int &cur_c, const two_d_int_vector &sudoku);
bool solveOneToNine(two_d_int_vector &sudoku, two_d_int_vector &temp,
                    std::atomic_bool &flag);
bool solveNineToOne(two_d_int_vector &sudoku, two_d_int_vector &temp,
                    std::atomic_bool &flag);
bool solve(two_d_int_vector &sudoku);

#endif // SUDOKU_SOLVER_LOGIC_H_
