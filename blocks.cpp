/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   blocks.cpp
 *
 * Blocks handler routines
 */

#include "flex.h"
#include <iostream>
#include <stdexcept>

using namespace std;

class Blocks {
public:
  vector<uint8_t> getBytes(vector<Message> messages, bool sendTime) {
    uint32_t amountAddressCws = countAddressCws(messages);
    vector<uint32_t> biwCws = getBiwCws(amountAddressCws, sendTime);

  }
  
private:
  uint32_t countAddressCws(vector<Message> messages) {
    return messages.size();
  }

  
}
  
