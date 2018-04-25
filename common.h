#ifndef COMMON_H
#define COMMON_H

#include "constants.h"

#include <functional>
#include <iostream>

std::string DEFAULT_STRING();
std::string DEFAULT_FULL_STRING();
def_arr_t DEFAULT_ARRAY();
def_arr_t DEFAULT_FULL_ARRAY();

void format(std::string& str);

#endif // COMMON_H
