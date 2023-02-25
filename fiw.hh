/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   fiw.hh
 *
 * Frame Information Word class
 */

#ifndef FIW_H
#define FIW_H


class FrameInformationWord {
private:
  uint32_t cycleNumber;
  uint32_t frameNumber;
  uint32_t repeatPaging;
  uint32_t lowTrafficFlags;
  
public: 
  FrameInformationWord(uint32_t cycleNumber, uint32_t frameNumber, uint32_t repeatPaging, uint32_t lowTrafficFlags); 
  uint32_t getCodeword();
}

#endif
  
