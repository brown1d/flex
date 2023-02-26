/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   test.cpp
 *
 * Test Class
 */

#include "flex.hh"
#include "message.hh"

#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
  // Test1: Test Message
  try {
    Message message(0, MessageType::AlphaNum, 0x0001, "test");
  } catch (std::invalid_argument& e) {
    cerr << "Test1: " << e.what() << endl;
  }

  // Test2: This test should throw an exception
  try {
    Message message(0, MessageType::AlphaNum, 0x0000, "test");
  } catch (std::invalid_argument& e) {
    cerr << "Test2: This should be invalid " << e.what() << endl;
  }
  
  // Test3: Test message get number of content codewords when five characters
  try {
    Message message(0, MessageType::AlphaNum, 0x8001, "abcde");
    if (message.getNumberOfContentCodewords() != 3) {
      cerr << "Test3: Invalid number of Codewords " << message.getNumberOfContentCodewords() << endl;
    }
  }  catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  // Test4: Test message get number of content codewords when two characters
  try {
    Message message(0, MessageType::AlphaNum, 0x8001, "ab");
    if (message.getNumberOfMessageCodewords() != 4) {
      cerr << "Test4: Invalid number of Codewords " << message.getNumberOfContentCodewords() << endl;
    }
  }  catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  // Test5: Test message get number of content codewords when four characters
  try {
    Message message(0, MessageType::AlphaNum, 0x8001, "abcd");
    if (message.getNumberOfMessageCodewords() != 5) {
      cerr << "Test5: Invalid number of Codewords " << message.getNumberOfContentCodewords() << endl;
    }
  }  catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

}
