/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   codewords.cpp
 *
 * Codeword implementation
 */

#include "flex.hh"
#include "codewords.hh"

// BIW1 Constructor
BIW1::BIW1(uint32_t priorityAddress, uint32_t endOfBlock, uint32_t vectorFieldStart, uint32_t carryOn, uint32_t frameIdCollapseMark) {
  this->priorityAddress = priorityAddress & 0xf;
  this->endOfBlock = endOfBlock & 0x3;
  this->vectorFieldStart = vectorFieldStart & 0x3f;
  this->carryOn = carryOn & 0x3;
  this->frameIdCollapseMark = frameIdCollapseMark & 0x7;
}

uint32_t BIW1::getCodeword() {
  uint32_t cw = 0x0;

  cw |= this->priorityAddress << 4;
  cw |= this->endOfBlock << 8;
  cw |= this->vectorFieldStart << 10;
  cw |= this->carryOn << 16;
  cw |= this->frameIdCollapseMark << 18;

  cw = apply4bitChecksum(cw);
  cw = applyBchAndParity(cw);

  return cw;
}

// BIW2 Constructor
BIW2::BIW2(uint32_t localId, uint32_t timezone) {
  this->localId = localId & 0x01FF;
  this->timezone = timezone & 0x01F;
}

uint32_t BIW2::getCodeword() {
  uint32_t cw = 0x0;
  cw |= this->timezone << 7;
  cw |= this->localId << 12;

  cw = apply4bitChecksum(cw);
  cw = applyBchAndParity(cw);

  return cw;
}

// BIW3 Constructor
BIW3::BIW3(uint32_t day, uint32_t month, uint32_t year) {
  if (!(checkDay(day) && checkMonth(month) && checkYear(year))) {
    throw std::invalid_argument("Invalid date given");
  }

  this->year = year - 1994;
  this->month = month;
  this->day = day;
}

uint32_t BIW3::getCodeword() {
  uint32_t cw = 0x0;
  cw |= 0x1 << 4;
  cw |= this->year << 7;
  cw |= this->day << 12;
  cw |= this->month << 17;

  cw = apply4bitChecksum(cw);
  cw = applyBchAndParity(cw);

  return cw;
}

bool BIW3::checkDay(uint32_t day) {
  return day >= 1 && day <= 31;
}

bool BIW3::checkMonth(uint32_t month) {
  return month >= 1 && month <= 12;
}

bool BIW3::checkYear(uint32_t year) {
  return year >= 1994 && year <= 2025;
}

// BIW4 Constructor
BIW4::BIW4(uint32_t hour, uint32_t minute, uint32_t second) {
  if (!(checkHour(hour) && checkMinute(minute) && checkSecond(second))) {
    throw std::invalid_argument("Invalid time given");
  }

  this->hour = hour;
  this->minute = minute;
  this->second = (unsigned int) second / 7.5;
  this->second &= 0x7;
}

uint32_t BIW4::getCodeword() {
  uint32_t cw = 0x0;
  cw |= 0x2 << 4;
  cw |= this->hour << 7;
  cw |= this->minute << 12;
  cw |= this->second << 18;

  cw = apply4bitChecksum(cw);
  cw = applyBchAndParity(cw);

  return cw;
}

bool BIW4::checkHour(uint32_t hour) {
  return hour <= 23;
}

bool BIW4::checkMinute(uint32_t minute) {
  return minute <= 59;
}

bool BIW4::checkSecond(uint32_t second) {
  return second <= 59;
}
