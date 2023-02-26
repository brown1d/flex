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

  // Test 6: Test CRC all zeros
  uint32_t testCodeword = 0;
  uint32_t result = applyBchChecksum(testCodeword);
  if (result == 0) {
    cout << "Test 6: Passed, excepted CRC matches" << endl;
  } else {
    cerr << "Test 6: Failed, excepted CRC does not match " << result << endl;
  }

  // Test 7 :Test CRC all ones
  testCodeword = 0x001fffff;
  result = applyBchChecksum(testCodeword);
  if (result == 0x7FFFFFFF) {
    cout << "Test 7: Passed, excepted CRC matches" << endl;
  } else {
    cerr << "Test 7: Failed, excepted CRC does not match " << result <<	endl;
  }

  // Test 8: Test CRC 1
  testCodeword = 0x1D40CD;
  result = applyBchChecksum(testCodeword);
  if (result == 0x1EDD40CD) {
    cout << "Test 8: Passed, excepted CRC matches" << endl;
  } else {
    cerr << "Test 8: Failed, excepted CRC does not match " << result <<	endl;
  }

  
  // Test 9: Test CRC 2
  testCodeword = 0x87523;
  result = applyBchChecksum(testCodeword);
  if (result == 0x38C87523) {
    cout << "Test 9: Passed, excepted CRC matches" << endl;
  } else {
    cerr << "Test 9: Failed, excepted CRC does not match " << result <<	endl;
  }

  // Test 10: 4 bit checksum all zeros
  testCodeword = 0x0;
  result = apply4bitChecksum(testCodeword);
  if (result == 0x0000000F) {
    cout << "Test 10: Passed, excepted 4bit checksum matches" << endl;
  } else {
    cerr << "Test 10: Failed, excepted 4bit checksum does not match " << result <<	endl;
  }

  // Test 11: 4 bit checksum all zeros
  testCodeword = 0x001FFFF0;
  result = apply4bitChecksum(testCodeword);
  if (result == 0x001FFFF2) {
    cout << "Test 11: Passed, excepted 4bit checksum matches" << endl;
  } else {
    cerr << "Test 11: Failed, excepted 4bit checksum does not match " << result <<	endl;
  }

    // Test 12: 4 bit checksum all zeros
  testCodeword = 0x00139C50;
  result = apply4bitChecksum(testCodeword);
  if (result == 0x00139C51) {
    cout << "Test 12: Passed, excepted 4bit checksum matches" << endl;
  } else {
    cerr << "Test 12: Failed, excepted 4bit checksum does not match " << result <<	endl;
  }

  
  // Test 13: Test Frame info word
  try {
    FrameInformationWord fiw(3, 60, 0, 8);
    uint32_t codeWord = fiw.getCodeword() & 0x1ffff0;
    if (codeWord != 0x103c30) {
      cerr << "Test 13: Invalid Codeworrd from FIW" << codeWord << endl;
    } else {
      cout << "Test 13 passed" << endl;
    }
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  // Test 14: Test Frame info word, out of range cycle
  try {
    FrameInformationWord fiw(15, 60, 0, 8);
    cerr << "Test 14 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 14 passed " << e.what() << endl;
  }

  // Test 15: Test Frame info word, out of range frame
  try {
    FrameInformationWord fiw(14, 128, 0, 8);
    cerr << "Test 15 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 15 passed " << e.what() << endl;
  }

  // Test 16: Test Frame info word, out of range repeat
  try {
    FrameInformationWord fiw(14, 60, 2, 8);
    cerr << "Test 16 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 16 passed " << e.what() << endl;
  }
  
  // Test 17: Test Frame info word CRC
  try {
    FrameInformationWord fiw(3, 107, 0, 0);
    uint32_t codeWord = fiw.getCodeword();
    if (codeWord != 0xe4a06b3b) {
      cerr << "Test 17: Invalid CRC " << codeWord << endl;
    } else {
      cout << "Test 17 passed" << endl;
    }
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

}
