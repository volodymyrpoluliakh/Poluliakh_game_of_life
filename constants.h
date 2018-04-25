#ifndef CONSTANTS_H
#define CONSTANTS_H

//CONSTANTS
#include <cstdint>
#include <string>
#include <array>
#include <vector>
#include <time.h>
#include <stdint.h>

static const int DEFAULT_HEIGHT = 65;
static const int DEFAULT_WIDTH = 128;
static const int DEFAULT_LOGIC_SIZE = 130;

static const char DOT = '.';
static const char SHARP = '#';

static const uint64_t ONE = 1;
static const clock_t DEFAULT_DELAY = 2000;

using def_arr_t = std::array<std::string, DEFAULT_HEIGHT>;

//STRING
static const std::string LOAD_FAIL_STR = std::string("Loading failed. Started new game\n");
static const std::string WRONG_COMMAND_STR = std::string("Please, enter command correct\n");
static const std::string INFO_STR = std::string("To play the new Game tap 'G'. Test the Game tap 'T'. To Exit tap 'E'.  To Pause tap 'P'. To Continue tap 'C'\n");
static const std::string MENU_STR = std::string("To play the Game tap 'G'. Test the Game tap 'T'. To Exit tap 'E'. To Pause tap 'P'\n");
static const std::string GREETING_STR  = std::string("Welcome to \"Conway`s Game of Life\"\n");
static const std::string NEW_GAME_FILE = std::string("newgame.txt");
static const std::string SAVE_FILE = std::string("save.txt");
static const std::string NEW_GAME_STR = std::string("File newgametable.txt have been generated. Please enter alive cells into this file with symbol '#' and save it.\n(All other symbols will be interpreted as '.'(empty cell))\nPress \"Enter\" when you will be ready");

#endif // CONSTANTS_H
