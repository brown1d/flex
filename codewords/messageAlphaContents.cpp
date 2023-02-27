/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   messageAlphaContents.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

MessageAlphaContent::MessageAlphaContent(string message) {
  if (message.size() != 3) {
    throw std::invalid_argument("Alphanumeric Message Content: 3 characters required.");
  }

  this->message = message;
}

uint32_t MessageAlphaContent::getCodeword() {
  uint32_t cw = 0x0;

  const char* c = this->message.c_str();

  cw |= (uint32_t) c[0] & 0x7f;
  cw |= ((uint32_t) c[1] & 0x7f) << 7;
  cw |= ((uint32_t) c[2] & 0x7f) << 14;

  cw = applyBchAndParity(cw);
  
  return cw;
  
}

