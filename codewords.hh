/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   codewords.hh
 *
 * Codeword implementation
 */


#ifndef CODEWORDS_H
#define CODEWORDS_H

class Biw1 {
private:
  uint32_t priorityAddress;
  uint32_t endOfBlock;
  uint32_t vectorFieldStart;
  uint32_t carryOn;
  uint32_t frameIdCollapseMark;

public:
  Biw1(uint32_t priorityAddress, uint32_t endOfBlock, uint32_t vectorFieldStart, uint32_t carryOn, uint32_t frameIdCollapseMark);
  uint32_t getCodeword();
}
  
#endif
