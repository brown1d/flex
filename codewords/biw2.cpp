/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   biw2.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

// BIW2 Constructor
BIW2::BIW2(uint32_t localId, uint32_t timezone) {
  this->localId = localId & 0x01FF;
  this->timezone = timezone & 0x01F;
}

uint32_t BIW2::getCodeword() {
  uint32_t cw = 0x0;
  cw |= this->timezone << 7;
  cw |= this->localId << 12;

  cw = apply4bitChecksum(cw);
  cw = applyBchAndParity(cw);

  return cw;
}
