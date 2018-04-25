#ifndef GRID_H
#define GRID_H

#include "constants.h"
#include "inputhandler.h"
#include "common.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>

class Grid : public InputHandler
{
protected:
  int m_n;
  long long m_generation;
  std::array<std::string, DEFAULT_HEIGHT> m_gridTable;

public:
  Grid();
  ~Grid();

  void update(const std::vector<int>& delta);
  virtual void reset();
  bool init();

  void show();
  bool printToFile(std::string pathToFile);
  bool readFromFile(std::string pathToFile);
};

#endif // GRID_H
