#include "flex.h"
#include <iostream>
#include <stdexcept>

using namespace std;

class Message {
private:
  uint32_t frame;
  MessageType messageType;
  uint32_t capcode;
  string data;

public:
  Message(uint32_t frame, MessageType messageType, uint32_t capcode, string data) {  // Constructor
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

  uint32_t getNumberOfContentCodewords() {
    uint32_t size;
    size += 2;
    size += (this->data.size()-2)/3;
    if (((this->data.size()-2) % 3) > 0) {
      size += 1;
    }
    return size;
  }
      
private:
  CapcodeType getCapcodeType(uint32_t capcode) {
    if (capcode >= 0x0001 && capcode <= 0x1ea7ff) {
      return CapcodeType::ShortAddress;
    }
    return CapcodeType::Invalid;
  }
};

int main() {
  try {
    Message message(1, MessageType::AlphaNum, 1, "test1234");
    cout << message.getNumberOfContentCodewords() << endl;
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  
  return 0;
}

