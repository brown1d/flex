/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   test.cpp
 *
 * Test Class
 */

#include "flex.hh"
#include "message.hh"
#include "fiw.hh"

#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
  // Test1: Test Message
  try {
    Message message(0, MessageType::AlphaNum, 0x0001, "test");
    cout << "Test 1 Passed"<< endl;
  } catch (std::invalid_argument& e) {
    cerr << "Test1: " << e.what() << endl;
  }
  
  // Test2: This test should throw an exception
  try {
    Message message(0, MessageType::AlphaNum, 0x0000, "test");
    cerr << "Test2: This should be invalid and throw an exception, test failed" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 2 Passed"<< endl;
  }
  
  // Test3: Test message get number of content codewords when five characters
  try {
    Message message(0, MessageType::AlphaNum, 0x8001, "abcde");
    if (message.getNumberOfContentCodewords() != 3) {
      cerr << "Test3: Invalid number of Codewords " << message.getNumberOfContentCodewords() << endl;
    } else {
      cout << "Test 3 Passed"<< endl;
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
    } else {
      cout << "Test 4 Passed"<< endl;
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
    } else {
      cout << "Test 5 Passed"<< endl;
    }
  }  catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  // Test 6: Test Frame info word
  try {
    FrameInformationWord fiw(3, 60, 0, 8);
    uint32_t codeWord = fiw.getCodeword() & 0x1ffff0;
    if (codeWord != 0x103c30) {
      cerr << "Test 6: Invalid Codeworrd from FIW" << codeWord << endl;
    } else {
      cout << "Test 6 passed" << endl;
    }
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  // Test 7: Test Frame info word, out of range cycle
  try {
    FrameInformationWord fiw(15, 60, 0, 8);
    cerr << "Test 7 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 7 passed " << e.what() << endl;
  }

  // Test 8: Test Frame info word, out of range frame
  try {
    FrameInformationWord fiw(14, 128, 0, 8);
    cerr << "Test 8 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 8 passed " << e.what() << endl;
  }

  // Test 9: Test Frame info word, out of range repeat
  try {
    FrameInformationWord fiw(14, 60, 2, 8);
    cerr << "Test 9 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 9 passed " << e.what() << endl;
  }
  
  // Test 10: Test Frame info word CRC
  try {
    FrameInformationWord fiw(3, 107, 0, 0);
    uint32_t codeWord = fiw.getCodeword();
    if (codeWord != 0xe4a06b3b) {
      cerr << "Test 10: Invalid CRC " << codeWord << endl;
    } else {
      cout << "Test 10 passed" << endl;
    }
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

}
