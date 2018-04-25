#include "common.h"

void format(std::string& str) {
  int deltaSize = str.length() - DEFAULT_WIDTH;
  if(deltaSize != 0) {
      if (deltaSize < 0) {
          for (; deltaSize < 0; deltaSize++) {
              str.push_back(DOT);
            }
        }
      if (deltaSize > 0) {
          str.erase(DEFAULT_WIDTH, deltaSize);
        }
    }
  for (auto&& it : str) {
      if (it != '.' && it != '#') {
          it = '.';
        }
    }
  return;
}

std::string DEFAULT_STRING() {
  std::string str("");
  for (int i = 0; i < DEFAULT_WIDTH; i++) {
      str.push_back(DOT);
    }
  return str;
}

std::string DEFAULT_FULL_STRING() {
  std::string str("");
  for (int i = 0; i < DEFAULT_WIDTH; i++) {
      str.push_back(SHARP);
    }
  return str;
}

def_arr_t DEFAULT_ARRAY() {
  def_arr_t arr;
  for (auto&& it : arr) {
      it = DEFAULT_STRING();
    }
  return arr;
}

def_arr_t DEFAULT_FULL_ARRAY() {
  def_arr_t arr;
  for (auto&& it : arr) {
      it = DEFAULT_FULL_STRING();
    }
  return arr;
}
