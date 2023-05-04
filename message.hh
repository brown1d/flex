/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   message.hh
 *
 * Message class
 */

#ifndef MESSAGE_H
#define MESSAGE_H

class Message {
private:
  uint32_t frame;
  MessageType messageType;
  string data;
  uint32_t capcode;

public:
  Message(uint32_t frame, MessageType messageType, uint32_t capcode, string data);
  uint32_t getNumberOfMessageCodewords();
  uint32_t getNumberOfContentCodewords();
  uint32_t getCapcode();
  string getData();
  
private:
  CapcodeType getCapcodeType(uint32_t capcode);
};
#endif
