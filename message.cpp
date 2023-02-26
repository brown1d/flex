/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   message.cpp
 *
 * Message Class
 */

#include "flex.hh"
#include "message.hh"

// Message contructor
Message::Message(uint32_t frame, MessageType messageType, uint32_t capcode, string data) {
    if (getCapcodeType(capcode) == CapcodeType::Invalid) {
      throw std::invalid_argument("Invalid CapCode");
    }
    
    if (frame > 128) {
      throw std::invalid_argument("Invalid Frame number"); 
    }
    this->frame = frame;
    this->messageType = messageType;
    this->capcode = capcode;
    this->data = data;
}

uint32_t Message::getNumberOfMessageCodewords() {
  uint32_t size = 0;

  switch (getCapcodeType(this->capcode)) {
  case CapcodeType::ShortAddress:
    size += 2;
    break;
  case CapcodeType:: Invalid:
    throw std::invalid_argument("Invalid Capcode");
    break;
  }

  switch (this->messageType) {
  case MessageType::AlphaNum:
    size += getNumberOfContentCodewords();
    break;
  }
  
  return size;
}

uint32_t Message::getNumberOfContentCodewords() {
    uint32_t size = 0;
    size += 2;
    size += (this->data.size()-2)/3;
    if (((this->data.size()-2) % 3) > 0) {
      size += 1;
    }
    return size;
  }
      
CapcodeType Message::getCapcodeType(uint32_t capcode) {
  if (capcode >= 0x0001 && capcode <= 0x1ea7ff) {
    return CapcodeType::ShortAddress;
  }
  return CapcodeType::Invalid;
}
