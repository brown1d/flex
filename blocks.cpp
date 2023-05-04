/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   blocks.cpp
 *
 * Blocks handler routines
 */

#include "flex.hh"
#include "blocks.hh"
#include <iostream>
#include <stdexcept>

using namespace std;

vector<uint8_t> Blocks::getBytes(vector<Message> messages, bool sendTime) {
  uint32_t amountAddressCws = countAddressCws(messages);
  vector<uint32_t> biwCws = getBiwCws(amountAddressCws, sendTime);
  vector<uint32_t> addressCws = getAddressCws(messages);
  VectorAndContentCws vectorAndContent = getVectorAndContentCws(messages, biwCws.size(), addressCws.size());
  
  vector<uint32_t> cws;
  cws.insert(cws.end(), biwCws.begin(), biwCws.end());
  cws.insert(cws.end(), addressCws.begin(), addressCws.end());
  cws.insert(cws.end(), vectorAndContent.vectorCws.begin(), vectorAndContent.vectorCws.end());
  cws.insert(cws.end(), vectorAndContent.contentCws.begin(), vectorAndContent.contentCws.end());
  cws = fillUpBlock1600(cws);

  vector<uint8_t> bytes;
  for (uint32_t i = 0; i < 11; i++) {
    vector<uint32_t> slice = vector<uint32_t>(cws.begin() + (i* 8), cws.begin() + ((i + 1) * 8));
    vector<uint8_t> interleaved = interleaveCodewords1600(slice);
    bytes.insert(bytes.end(),  interleaved.begin(), interleaved.end()); 
  }

  return bytes;
}
  
uint32_t Blocks::countAddressCws(vector<Message> messages) {
  // Currently, only Short Addresses supported, so
  // amount of address codwords is equal to amount of messages
  return messages.size();
}

vector<uint32_t> Blocks::getBiwCws(uint32_t amountAddresses, bool sendTime) {
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

vector<uint32_t> Blocks::getAddressCws(vector<Message> messages) {
  vector<uint32_t> addressCws;

  for (auto it = messages.begin(); it != messages.end(); it++) {
    AddressShort addressShort(it->getCapcode());
    addressCws.push_back(addressShort.getCodeword());
  }
  return addressCws;
}

VectorAndContentCws Blocks::getVectorAndContentCws(vector<Message> messages, uint32_t biwCwsSize, uint32_t addressCwsSize) {
  uint32_t biwAddressVectorCwsSize= biwCwsSize + 2 * addressCwsSize;  // Address and Vector CWS
  
  VectorAndContentCws vectorAndContentCws;

  for (auto it = messages.begin(); it != messages.end(); it++) {
    uint32_t contentStart = biwAddressVectorCwsSize + vectorAndContentCws.contentCws.size();
    uint32_t contentWords = it->getNumberOfContentCodewords();

    VectorAlpha vectorAlpha(contentStart, contentWords);
    vectorAndContentCws.vectorCws.push_back(vectorAlpha.getCodeword());

    MessageAlpha messageAlpha(0, it->getData());
    vector<uint32_t> content = messageAlpha.getCodewords(); 
    vectorAndContentCws.contentCws.insert(vectorAndContentCws.contentCws.end(), content.begin(), content.end());
  }

  return vectorAndContentCws;
}
 
vector<uint32_t> Blocks::fillUpBlock1600(vector<uint32_t> cws) {
   vector<uint32_t> filledCws;

  while (filledCws.size() < 88) {
    if (filledCws.size() % 2 == 0) {
      filledCws.push_back(0xffffffff);
    } else {
      filledCws.push_back(0x0);
    }
  }

  return filledCws;
}

vector<uint8_t> Blocks::interleaveCodewords1600(vector<uint32_t> input) {
  if (input.size() != 8) {
    throw std::invalid_argument("Exactly 8 input codewords required");
  }
  
  vector<uint8_t> outputData(32, 0);
  for (uint8_t bitIndex = 0; bitIndex < 32; bitIndex++) {
    for (uint8_t codeword = 0; codeword < 8; codeword++) {
      uint32_t inputMask = 1 << bitIndex;
      uint32_t maskedInput = input[codeword] & inputMask;
      uint32_t backshiftedInput = (maskedInput >> bitIndex) & 0x00000001;
      uint8_t readBit = (uint8_t) backshiftedInput;
      uint8_t bitToWrite = readBit << codeword;
      outputData[bitIndex] = outputData[bitIndex] ^ bitToWrite;      
    }
  }
  
  return outputData;
}

