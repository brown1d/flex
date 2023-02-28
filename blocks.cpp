/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   blocks.cpp
 *
 * Blocks handler routines
x */

#include "flex.hh"
#include "blocks.hh"
#include <iostream>
#include <stdexcept>

using namespace std;

vector<uint8_t> Block::getBytes(vector<Message> messages, bool sendTime) {
  uint32_t amountAddressCws = countAddressCws(messages);
  vector<uint32_t> biwCws = getBiwCws(amountAddressCws, sendTime);

  
}
  
uint32_t Block::countAddressCws(vector<Message> messages) {
  // Currently, only Short Addresses supported, so
  // amount of address codwords is equal to amount of messages
  return messages.size();
}

vector<uint32_t> Block::getBinCws(uint32_t amountAddresses, bool sendTime) {
  uint32_t startwordAddresses = 0;
  if (sendTime) {
    startwordAddresses = 3;   // Offset because of BIW 2, 3 and 4
  }

  uint32_t startwordVectors = 1  // BIW 1
    + startwordAddresses + amountAddresses;

  BIW1 biw1(0, startwordAddresses, startwordVectors, 0, 0);
  vector<uint32_t> biwCws;
  biwCws.push_back(biw1.getCodeword());

  if (sendTime) {
    biwCws.push_back(BIW2(0, 0x1).getCodeword());
    biwCws.push_back(BIW3(23, 5, 1999).getCodeword());
    biwCws.push_back(BIW4(13, 37, 0).getCodeword());
  }

  return biwCws;
}

vector<uint32_t> getAddressCws(vector<Message> messages) {
  vector<uint32_t> addressCws;

  for (auto it = messages.begin(); it != messages.end(); it++) {
    AddressShort addressShort(*it->getCapcode());
    addressCws(addressShort.getCodeword());
  }
  return addressCws;
}

VectorAndContentCws getVectorAndContentCws(vector<Message> messages, uint32_t biwCwsSize, uint32_t addressCwsSize) {
  uint32_t biwAddressVectorCwsSize= biwCwsSize + 2 * addressCwsSize;  // Address and Vector CWS
  
  VectorAndContentCws vectorAndContentCws;

  for (auto it = messages.begin(); it != messages.end(); it++) {
    uint32_t contentStart = biwAddressVectorCwsSize + vectorAndContentCws.length();
    uint32_t contentWords = it->getNumberOfContentCodewords();

    VectorAlpha vectorAlpha(contentStart, contentWords);
    vectorAndContentCws.vectorCws.push_back(vectorAlpha.getCodeword());

    MessageAlpha messageAlpha(0, message.data);
    vectorAndContentCws.contentCws.push_back(content.getCodeword());
  }

  return vectorAndContentCws;
}
