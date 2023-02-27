/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   addressShort.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

AddressShort::AddressShort(uint32_t capCode) {
  if (capCode >= 0x0001 && capCode < 0x1ea7ff) {
    this->capCode = capCode;
  } else {
    throw std::invalid_argument("CAPCODE for short address out of range");
  }
}

uint32_t AddressShort::getCodeword() {
  uint32_t cw = 0x0;
  cw |= this->capCode + SHORT_ADDRESS_CAPCODE_OFFSET;

  cw = applyBchAndParity(cw);

  return cw;
}

	
