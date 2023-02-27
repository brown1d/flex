/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   messageAlphaSignature.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

MessageAlphaSignature::MessageAlphaSignature(uint32_t signature, string message) {
  if (message.size() != 2) {
    throw std::invalid_argument("Alphanumeric Message Signature: 2 chars required.");
  }

  if (signature <= 0x7f) {
    this->signature = signature;
    this->message = message;
  } else {
    throw std::invalid_argument("Alphanumeric Message Signature: Invalid Parameter.");
  }

}

uint32_t MessageAlphaSignature::getCodeword() {
  uint32_t cw = 0x0;

  const char* c = this->message.c_str();

  cw |= this->signature;
  cw |= ((uint32_t) c[0] & 0x7f) << 7;
  cw |= ((uint32_t) c[1] & 0x7f) << 14;

  cw = applyBchAndParity(cw);
  
  return cw;
  
}
