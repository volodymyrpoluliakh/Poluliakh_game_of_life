#ifndef BITCOUNTERS_H
#define BITCOUNTERS_H

#include "constants.h"

#define CHECK_PUT_BIT(countBits, newRowUint, currentRowUint , i) \
  if (countBits == 3)  newRowUint |= ONE << (63 - i); \
  if (countBits == 2)  newRowUint |= currentRowUint & (ONE << (63 - i));

//BORDER ROW
#define COUNT_MID_BITS_UINT_BORDER_ROW(countBits, uintFirstRow, uintSecondRow, i) \
  countBits += ((uintSecondRow >> (63 - i)) & 1); \
  countBits += ((uintSecondRow >> (62 - i)) & 1); \
  countBits += ((uintSecondRow >> (64 - i)) & 1); \
  countBits += ((uintFirstRow >> (64 - i)) & 1); \
  countBits += ((uintFirstRow >> (62 - i)) & 1);

#define COUNT_HEAD_BITS_FIRST_UINT_BORDER_ROW(countBits, firstRowUint, secondRowUint) \
  countBits += ((firstRowUint >> 62) & 1); \
  countBits += ((secondRowUint >> 63) & 1); \
  countBits += ((secondRowUint >> 62) & 1);

#define COUNT_BACK_BITS_FIRST_UINT_BORDER_ROW(countBits, firstRowFirstUint, firstRowSecondUint, secondRowFirstUint, secondRowSecondUint) \
  countBits += (firstRowFirstUint >> 1) & 1; \
  countBits += (firstRowSecondUint >> 63) & 1; \
  countBits += (secondRowFirstUint >> 1) & 1; \
  countBits += secondRowFirstUint & 1; \
  countBits += (secondRowSecondUint >> 63) & 1;

#define COUNT_BACK_BITS_SECOND_UINT_BORDER_ROW(countBits, firstRowUint, secondRowUint) \
  countBits += (firstRowUint >> 1) & 1; \
  countBits += secondRowUint & 1; \
  countBits += (secondRowUint >> 1) & 1;

#define COUNT_HEAD_BITS_SECOND_UINT_BORDER_ROW(countBits, firstRowFirstUint, firstRowSecondUint, secondRowFirstUint, secondRowSecondUint) \
  countBits += firstRowFirstUint & 1; \
  countBits += secondRowFirstUint & 1; \
  countBits += (secondRowSecondUint >> 63) & 1; \
  countBits += (secondRowSecondUint >> 62) & 1; \
  countBits += (firstRowSecondUint >> 62) & 1;

//MID ROW
#define COUNT_MID_BITS_UINT_MID_ROW(countBits, uintFirstRow, uintSecondRow, uintThirdRow, i) \
  countBits += ((uintFirstRow >> (63 - i)) & 1); \
  countBits += ((uintFirstRow >> (62 - i)) & 1); \
  countBits += ((uintFirstRow >> (64 - i)) & 1); \
  countBits += ((uintThirdRow >> (63 - i)) & 1); \
  countBits += ((uintThirdRow >> (62 - i)) & 1); \
  countBits += ((uintThirdRow >> (64 - i)) & 1); \
  countBits += ((uintSecondRow >> (64 - i)) & 1); \
  countBits += ((uintSecondRow >> (62 - i)) & 1);

#define COUNT_HEAD_BITS_FIRST_UINT_MID_ROW(countBits, uintFirstRow, uintSecondRow, uintThirdRow) \
  countBits += ((uintFirstRow >> 63) & 1); \
  countBits += ((uintFirstRow >> 62) & 1); \
  countBits += ((uintThirdRow >> 63) & 1); \
  countBits += ((uintThirdRow >> 62) & 1); \
  countBits += ((uintSecondRow >> 62) & 1);

#define COUNT_BACK_BITS_FIRST_UINT_MID_ROW(countBits, firstRowFirstUint, firstRowSecondUint, secondRowFirstUint, secondRowSecondUint, thirdRowFirstUint, thirdRowSecondUint) \
  countBits += (firstRowFirstUint >> 1) & 1; \
  countBits += (secondRowFirstUint >> 1) & 1; \
  countBits += (thirdRowFirstUint >> 1) & 1; \
  countBits += (firstRowSecondUint >> 63) & 1; \
  countBits += (secondRowSecondUint >> 63) & 1; \
  countBits += (thirdRowSecondUint >> 63) & 1; \
  countBits += firstRowFirstUint & 1; \
  countBits += thirdRowFirstUint & 1;

#define COUNT_HEAD_BITS_SECOND_UINT_MID_ROW(countBits, firstRowFirstUint, firstRowSecondUint, secondRowFirstUint, secondRowSecondUint, thirdRowFirstUint, thirdRowSecondUint) \
  countBits += firstRowFirstUint & 1; \
  countBits += secondRowFirstUint & 1; \
  countBits += thirdRowFirstUint & 1; \
  countBits += (firstRowSecondUint >> 63) & 1; \
  countBits += (firstRowSecondUint >> 62) & 1; \
  countBits += (thirdRowSecondUint >> 63) & 1; \
  countBits += (thirdRowSecondUint >> 62) & 1; \
  countBits += (secondRowSecondUint >> 62) & 1;

#define COUNT_BACK_BITS_SECOND_UINT_MID_ROW(countBits, uintFirstRow, uintSecondRow, uintThirdRow) \
  countBits += uintFirstRow & 1; \
  countBits += (uintFirstRow >> 1) & 1; \
  countBits += uintThirdRow & 1; \
  countBits += (uintThirdRow >> 1) & 1; \
  countBits += (uintSecondRow >> 1) & 1;

#endif // BITCOUNTERS_H
