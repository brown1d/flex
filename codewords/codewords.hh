/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   codewords.hh
 *
 * Codeword implementation
 */

#ifndef CODEWORDS_H
#define CODEWORDS_H

#include "../flex.hh"

const uint32_t SHORT_ADDRESS_CAPCODE_OFFSET = 0x8000;

class AddressShort {
private:
  uint32_t capCode;

public:
  AddressShort(uint32_t capCode);
  uint32_t getCodeword();
};
  
class BIW1 {
private:
  uint32_t priorityAddress;
  uint32_t endOfBlock;
  uint32_t vectorFieldStart;
  uint32_t carryOn;
  uint32_t frameIdCollapseMark;
  
public:
  BIW1(uint32_t priorityAddress, uint32_t endOfBlock, uint32_t vectorFieldStart, uint32_t carryOn, uint32_t frameIdCollapseMark);
  uint32_t getCodeword();
};

class BIW2 {
private:
  uint32_t localId;
  uint32_t timezone;
  
public:
  BIW2(uint32_t localId, uint32_t timezone);
  uint32_t getCodeword();
};

class BIW3 {
private:
  uint32_t year;
  uint32_t month;
  uint32_t day;
  
public:
  BIW3(uint32_t day, uint32_t month, uint32_t year);
  uint32_t getCodeword();

private:
  bool checkDay(uint32_t day);
  bool checkMonth(uint32_t month);
  bool checkYear(uint32_t year);
};

class BIW4 {
private:
  uint32_t hour;
  uint32_t minute;
  uint32_t second;

public:
  BIW4(uint32_t hour, uint32_t minute, uint32_t second);
  uint32_t getCodeword();

private:
  bool checkHour(uint32_t hour);
  bool checkMinute(uint32_t minute);
  bool checkSecond(uint32_t second);
};


class FrameInformationWord {
private:
  uint32_t cycleNumber;
  uint32_t frameNumber;
  uint32_t repeatPaging;
  uint32_t lowTrafficFlags;
  
public: 
  FrameInformationWord(uint32_t cycleNumber, uint32_t frameNumber, uint32_t repeatPaging, uint32_t lowTrafficFlags); 
  uint32_t getCodeword();
};

#endif
