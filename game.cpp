#include "game.h"
#include "bitcounters.h"

Game::Game()
  : Grid(),
    m_cellTable1(new std::array<uint64_t, DEFAULT_LOGIC_SIZE>{}),
    m_cellTable2(new std::array<uint64_t, DEFAULT_LOGIC_SIZE>{})
{}

Game::~Game(){}

void Game::reset() {
  Grid::reset();
  std::fill((*m_cellTable1).begin(), (*m_cellTable1).end(), 0);
  std::fill((*m_cellTable2).begin(), (*m_cellTable2).end(), 0);
}

void Game::play() {
  while(m_state != EXIT) {
      m_isStateChanged = false;
      switch (m_state) {
        case DEFAULT:
          setup();
          break;
        case GAME:
          newGame();
          break;
        case TEST:
          test();
          break;
        default:
          break;
        }
    }
  return;
}

void Game::setup() {
  std::cout << GREETING_STR;
  std::cout << MENU_STR;
  handlePause();
}

void Game::newGame() {
  system("cls");
  m_isStateChanged = false;
  reset();
  std::cout << INFO_STR << '\n';
  std::cout << NEW_GAME_STR;
  Grid::init();
  adjustCellTable();
  while (m_state == GAME) {
      nextGeneration();
      if ((m_state == GAME && m_isStateChanged) || m_state == EXIT) {
          m_isStateChanged = false;
          return;
        }
      if (m_state == CONTINUE) {
          m_state = GAME;
          m_isStateChanged = false;
        }
    }
  return;
}

void Game::test() {
  system("cls");
  std::cout << INFO_STR;
  bool result;
  reset();
  //test of countPopulation() and adjustCellTable() (empty array)
  m_gridTable = []() -> def_arr_t {
      def_arr_t arr;
      std::string str("");
      for (int i = 0; i < DEFAULT_WIDTH; i++) str += DOT;
      for (auto&& it : arr) {
          it = str;
        }
      return arr;
    }();
  adjustCellTable();
  countPopulation();
  result = (m_n == 0);
  std::cout << "Result of testing empty array: " << result << '\n';
  reset();

  //test of countPopulation(), adjustCellTable() and update() (10 alive cells)
  srand(clock());
  std::vector<int> vecRand;
  int buf;
  while (vecRand.size() < 10) {
      buf = rand();
      buf %= DEFAULT_HEIGHT * DEFAULT_WIDTH;
      for (auto&& it : vecRand) {
          if (it == buf) continue;
        }
      vecRand.emplace_back(buf);
    }
  Grid::update(vecRand);
  adjustCellTable();
  countPopulation();
  result = (m_n == 10);
  std::cout << "Result of testing array with 10 alive cells: " << result << '\n';

  //test of countPopulation() and adjustCellTable() (full array)
  std::string fullStr("");
  for (int i = 0; i < DEFAULT_WIDTH; i++) fullStr += SHARP;
  for (auto&& it : m_gridTable) it = fullStr;
  adjustCellTable();
  countPopulation();
  result = (m_n == DEFAULT_HEIGHT * DEFAULT_WIDTH);
  std::cout << "Result of testing full array: " << result << '\n';

  m_state = DEFAULT;
}

void Game::nextGeneration() {
  clock_t start = clock();
  show();
  update();
  while (clock() - start <= DEFAULT_DELAY) {
      if(handleTap()) {
          std::cout << INFO_STR;
          handlePause();
        }
      if(m_state == EXIT || (m_state == GAME && m_isStateChanged)) return;
    }
  system("cls");
}

