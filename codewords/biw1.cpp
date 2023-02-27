/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   biw1.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

// BIW1 Constructor
BIW1::BIW1(uint32_t priorityAddress, uint32_t endOfBlock, uint32_t vectorFieldStart, uint32_t carryOn, uint32_t frameIdCollapseMark) {
  this->priorityAddress = priorityAddress & 0xf;
  this->endOfBlock = endOfBlock & 0x3;
  this->vectorFieldStart = vectorFieldStart & 0x3f;
  this->carryOn = carryOn & 0x3;
  this->frameIdCollapseMark = frameIdCollapseMark & 0x7;
}

uint32_t BIW1::getCodeword() {
  uint32_t cw = 0x0;

  cw |= this->priorityAddress << 4;
  cw |= this->endOfBlock << 8;
  cw |= this->vectorFieldStart << 10;
  cw |= this->carryOn << 16;
  cw |= this->frameIdCollapseMark << 18;

  cw = apply4bitChecksum(cw);
  cw = applyBchAndParity(cw);

  return cw;
}
