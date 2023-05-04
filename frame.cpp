/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   frame.cpp
 *
 * Frame routines
 */

#include "flex.hh"
#include "blocks.hh"
#include "frame.hh"
#include "message.hh"

using namespace std;

Frame::Frame(uint32_t cycleNumber, uint32_t frameNumber) {
  this->fiw = FrameInformationWord(cycleNumber, frameNumber, 0, 0);
  
  this->numCws = 1;         // BIW1
  this->sendTime = false;
  
  if (frameNumber == 0) {
    this->sendTime = true;  // send BIW2, 3 and 4
    this->numCws = 3;
  }
}

vector<uint8_t> Frame::getSync1() {
  vector<uint8_t> sync1;
  uint8_t patternBS1[4] = { 0, 0, 0, 0};
  uint8_t patternA1[4] = { 0, 0, 0, 0};
  uint8_t patternB[2] = { 0, 0};
  
  u8from32(PATTERN_BS1, patternBS1);
  sync1.insert(sync1.end(), &patternBS1[0], &patternBS1[3]);
  u8from32(PATTERN_A1, patternA1);
  sync1.insert(sync1.end(), &patternA1[0], &patternA1[3]);
  u8from16(PATTERN_B, patternB);
  sync1.insert(sync1.end(), &patternB[0], &patternB[1]);
  u8from32(PATTERN_A1 ^ 0xFFFFFFFF, patternA1);
  sync1.insert(sync1.end(), &patternA1[0], &patternA1[3]);

  return sync1;
}

vector<uint8_t> Frame::getSync2() {
  vector<uint8_t> sync2;
  uint32_t tmp = 0x0;
  uint8_t u8tmp[4] = { 0, 0, 0, 0};

  tmp |= PATTERN_BS2 & 0X0f;
  tmp |= PATTERN_C << 4;
  tmp |= ((PATTERN_BS2 ^ 0x0f) & 0x0f) << 20;
  tmp |= ((PATTERN_C ^ 0xffff) & 0x0f) << 24;
  u8from32(tmp, u8tmp);
  sync2.insert(sync2.end(), &u8tmp[0], &u8tmp[3]);
  sync2.push_back((PATTERN_C ^ 0xffff) >> 8);
  return sync2;
}

vector<uint8_t> Frame::getHeader() {
  vector<uint8_t> header;
  vector<uint8_t> sync1 = getSync1();
  vector<uint8_t> sync2 = getSync2();
  uint8_t codeword[4] = {0, 0, 0, 0};
  u8from32(this->fiw.getCodeword(), codeword);

  header.insert(header.end(), sync1.begin(), sync1.end());
  header.insert(header.end(), &codeword[0], &codeword[3]);
  header.insert(header.end(), sync2.begin(), sync2.end());

  return header;
}

vector<uint8_t> Frame::getBytes() {
  vector<uint8_t> bytes;
  
  auto header = getHeader();
  bytes.insert(bytes.end(), header.begin(), header.end());
  auto blocks = Blocks::getBytes(this->messages, this->sendTime);
  bytes.insert(bytes.end(), blocks.begin(), blocks.end());
  
  return bytes;
}

uint32_t Frame::addMessage(Message message) {
  uint32_t sizeNewMsg = message.getNumberOfContentCodewords();

  if (sizeNewMsg < spaceLeft()) {
    this->messages.push_back(message);
    this->numCws += sizeNewMsg;
    return (this->numCws);
  }
  
  throw std::invalid_argument("Count not add message to frame");
}

uint32_t Frame::spaceLeft() {
  return MAX_CODEWORDS_PER_BLOCK_1600 - this->numCws;
}

tuple<uint32_t, uint32_t> Frame::calculateCycleAndFrame(uint32_t minutes, uint32_t seconds) {
  uint32_t cycle = minutes / 4;
  uint32_t frame = ((minutes % 4) * 60 + seconds) / 1.875;
  return make_tuple(cycle, frame);
}

void Frame::u8from32 (uint32_t u32, uint8_t* u8) {
  u8[3] = (uint8_t) u32;
  u8[2] = (uint8_t)(u32>>=8);
  u8[1] = (uint8_t)(u32>>=8);
  u8[0] = (uint8_t)(u32>>=8);
}

void Frame::u8from16 (uint16_t u16, uint8_t* u8) {
  u8[1] = (uint8_t)(u16>>=8);
  u8[0] = (uint8_t)(u16>>=8);
}
  