void Game::adjustCellTable() {
  int row = 0, column = 0;
  for (def_arr_t::const_iterator it = m_gridTable.begin(); it != m_gridTable.end(); it++) {
      uint64_t& firstUintRow = (*m_cellTable1)[row * 2];
      uint64_t& secondUintRow = (*m_cellTable1)[row * 2+1];
      for(std::string::const_iterator jt = (*it).begin(); jt != (*it).end(); jt++) {
          if (*jt == '#') {
              if (column < 64) {
                  firstUintRow |= (ONE << (63 - column));
                }
              else {
                  secondUintRow |= (ONE << (127 - column));
                }
            }
          ++column;
        }
      column = 0;
      ++row;
    }
}

void Game::findBorderRowDelta(int row, std::vector<int>* vecRowDelta) {
  uint64_t& firstUintNewRow = row == 0 ? (*m_cellTable2)[0] : (*m_cellTable2)[128];
  uint64_t& firstRowFirstUint =  row == 0 ? (*m_cellTable1)[0] : (*m_cellTable1)[128];
  uint64_t& secondRowFirstUint = row == 0 ? (*m_cellTable1)[2] : (*m_cellTable1)[126];
  uint8_t countBits = 0;
  COUNT_HEAD_BITS_FIRST_UINT_BORDER_ROW(countBits,
                                        firstRowFirstUint,
                                        secondRowFirstUint)
  CHECK_PUT_BIT(countBits, firstUintNewRow, firstRowFirstUint, 0)
  countBits = 0;

  for (int i = 1; i < 63; i++) {
      COUNT_MID_BITS_UINT_BORDER_ROW(countBits,
                                     firstRowFirstUint,
                                     secondRowFirstUint, i)
      CHECK_PUT_BIT(countBits, firstUintNewRow, firstRowFirstUint, i)
      countBits = 0;
    }

  uint64_t& secondUintNewRow = row == 0 ? (*m_cellTable2)[1] : (*m_cellTable2)[129];
  uint64_t& firstRowSecondUint =  row == 0 ? (*m_cellTable1)[1] : (*m_cellTable1)[129];
  uint64_t& secondRowSecondUint = row == 0 ? (*m_cellTable1)[3] : (*m_cellTable1)[127];

  COUNT_BACK_BITS_FIRST_UINT_BORDER_ROW(countBits,
                                        firstRowFirstUint, firstRowSecondUint,
                                        secondRowFirstUint, secondRowSecondUint)
  CHECK_PUT_BIT(countBits, firstUintNewRow, firstRowFirstUint, 63)
  countBits = 0;

  COUNT_HEAD_BITS_SECOND_UINT_BORDER_ROW(countBits,
                                         firstRowFirstUint, firstRowSecondUint,
                                         secondRowFirstUint, secondRowSecondUint)
  CHECK_PUT_BIT(countBits, secondUintNewRow, firstRowSecondUint, 0)
  countBits = 0;

  for (int i = 0; i < 63; i++) {
      COUNT_MID_BITS_UINT_BORDER_ROW(countBits,
                                     firstRowSecondUint,
                                     secondRowSecondUint, i)
      CHECK_PUT_BIT(countBits, secondUintNewRow, firstRowSecondUint, i)
      countBits = 0;
    }

  COUNT_BACK_BITS_SECOND_UINT_BORDER_ROW(countBits,
                                         firstRowSecondUint,
                                         secondRowSecondUint)
  CHECK_PUT_BIT(countBits, secondUintNewRow, firstRowSecondUint, 63)

  uint64_t deltaFirstUint = firstUintNewRow ^ firstRowFirstUint;
  uint64_t deltaSecondUint = secondUintNewRow ^ firstRowSecondUint;
  for (int i = 63; i >= 0; i--) {
      if((deltaFirstUint >> i) & 1) {
          vecRowDelta->emplace_back(row * DEFAULT_WIDTH + (63 - i));
        }
    }
  for (int i = 63; i >= 0; i--) {
      if((deltaSecondUint >> i) & 1) {
          vecRowDelta->emplace_back(row * DEFAULT_WIDTH + (127 - i));
        }
    }
}

