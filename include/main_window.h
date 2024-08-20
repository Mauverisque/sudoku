#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QButtonGroup>
#include <QDebug>
#include <QFont>
#include <QGridLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>
#include <QPushButton>
#include <QThread>

#include "window_keyboard_detect.h"

class MainWindow : public WindowKeyboardDetect {
  Q_OBJECT

public:
  MainWindow();

private slots:
  void onKeyPressed(const int &num);
  void onSudokuCellChanged(int id);
  void onNumberChanged();
  void onProgressUpdated();

private:
  void createSudokuBoard();
  void createNumberBoard();
  void createWidgets();
  void createLayout();
  void createPopup(const QString &window_title, const QString &text,
                   const QMessageBox::Icon icon);

  void updateSudoku();
  void clearSudoku();
  void solveSudoku();
  QString getButtonStyle(const int row, const int col);

  std::vector<std::vector<int>> m_sudoku_board{};
  int m_current_number{0};

  QPushButton *clear_sudoku;
  QPushButton *solve_sudoku;

  QButtonGroup *sudoku_group;
  QButtonGroup *number_group;

  QWidget *central_widget;
  QGridLayout *sudoku_layout;
  QGridLayout *number_layout;

  QProgressDialog *progress;
};

#endif // MAIN_WINDOW_H_
