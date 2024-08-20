#ifndef WINDOW_KEYBOARD_DETECT_H_
#define WINDOW_KEYBOARD_DETECT_H_

#include <QKeyEvent>
#include <QMainWindow>

class WindowKeyboardDetect : public QMainWindow {
  Q_OBJECT

public:
  explicit WindowKeyboardDetect(QObject *parent = nullptr);

signals:
  void keyPressed(const int &num);

protected:
  void keyPressEvent(QKeyEvent *event) override;
};

#endif // WINDOW_KEYBOARD_DETECT_H_
