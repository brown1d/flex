/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   biw4.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

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
