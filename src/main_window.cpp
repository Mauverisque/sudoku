#include "main_window.h"
#include "sudoku_solver_logic.h"

MainWindow::MainWindow() {
  setWindowTitle("Sudoku");
  setFixedSize(800, 600);

  createSudokuBoard();
  createNumberBoard();
  createWidgets();
  createLayout();

  connect(sudoku_group, SIGNAL(idClicked(int)), this,
          SLOT(onSudokuCellChanged(int)));
  connect(number_group, &QButtonGroup::buttonClicked, this, onNumberChanged);
  connect(clear_sudoku, &QPushButton::clicked, this, clearSudoku);
  connect(solve_sudoku, &QPushButton::clicked, this, solveSudoku);
  connect(this, SIGNAL(keyPressed(const int &)), this,
          SLOT(onKeyPressed(const int &)));
}

void MainWindow::onKeyPressed(const int &num) {
  number_group->button(num)->click();
}

void MainWindow::onSudokuCellChanged(int id) {
  m_sudoku_board[id / 9][id % 9] = m_current_number;
  updateSudoku();
}

void MainWindow::onNumberChanged() {
  m_current_number = number_group->checkedId();
}

void MainWindow::onProgressUpdated() { progress->update(); }

void MainWindow::createSudokuBoard() {
  m_sudoku_board.resize(9);
  for (std::vector<int> &vect : m_sudoku_board) {
    vect.resize(9, 0);
  }

  sudoku_group = new QButtonGroup{this};

  sudoku_layout = new QGridLayout{};
  for (int row = 0; row != 9; ++row) {
    for (int col = 0; col != 9; ++col) {
      QPushButton *new_button = new QPushButton{this};
      new_button->setFixedSize(50, 50);
      new_button->setFont(QFont("Helvetica", 20));
      new_button->setStyleSheet(getButtonStyle(row, col));

      sudoku_group->addButton(new_button);
      sudoku_group->setId(new_button, row * 9 + col);

      sudoku_layout->addWidget(new_button, row, col);

      connect(new_button, &QPushButton::clicked, this, [this, new_button]() {
        (m_current_number == 0)
            ? (new_button->setText(""))
            : (new_button->setText(tr("%1").arg(m_current_number)));
      });
    }
  }
  updateSudoku();
}

void MainWindow::createNumberBoard() {
  number_group = new QButtonGroup{this};
  number_group->setExclusive(true);

  number_layout = new QGridLayout{};
  for (int i = 0; i != 5; ++i) {
    for (int j = 0; j != 2; ++j) {
      QPushButton *new_button =
          new QPushButton{tr("%1").arg(2 * i + j + 1), this};
      if (i + j == 5) {
        new_button->setText("");
      }
      new_button->setCheckable(true);

      number_group->addButton(new_button);
      number_group->setId(new_button, (2 * i + j + 1) % 10);

      number_layout->addWidget(new_button, i, j);
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

void MainWindow::createPopup(const QString &window_title, const QString &text,
                             const QMessageBox::Icon icon) {
  QMessageBox message_box{this};
  message_box.setWindowTitle(window_title);
  message_box.setText(text);
  message_box.setIcon(icon);
  message_box.setStandardButtons(QMessageBox::Ok);
  message_box.setDefaultButton(QMessageBox::Ok);
  message_box.exec();
}

void MainWindow::updateSudoku() {
  for (int row = 0; row != 9; ++row) {
    for (int col = 0; col != 9; ++col) {
      QAbstractButton *button{sudoku_group->button(row * 9 + col)};
      if (m_sudoku_board[row][col] != 0) {
        button->setText(tr("%1").arg(m_sudoku_board[row][col]));
      } else {
        button->setText("");
      }
      button->setStyleSheet(getButtonStyle(row, col));
    }
  }
  if (getAllInvalidCells(m_sudoku_board).size() != 0) {
    for (const auto &[row, col] : getAllInvalidCells(m_sudoku_board)) {
      int button_id = row * 9 + col;
      sudoku_group->button(button_id)->setStyleSheet(
          QString("background-color: red; color: white"));
    }
  }
}

void MainWindow::clearSudoku() {
  for (auto &vect : m_sudoku_board) {
    for (auto &elem : vect) {
      elem = 0;
    }
  }
  updateSudoku();
}

void MainWindow::solveSudoku() {
  if (getAllInvalidCells(m_sudoku_board).size() != 0) {
    createPopup("Incorrect Sudoku", "Your Sudoku is filled incorrectly!",
                QMessageBox::Icon::Critical);
  } else {
    progress = new QProgressDialog("Solving Sudoku...", "", 0, 100, this);
    progress->setWindowModality(Qt::WindowModal);
    progress->setCancelButton(nullptr);
    bool finished{solve(m_sudoku_board)};
    progress->cancel();
    if (!finished) {
      createPopup("No Solutions Found",
                  "No solutions for this sudoku could be found.",
                  QMessageBox::Icon::NoIcon);
    }
  }
  updateSudoku();
}

QString MainWindow::getButtonStyle(const int row, const int col) {
  QString style{"background-color: white; color: black"};
  if (row + col >= 3 && row + col <= 13) {
    if ((row >= 3 || col >= 3) && (row <= 5 || col <= 5) &&
        (row >= 3 || col <= 5) && (row <= 5 || col >= 3)) {
      style = "background-color: gray; color: white";
    }
    if ((row >= 3 && col >= 3) && (row <= 5 && col <= 5)) {
      style = "background-color: white; color: black";
    }
  }

  return style;
}
