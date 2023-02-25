/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   fiw.cpp
 *
 * Frame Information Word class
 */

#include "flex.h"
#include <iostream>
#include <stdexcept>

using namespace std;

class FrameInformationWord {
private:
  uint32_t cycleNumber;
  uint32_t frameNumber;
  uint32_t repeatPaging;
  uint32_t lowTrafficFlags;
  
public: 
  fiw(uint32_t cycleNumber, uint32_t frameNumber, uint32_t repeatPaging, uint32_t lowTrafficFlags) {
    if (!(cycleNumber <= 14 && frameNumber <= 127 && repeatPaging <= 1)) {
      throw std::invalid_argument("Frame Information Word: Parameters out of range");
    }

    this->cycleNumber = cycleNumber;
    this->frameNumber = frameNumber;
    this->repeatPaging = repeatPaging;
    this->lowTrafficFlags = lowTrafficFlags;
  }

  uint32_t getCodeword() {
    uint32_t cw = 0x0;
    cw |= this->cycleNumber << 4;
    cw |= this->frameNumber << 8;
    cw |= this->repeatPaging << 16;
    cw |= this->lowTrafficFlags << 17;

    cw = apply4bitChecksum(cw);
    cw = applyBchAndParity(cw);
    
    return cw;
  }
}
  
  
