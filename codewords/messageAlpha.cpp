/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   messageAlpha.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

MessageAlpha::MessageAlpha(uint32_t messageNumber, string message) {
  // Not supported for now
  // - Fragmented messages
  // - Message retrieval flag
  // - Mail Drop flag
  this->messageAlphaHeader = new MessageAlphaHeader(0, 3, messageNumber, 0, 0);
  string messageFilled = message;
  fillUpChars(&messageFilled);
  this->messageAlphaSignature = new MessageAlphaSignature(calculateSignature(message),
							  messageFilled.substr(0, 3));

  this->messageAlphaContent = new vector<MessageAlphaContent>();
  for (int i = 0; i < (messageFilled.length() - 2) / 3; i++) {
    this->messageAlphaContent->push_back(MessageAlphaContent(messageFilled.substr(2+i * 3, 3)));
  }
						      
}

// Pad the String
void MessageAlpha::fillUpChars(string *message) {
  while (message->length() % 3 != 2) {
    message->append("\x3");
  }
}

uint32_t MessageAlpha::calculateSignature(string message) {
  uint32_t sum = 0x0;

  const char* c = message.c_str();
  for (int i = 0; i < message.size(); i++) {
    sum += ((uint32_t) c[i]) & 0x7F;
  }
  sum ^= 0xFFFFFFFF;
  return sum & 0x7F;
}

uint32_t MessageAlpha::calculateFragmentCheck(vector<uint32_t> codewords) {
  uint32_t fragmentCheck = 0x00;

  for (auto it = codewords.begin(); it != codewords.end(); it++) {
    fragmentCheck += getBitgroupSum(*it);
  }
  
  fragmentCheck ^= 0xFFFFFFFF;
  return fragmentCheck & 0x3FF;
}

uint32_t MessageAlpha::getBitgroupSum(uint32_t codeword) {
  uint32_t sum = 0x0;

  sum += codeword & 0xff;
  sum += (codeword >> 8) & 0xff;
  sum += (codeword >> 16) & 0x1f;

  return sum;
}

vector<uint32_t> MessageAlpha::getCodewords() {
    vector<uint32_t> cws;

    cws.push_back(messageAlphaHeader->getCodeword());
    cws.push_back(messageAlphaSignature->getCodeword());
    // Iterate through vector of Message Alpha Content
    for (auto it = messageAlphaContent->begin(); it != messageAlphaContent->end(); it++) {
      cws.push_back(it->getCodeword());
    }
    
    auto header = cws.begin();
    *header = *header | calculateFragmentCheck(cws);
    *header = applyBchAndParity(*header & 0x1fffff);
    return cws;  
}
  
	
