/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   biw3.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

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
