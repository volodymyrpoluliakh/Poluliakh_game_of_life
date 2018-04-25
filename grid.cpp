#include "grid.h"
#include "common.h"


Grid::Grid():
  InputHandler(),
  m_n(0),
  m_generation(0),
  m_gridTable(DEFAULT_ARRAY())
{}

Grid::~Grid() {}

bool Grid::init() {
  reset();
  printToFile(NEW_GAME_FILE);
  std::cin.get();
  bool isInited = readFromFile(NEW_GAME_FILE);
  if (!isInited) {
      std::cout << "Initializitaion failed. Press 'n' or 'N' to restart\n";
    }
  return isInited;
}

void Grid::reset() {
  std::fill(m_gridTable.begin(), m_gridTable.end(), DEFAULT_STRING());
}

bool Grid::printToFile(std::string pathToFile) {
  std::ofstream out;
  out.open(pathToFile, std::ios::trunc);
  std::ofstream outInit;
  outInit.open(pathToFile);
  if(!outInit.is_open()) {
      std::cout << "file " << pathToFile << " hadn`t been opened\n";
      return false;
    }
  for (auto&& it : m_gridTable) {
      out << it << '\n';
    }
  out.close();
  return true;
}

bool Grid::readFromFile(std::string pathToFile) {
  std::ifstream input;
  input.open(pathToFile);
  if (!input.is_open()) {
      std::cout << "file " << pathToFile << " hadn`t been opened\n";
      return false;
    }

  int i = 0;
  std::string line("");
  while(!input.eof() && i < DEFAULT_HEIGHT) {
      std::getline(input, line);
      format(line);
      m_gridTable[i] = line;
      i++;
    }
  input.close();

  if (i < DEFAULT_HEIGHT) {
      std::string defaultString = DEFAULT_STRING();
      for (std::array< std::string, DEFAULT_HEIGHT >::iterator it = m_gridTable.begin() + i; it != m_gridTable.end(); it++) {
          *it = defaultString;
        }
    }
  return true;
}

void Grid::show() {
  std::cout << INFO_STR;
  std::cout << "population: " << m_n << " generation: " << m_generation << '\n';
  for (auto&& it : m_gridTable) {
      std::cout << it << '\n';
    }
}

void Grid::update(const std::vector<int>& vecDeltas) {
  for (std::vector<int>::const_iterator it = vecDeltas.begin(); it != vecDeltas.end(); it++) {
      char& cell = m_gridTable[*it / DEFAULT_WIDTH][*it % DEFAULT_WIDTH];
      if (cell == DOT) {
          cell = SHARP;
        }
      else {
          cell = DOT;
        }
    }
}

