#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <conio.h>

class InputHandler
{
public:
  int m_state;
  bool m_isStateChanged;
  enum states {DEFAULT, GAME, PAUSE, TEST, EXIT, CONTINUE};

  InputHandler();
  ~InputHandler();
  bool handleTap();
  void handlePause();
  virtual void setup() = 0;
};

#endif // INPUTHANDLER_H
