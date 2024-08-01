#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QButtonGroup>
#include <QDebug>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

private:
  void createSudokuBoard();
  void createNumberBoard();
  void createWidgets();
  void createLayout();

  void onNumberChanged();
  void clearSudoku();
  void solveSudoku();

  int current_number{};

  QPushButton *clear_sudoku;
  QPushButton *solve_sudoku;

  QButtonGroup *push_button_group;
  QButtonGroup *radio_button_group;

  QWidget *central_widget;
  QGridLayout *sudoku_layout;
  QGridLayout *number_layout;
};

#endif // MAIN_WINDOW_H_
