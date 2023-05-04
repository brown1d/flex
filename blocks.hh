/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   block.hh
 *
 * Block class
 */

#include "message.hh"
#include "codewords/codewords.hh"

#ifndef BLOCK_H
#define BLOCK_H

struct VectorAndContentCws {
  vector<uint32_t> vectorCws;
  vector<uint32_t> contentCws;
};
  
class Blocks {
public:
  static vector<uint8_t> getBytes(vector<Message> messages, bool sendTime);
private:
  static uint32_t countAddressCws(vector<Message> messages);
  static vector<uint32_t> getBiwCws(uint32_t amountAddresses, bool sendTime);
  static vector<uint32_t> getAddressCws(vector<Message> messages);
  static VectorAndContentCws getVectorAndContentCws(vector<Message> messages, uint32_t biwCwsSize, uint32_t addressCwsSize);
  static vector<uint32_t> fillUpBlock1600(vector<uint32_t> cws);
  static vector<uint8_t> interleaveCodewords1600(vector<uint32_t> input);
  
};
  
#endif

