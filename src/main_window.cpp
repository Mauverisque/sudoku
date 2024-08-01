#include "main_window.h"

MainWindow::MainWindow() {
  setWindowTitle("Sudoku");
  setFixedSize(800, 600);

  createSudokuBoard();
  createNumberBoard();
  createWidgets();
  createLayout();

  connect(radio_button_group, &QButtonGroup::buttonClicked, this,
          onNumberChanged);
  connect(clear_sudoku, &QPushButton::clicked, this, clearSudoku);
  connect(solve_sudoku, &QPushButton::clicked, this, solveSudoku);
}

void MainWindow::createSudokuBoard() {
  push_button_group = new QButtonGroup{this};

  sudoku_layout = new QGridLayout{};
  for (int i = 0; i != 9; ++i) {
    for (int j = 0; j != 9; ++j) {
      QPushButton *new_button = new QPushButton{this};
      new_button->setFixedSize(50, 50);
      sudoku_layout->addWidget(new_button, i, j);
      connect(new_button, &QPushButton::clicked, this, [this, new_button]() {
        new_button->setText(tr("%1").arg(current_number));
      });
      push_button_group->addButton(new_button);
    }
  }
}

void MainWindow::createNumberBoard() {
  radio_button_group = new QButtonGroup{this};
  radio_button_group->setExclusive(true);

  number_layout = new QGridLayout{};
  for (int i = 0; i != 5; ++i) {
    for (int j = 0; j != 2; ++j) {
      QPushButton *new_button =
          new QPushButton{tr("%1").arg((2 * i + j + 1) % 10), this};
      new_button->setCheckable(true);
      number_layout->addWidget(new_button, i, j);
      radio_button_group->addButton(new_button);
      radio_button_group->setId(new_button, (2 * i + j + 1) % 10);
    }
  }
}

void MainWindow::createWidgets() {
  clear_sudoku = new QPushButton{"Clear", this};
  solve_sudoku = new QPushButton{"Solve", this};

  central_widget = new QWidget{this};
  setCentralWidget(central_widget);
}

void MainWindow::createLayout() {
  QHBoxLayout *h_layout = new QHBoxLayout{};
  h_layout->addLayout(sudoku_layout);
  QVBoxLayout *v_layout = new QVBoxLayout{};
  v_layout->addLayout(number_layout);
  v_layout->addWidget(clear_sudoku);
  v_layout->addWidget(solve_sudoku);
  h_layout->addLayout(v_layout);

  central_widget->setLayout(h_layout);
}

void MainWindow::onNumberChanged() {
  current_number = radio_button_group->checkedId();
}

void MainWindow::clearSudoku() {
  for (auto &button : push_button_group->buttons()) {
    button->setText("");
  }
}

void MainWindow::solveSudoku() {
  std::vector<std::vector<int>> sudoku_board{};
  std::vector<int> vect{};
  for (auto &button : push_button_group->buttons()) {
    vect.push_back(button->text().toInt());
    if (vect.size() == 9) {
      sudoku_board.push_back(vect);
      vect.clear();
    }
  }

  for (const auto &vect : sudoku_board) {
    qInfo() << vect;
  }
}
