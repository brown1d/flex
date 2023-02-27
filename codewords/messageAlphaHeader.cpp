/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   messageAlphaHeader.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

MessageAlphaHeader::MessageAlphaHeader(uint32_t messageContinuedFlag, uint32_t fragmentNumber, uint32_t messageNumber, uint32_t retrievalFlag, uint32_t mailDropFlag) {
  if (messageContinuedFlag <= 1 && fragmentNumber <= 3 && messageNumber <= 63 && retrievalFlag <= 1 && mailDropFlag <= 1) {
    this->messageContinuedFlag = messageContinuedFlag;
    this->fragmentNumber = fragmentNumber;
    this->messageNumber = messageNumber;
    this->retrievalFlag = retrievalFlag;
    this->mailDropFlag = mailDropFlag;
  } else {
    throw std::invalid_argument("Alphanumeric Message Header: Invalid Parameter.");
  }

}

uint32_t MessageAlphaHeader::getCodeword() {
  uint32_t cw = 0x0;

  cw |= this->messageContinuedFlag << 10;
  cw |= this->fragmentNumber << 11;
  cw |= this->messageNumber << 13;
  cw |= this->retrievalFlag << 19;
  cw |= this->mailDropFlag << 20;

  cw = applyBchAndParity(cw);
  
  return cw;
  
}
