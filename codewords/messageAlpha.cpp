/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   messageAlpha.cpp
 *
 * Codeword implementation
 */

#include "codewords.hh"

MessageAlpha::MessageAlpha(uint32_t messageNumber, char* message) {
  // Not supported for now
  // - Fragmented messages
  // - Message retrieval flag
  // - Mail Drop flag
  MessageAlphaHeader messageAlphaHeader(0, 3, messageNumber, 0, 0);

}

uint32_t AddressShort::getCodeword() {
}

	
