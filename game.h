#ifndef GAME_H
#define GAME_H

#include "grid.h"

#include <thread>
#include <memory>
#include <time.h>
#include <cctype>

class Game : public Grid
{
  std::shared_ptr< std::array<uint64_t, DEFAULT_LOGIC_SIZE> >  m_cellTable1;
  std::shared_ptr< std::array<uint64_t, DEFAULT_LOGIC_SIZE> >  m_cellTable2;

public:
  Game();
  ~Game();
  virtual void setup() override;
  virtual void reset() override;
  void play();
  void newGame();
  void test();

  void update();
  void nextGeneration();
  void adjustCellTable();

  void findBorderRowDelta(int row, std::vector<int>* vecRowDelta);
  void findMidRowDelta(int row, std::vector<int>* vecRowDelta);
  void findRowDelta(int row, std::vector<int>* vecRowDelta);
  void countPopulation();

};

#endif // GAME_H
