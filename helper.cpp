/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   helper.cpp
 *
 * Helper routines
 */

#include "flex.hh"
#include <iostream>
#include <stdexcept>

using namespace std;

// Declare private functions 
uint32_t countOnes(uint32_t codeword);
void setParity(uint32_t *codeword);
void clearParity(uint32_t *codeword);

uint32_t apply4bitChecksum(uint32_t codeword) {
  uint32_t sum = 0x0;
  sum += (codeword >> 4) & 0xf;
  sum += (codeword >> 8) & 0xf;
  sum += (codeword >> 12) & 0xf;
  sum += (codeword >> 16) & 0xf;
  sum += (codeword >> 20) & 0x1;

  sum ^= 0xf;
  sum &= 0xf;

  return codeword | sum;
}

uint32_t applyBchChecksum(uint32_t codeword) {
  uint32_t crc = codeword;
  for (int i = 0; i < 21; i++) {
    if ((crc & (0x00000001 << i)) != 0) {
	  crc ^= 0x4b7 << i;
    }
  }
  return codeword | crc;
}

uint32_t applyBchAndParity(uint32_t codeword) {
  uint32_t cw = codeword;
  cw = applyBchChecksum(cw);
  checkAndSetParity(&cw);
  return cw;
}

bool checkAndSetParity(uint32_t *codeword) {
  uint32_t ones = countOnes(*codeword);

  if ((ones % 2) != 0) {
    setParity(codeword);
    return true;
  } else {
    clearParity(codeword);
    return false;
  }
}

uint32_t countOnes(uint32_t codeword) {
  uint32_t ones = 0;
  for (int i=0; i < 31; i++) {
    uint32_t mask = 1 << i;
    ones += (codeword & mask) >> i;
  }
  return ones;
}

void setParity(uint32_t *codeword) {
  *codeword = *codeword | 0x80000000;
}

void clearParity(uint32_t *codeword) {
  *codeword = *codeword & 0x7FFFFFFF;
}