void Game::findMidRowDelta(int row, std::vector<int>* vecRowDelta) {
  uint64_t& firstUintNewRow = (*m_cellTable2)[row * 2];
  uint64_t& firstRowFirstUint = (*m_cellTable1)[row*2 - 2];
  uint64_t& secondRowFirstUint = (*m_cellTable1)[row * 2];
  uint64_t& thirdRowFirstUint = (*m_cellTable1)[row * 2 + 2];

  uint8_t countBits = 0;

  COUNT_HEAD_BITS_FIRST_UINT_MID_ROW(countBits,
                                     firstRowFirstUint,
                                     secondRowFirstUint,
                                     thirdRowFirstUint)
  CHECK_PUT_BIT(countBits, firstUintNewRow, secondRowFirstUint, 0)
  countBits = 0;

  for (int i = 1; i < 63; i++) {
      COUNT_MID_BITS_UINT_MID_ROW(countBits,
                                  firstRowFirstUint,
                                  secondRowFirstUint,
                                  thirdRowFirstUint, i)
      CHECK_PUT_BIT(countBits, firstUintNewRow, secondRowFirstUint, i)
      countBits = 0;
    }
  uint64_t& secondUintNewRow = (*m_cellTable2)[row * 2 + 1];
  uint64_t& firstRowSecondUint = (*m_cellTable1)[row*2 - 1];
  uint64_t& secondRowSecondUint = (*m_cellTable1)[row * 2 + 1];
  uint64_t& thirdRowSecondUint = (*m_cellTable1)[row * 2 + 3];

  COUNT_BACK_BITS_FIRST_UINT_MID_ROW(countBits,
                                     firstRowFirstUint, firstRowSecondUint,
                                     secondRowFirstUint, secondRowSecondUint,
                                     thirdRowFirstUint, thirdRowSecondUint)
  CHECK_PUT_BIT(countBits, firstUintNewRow, secondRowFirstUint, 63)
  countBits = 0;

  COUNT_HEAD_BITS_SECOND_UINT_MID_ROW(countBits,
                                      firstRowFirstUint, firstRowSecondUint,
                                      secondRowFirstUint, secondRowSecondUint,
                                      thirdRowFirstUint, thirdRowSecondUint)
  CHECK_PUT_BIT(countBits, secondUintNewRow, secondRowSecondUint, 0)
  if(row == 22) std::cout << (int)countBits << " " << secondRowSecondUint << " " << secondRowFirstUint;
  countBits = 0;

  for (int i = 1; i < 63; i++) {
      COUNT_MID_BITS_UINT_MID_ROW(countBits,
                                  firstRowSecondUint,
                                  secondRowSecondUint,
                                  thirdRowSecondUint, i)
      CHECK_PUT_BIT(countBits, secondUintNewRow, secondRowSecondUint, i)
      countBits = 0;
    }

  COUNT_BACK_BITS_SECOND_UINT_MID_ROW(countBits,
                                      firstRowSecondUint,
                                      secondRowSecondUint,
                                      thirdRowSecondUint)
  CHECK_PUT_BIT(countBits, secondUintNewRow, secondRowSecondUint, 63)

  uint64_t deltaFirstUint = firstUintNewRow ^ secondRowFirstUint;
  uint64_t deltaSecondUint = secondUintNewRow ^ secondRowSecondUint;

  for (int i = 63; i >= 0; i--) {
      if((deltaFirstUint >> i) & 1) {
          vecRowDelta->emplace_back(row * DEFAULT_WIDTH + (63 - i));
        }
    }
  for (int i = 63; i >= 0; i--) {
      if((deltaSecondUint >> i) & 1) {
          vecRowDelta->emplace_back(row * DEFAULT_WIDTH + (127 - i));
        }
    }
}

void Game::findRowDelta(int row, std::vector<int>* vecRowDelta) {
  if (row == 0 || (row == (DEFAULT_HEIGHT - 1))) {
      findBorderRowDelta(row, vecRowDelta);
      return;
    }
  findMidRowDelta(row, vecRowDelta);
}

