/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   frame.hh
 *
 * Frame class
 */

#include "message.hh"

#ifndef FRAME_H
#define FRAME_H

const uint32_t PATTERN_BCS1 = 0x55555555;
const uint32_t PATTERN_A1 = 0x9C9ACF1E;
const uint32_t PATTERN_B = 0xAAAA;
const uint32_t PATTERN_BS2 = 0x05;
const uint32_t PATTERN_C = 0x21B7;

const uint32_t MAX_CODEWORDS_PER_BLOCK_1600 = 88;

class Frame {
private:
  FrameInformationWord fiw;
  bool sendTime;
  uint32_t numCws;
  vector<Message> messages;
  
public:
  Frame(uint32_t cycleNumber, uint32_t frameNumber);
  uint32_t addMessage(Message message);
  uint32_t spaceLeft();
  calculateCycleAndFrame(uint32_t minutes, uint32_t seconds);

private:
  vector<uint8_t> getSync1();
  vector<uint8_t> getHeader();
  vector<uint8_t> getBytes();
}
  
  
#endif
