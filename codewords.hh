/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   codewords.hh
 *
 * Codeword implementation
 */


#ifndef CODEWORDS_H
#define CODEWORDS_H

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
  
#endif
