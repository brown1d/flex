/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   vectorAlpha.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

// VectorAlpha Constructor
VectorAlpha::VectorAlpha(uint32_t messageStart, uint32_t messageWords) {
  if (messageStart >= 3 && messageStart <= 87 && messageWords >= 1 && messageWords <= 85) {
    this->messageStart = messageStart;
    this->messageWords = messageWords;
  } else {
    throw std::invalid_argument("Parameter out of range");
  }
}

uint32_t VectorAlpha::getCodeword() {
  uint32_t cw = 0x0;

  cw |= 0x5 << 4;   // Type: Alpha Messge Vector
  cw |= this->messageStart << 7;
  cw |= this->messageWords << 14;

  cw = apply4bitChecksum(cw);
  cw = applyBchAndParity(cw);

  return cw;
}
