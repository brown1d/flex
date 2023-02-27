/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   block.hh
 *
 * Block class
 */

#ifndef BLOCK_H
#define BLOCK_H

class Blocks {
public:
  vector<uint8_t> getBytes(vector<Message> messages, bool sendTime);
private:
  uint32_t countAddressCws(vector<Message> messages);
}

#endif

