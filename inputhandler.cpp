#include "inputhandler.h"
#include "constants.h"
#include <iostream>

InputHandler::InputHandler():
  m_state(DEFAULT),
  m_isStateChanged(false)
{}

InputHandler::~InputHandler()
{}

bool InputHandler::handleTap(){
  if (_kbhit()) {
      switch (_getch()) {
        case 'p':
        case 'P':
          m_state = PAUSE;
          return true;
          break;
        case 'e':
        case 'E':
          m_state = EXIT;
          return true;
          break;
        default:
          return false;
          break;
        }
    }
  return false;
}

void InputHandler::handlePause() {
  while (true) {
      switch (_getch()) {
        case 'g':
        case 'G':
          m_state = GAME;
          m_isStateChanged = true;
          return;
          break;
        case 't':
        case 'T':
          m_state = TEST;
          m_isStateChanged = true;
          return;
          break;
        case 'e':
        case 'E':
          m_state = EXIT;
          m_isStateChanged = true;
          return;
          break;
        case 'p':
        case 'P':
        case 'c':
        case 'C':
          m_state = CONTINUE;
          m_isStateChanged = false;
          return;
          break;
        default:
          std::cout << WRONG_COMMAND_STR;
          break;
        }
    }
}
