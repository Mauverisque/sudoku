#include "window_keyboard_detect.h"

WindowKeyboardDetect::WindowKeyboardDetect(QObject *parent) {}

void WindowKeyboardDetect::keyPressEvent(QKeyEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) {
      emit keyPressed(event->key() - Qt::Key_0);
    }
  }
}
