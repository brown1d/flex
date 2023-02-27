/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   flex.hh
 *
 * Flex Implementation
 */


#ifndef FLEX_H
#define FLEX_H

#include <cstdint>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

enum MessageType {
  AlphaNum
};

enum CapcodeType {
  ShortAddress,
  Invalid
};

// Helper functions
uint32_t apply4bitChecksum(uint32_t codeword);
uint32_t applyBchChecksum(uint32_t codeword);
uint32_t applyBchAndParity(uint32_t codeword);
bool checkAndSetParity(uint32_t *codeword);

#endif
