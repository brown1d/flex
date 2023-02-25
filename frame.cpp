/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   frame.cpp
 *
 * Frame routines
 */

#include "flex.h"
#include <iostream>
#include <stdexcept>

using namespace std;

const PATTERN_BCS1 0x55555555;
const PATTERN_A1 = 0x9C9ACF1E;
const PATTERN_B = 0xAAAA;
const PATTERN_BS2 = 0x05;
const PATTERN_C = 0x21B7;

const MAX_CODEWORDS_PER_BLOCK_1600 = 88;

class Frame {
private:
  FrameInformationWord fiw;
  bool sendTime;
  uint32_t numCws;
  vector<Message> messages;
  
public:
  Frame(uint32_t cycleNumber, uint32_t frameNumber) {
    this->fiw = FrameInformationWord(cycleNumber, frameHumber, 0, 00);

    this->numCws = 1;         // BIW1
    this->sendTime = false;

    if (frameNumber == 0) {
      this->sendTime = true;  // send BIW2, 3 and 4
      this->numCws = 3;
    }
  }

  uint32_t addMessage(Message message) {
    uint32_t sizeNewMsg = message.getNumberOfContentCodewords();

    if (sizeNewMsg < spaceLeft()) {
      this->messages.push_back(message);
      this->numCws += sizeNewMsg;
      return (this->numCws);
    }
    
    throw std::invalid_argument("Count not add message to frame")
  }
  
  uint32_t spaceLeft() {
    return MAX_CODEWORDS_PER_BLOCK_1600 - this->numCws;
  }

  calculateCycleAndFrame(uint32_t minutes, uint32_t seconds) {
    uint32_t minutes / 4;
    uint32_t frame = ((minutes % 4) * 60 + seconds) / 1.875;
  }

private:
  vector<uint8_t> getSync1() {
  }

  
  vector<uint8_t> getHeader() {
    vector<uint8_t> header;
    return header;
  }
  
  vector<uint8_t> getBytes() {
    vector<uint8_t> bytes;
    
    return bytes;
  }
}
  
  