void Game::countPopulation() {
  m_n = 0;
  std::for_each(m_cellTable1->begin(), m_cellTable1->end(), [this](uint64_t cells) {
    for (int i = 0; i < 64; i++) {
        m_n += (cells >> i) & 1;
      }
  });
}

void Game::update() {
  std::vector<int>* arrVecDeltas = new std::vector<int> [DEFAULT_HEIGHT]{};
//  for (int i = 0; i < 65 ; i++) {
//      findRowDelta(i, &arrVecDeltas[i]);
//      Grid::update(arrVecDeltas[i]);
//    }

    for (int i = 0; i < DEFAULT_HEIGHT / 5; i++) {
      std::thread t1(&findRowDelta, this, i, &arrVecDeltas[i]);
      std::thread t2(&findRowDelta, this, i + 13, &arrVecDeltas[i + 13]);
      std::thread t3(&findRowDelta, this, i + 26, &arrVecDeltas[i + 26]);
      std::thread t4(&findRowDelta, this, i + 39, &arrVecDeltas[i + 39]);
      std::thread t5(&findRowDelta, this, i + 52, &arrVecDeltas[i + 52]);
      if (t1.joinable()) t1.join();
      if (t2.joinable()) t2.join();
      if (t3.joinable()) t3.join();
      if (t4.joinable()) t4.join();
      if (t5.joinable()) t5.join();
    }

  std::vector<std::thread> vecThreads;
  for (int i = 0; i < DEFAULT_HEIGHT; i++) {
      if (arrVecDeltas[i].size() != 0) {
          std::thread thr(&Grid::update, this, arrVecDeltas[i]);
          vecThreads.emplace_back(std::move(thr));
        }
    }
  for (auto&& it_t : vecThreads) {
      if (it_t.joinable()) it_t.join();
    }

  m_cellTable1.swap(m_cellTable2);
  countPopulation();
  m_generation++;

  std::fill((*m_cellTable2).begin(), (*m_cellTable2).end(), 0);
  delete [] arrVecDeltas;
}

//void Game::loadedGame() {
//  load();
//  m_previousState = m_state;

//}

//void Game::verify() {
//  //first part of verification
//  //checking number of population

//  for (auto&& it : m_gridTable) {
//      for (auto&& jt : it) {

//        }
//    }
//  int row = 0, column = 0;
//  for (auto&& it : m_gridTable) {
//      uint64_t& firstUintRow = (*m_cellTable1)[row * 2];
//      uint64_t& secondUintRow = (*m_cellTable1)[row * 2+1];
//      for ()
//    }
//}

//void Game::save() {
//  printToFile(SAVE_FILE);
//  std::ofstream out;
//  out.open(SAVE_FILE, std::ios::app);

//  for (auto&& it : (*m_cellTable1)) {
//      out << it << '\n';
//    }

//  out.close();
//  m_state = m_previousState;
//}

//bool Game::load() {
//  m_state = LOAD;
//  m_isStateChanged = true;
//  m_gridTable = DEFAULT_ARRAY();
//  std::fill((*m_cellTable2).begin(), (*m_cellTable2).end(), 0);
//  std::fill((*m_cellTable2).begin(), (*m_cellTable2).end(), 0);

//  std::ifstream in;
//  in.open(SAVE_FILE);
//  if (!in.is_open()) {
//      std::cout << LOAD_FAIL_STR;
//      m_state = GAME;
//      return false;
//    }

//  readFromFile(SAVE_FILE);
//  std::string buf;
//  for (auto&& it : (*m_cellTable1)) {
//      std::getline(in, buf);
//      for (auto&& jt : buf) {
//          if (!isdigit(jt)) {
//              std::cout << LOAD_FAIL_STR;
//              m_state = GAME;
//              return false;
//            }
//        }
//      it = std::stoull(buf);
//    }
//  return true;
//}
