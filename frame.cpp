/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   frame.cpp
 *
 * Frame routines
 */

#include "flex.hh"
#include "frame.h"
#include "message.h"

using namespace std;

Frame::Frame(uint32_t cycleNumber, uint32_t frameNumber) {
  this->fiw = FrameInformationWord(cycleNumber, frameHumber, 0, 00);
  
  this->numCws = 1;         // BIW1
  this->sendTime = false;
  
  if (frameNumber == 0) {
    this->sendTime = true;  // send BIW2, 3 and 4
    this->numCws = 3;
    }
}

uint32_t Frame::addMessage(Message message) {
  uint32_t sizeNewMsg = message.getNumberOfContentCodewords();

  if (sizeNewMsg < spaceLeft()) {
    this->messages.push_back(message);
    this->numCws += sizeNewMsg;
    return (this->numCws);
  }
  
  throw std::invalid_argument("Count not add message to frame")
  }

uint32_t Frame::spaceLeft() {
  return MAX_CODEWORDS_PER_BLOCK_1600 - this->numCws;
}

Frame::calculateCycleAndFrame(uint32_t minutes, uint32_t seconds) {
  uint32_t minutes / 4;
  uint32_t frame = ((minutes % 4) * 60 + seconds) / 1.875;
}

vector<uint8_t> Frame::getSync1() {
}


vector<uint8_t> Frame::getHeader() {
  vector<uint8_t> header;
  return header;
}

vector<uint8_t> Frame::getBytes() {
  vector<uint8_t> bytes;
  
  return bytes;
}
  
  
