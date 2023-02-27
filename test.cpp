/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   test.cpp
 *
 * Test Class
 */

#include "flex.hh"
#include "message.hh"
#include "fiw.hh"
#include "codewords.hh"

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
   //--------------- Bch Checksum
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

  //--------------- 4bit Checksum
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

  //--------------- Parity
  // Test 13: Test Parity all zeros
  uint32_t testData = 0x0;
  bool resultBool = checkAndSetParity(&testData);
  if (resultBool == false) {
    cout << "Test 13: Passed, Parity is false" << endl;
  } else {
    cerr << "Test 13: Failed, partiy is true " << result << endl;
  }
  if (unsigned(testData) == testData) {
    cout << "Test 13: Passed, test data is " << unsigned(testData) << endl;
  } else {
    cerr << "Test 13: Failed, test data is " << unsigned(testData) << endl;
  }

  // Test 14: Test Parity all ones
  testData = 0x7FFFFFFF;
  resultBool = checkAndSetParity(&testData);
  if (resultBool == true) {
    cout << "Test 14: Passed, Parity is true" << endl;
  } else {
    cerr << "Test 14: Failed, partiy is false " << result << endl;
  }
  if (testData == 0xFFFFFFFF) {
    cout << "Test 14: Passed, test data is " << testData << endl;
  } else {
    cerr << "Test 14: Failed, test data is " << testData << endl;
  }

  // Test 15: Test Parity Even
  testData = 0x3;
  resultBool = checkAndSetParity(&testData);
  if (resultBool == false) {
    cout << "Test 15: Passed, Parity is false" << endl;
  } else {
    cerr << "Test 15: Failed, partiy is true " << result << endl;
  }
  if (testData == testData) {
    cout << "Test 15: Passed, test data is " << testData << endl;
  } else {
    cerr << "Test 15: Failed, test data is " << testData << endl;
  }
  
  // Test 16: Test Illegal Parity Even
  testData = 0x80000003;
  resultBool = checkAndSetParity(&testData);
  if (resultBool == false) {
    cout << "Test 16: Passed, Parity is false" << endl;
  } else {
    cerr << "Test 16: Failed, partiy is true " << result << endl;
  }
  if (testData == 0x00000003) {
    cout << "Test 16: Passed, test data is " << testData << endl;
  } else {
    cerr << "Test 16: Failed, test data is " << testData << endl;
  }

  // Test 17: Test Illegal Parity odd
  testData = 0x80000001;
  resultBool = checkAndSetParity(&testData);
  if (resultBool == true) {
    cout << "Test 17: Passed, Parity is true" << endl;
  } else {
    cerr << "Test 17: Failed, partiy is false " << result << endl;
  }
  if (testData == 0x80000001) {
    cout << "Test 17: Passed, test data is " << testData << endl;
  } else {
    cerr << "Test 17: Failed, test data is " << testData << endl;
  }

  //--------------- Frame Information Word
  // Test 18: Test Frame info word
  try {
    FrameInformationWord fiw(3, 60, 0, 8);
    uint32_t codeWord = fiw.getCodeword() & 0x1ffff0;
    if (codeWord != 0x103c30) {
      cerr << "Test 18: Invalid Codeworrd from FIW" << codeWord << endl;
    } else {
      cout << "Test 18 passed" << endl;
    }
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  // Test 19: Test Frame info word, out of range cycle
  try {
    FrameInformationWord fiw(15, 60, 0, 8);
    cerr << "Test 19 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 19 passed " << e.what() << endl;
  }

  // Test 20: Test Frame info word, out of range frame
  try {
    FrameInformationWord fiw(14, 128, 0, 8);
    cerr << "Test 20 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 20 passed " << e.what() << endl;
  }

  // Test 21: Test Frame info word, out of range repeat
  try {
    FrameInformationWord fiw(14, 60, 2, 8);
    cerr << "Test 21 should throw exception" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 21 passed " << e.what() << endl;
  }
  
  // Test 22: Test Frame info word CRC
  try {
    FrameInformationWord fiw(3, 107, 0, 0);
    uint32_t codeWord = fiw.getCodeword();
    if (codeWord != 0xe4a06b3b) {
      cerr << "Test 22: Invalid CRC " << codeWord << endl;
    } else {
      cout << "Test 22 passed" << endl;
    }
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  //--------------- Test Code word
  // Test 23: BIW1 - Test Codeword
  BIW1 biw1(10, 2, 60, 1, 6);
  if ((biw1.getCodeword() & 0x1FFFF0) != 0x19F2A0) {
    cerr << "Test 23: BIW1 Invalid Codeword" << endl;
  } else {
    cout << "Test 23: Test passed" << endl;
  }

  
  // Test 24: BIW1 - Test Codeword CRC
  BIW1 biw1a(0, 0, 2, 0, 0);
  if (biw1a.getCodeword() != 0x19400807) {
    cerr << "Test 24: BIW1 Invalid Codeword" << endl;
  } else {
    cout << "Test 24: Test passed" << endl;
  }

  // Test 25 : BIW2 - Test Codeword
  BIW2 biw2(0x1ff, 1);
  if ((biw2.getCodeword() & 0x01ffff0) != 0x1ff080) {
    cerr << "Test 25: BIW2 Invalid Codeword" << endl;
  } else {
    cout << "Test 25: Test passed" << endl;
  }

  // Test 26: BIW3 - Test Codeword
  BIW3 biw3(31, 12, 1999);
  if ((biw3.getCodeword() & 0x01ffff0) != 0x19F290) {
    cerr << "Test 26: BIW3 Invalid Codeword" << endl;
  } else {
    cout << "Test 26: Test passed" << endl;
  }

  // Test 27: BIW3 - Invalid Day
  try {
    BIW3 biw3a(32, 12, 1999);
    cerr << "Test 27: Invalid Date exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 27: Passed" << endl;
  }

  // Test 28: BIW3 - Invalid Month
  try {
    BIW3 biw3a(31, 13, 1999);
    cerr << "Test 28: Invalid Date exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 28: Passed" << endl;
  }

  // Test 29: BIW3 - Invalid Day 0
  try {
    BIW3 biw3a(0, 12, 1999);
    cerr << "Test 29: Invalid Date exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 29: Passed" << endl;
  }
  
  // Test 30: BIW3 - Invalid Month 0
  try {
    BIW3 biw3a(31, 0, 1999);
    cerr << "Test 30: Invalid Date exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 30: Passed" << endl;
  }

  // Test 31: BIW3 - Invalid Year low
  try {
    BIW3 biw3a(1, 1, 1993);
    cerr << "Test 31: Invalid Date exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 31: Passed" << endl;
  }

  // Test 32: BIW3 - Invalid Year high
  try {
    BIW3 biw3a(1, 1, 2026);
    cerr << "Test 32: Invalid Date exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 32: Passed" << endl;
  }

  // Test 33: BIW4 - Test Codeword
  BIW4 biw4(23, 59, 59);
  if ((biw4.getCodeword() & 0x01ffff0) != 0x1fbba0) {
    cerr << "Test 33: BIW4 Invalid Codeword" << endl;
  } else {
    cout << "Test 33: Test passed" << endl;
  }

  // Test 34: BIW4 - Test Codeword 2
  BIW4 biw4a(23, 59, 31);
  if ((biw4a.getCodeword() & 0x01ffff0) != 0x13bba0) {
    cerr << "Test 34: BIW4 Invalid Codeword" << endl;
  } else {
    cout << "Test 34: Test passed" << endl;
  }

  // Test 35: BIW4 - Test Codeword 3
  BIW4 biw4b(0, 0, 0);
  if ((biw4b.getCodeword() & 0x01ffff0) != 0x000020) {
    cerr << "Test 35: BIW4 Invalid Codeword" << endl;
  } else {
    cout << "Test 35: Test passed" << endl;
  }

  // Test 36: BIW4 - Invalid Hour
  try {
    BIW4 biw4c(24, 59, 59);
    cerr << "Test 36: Invalid Time exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 36: Passed" << endl;
  }

  // Test 37: BIW4 - Invalid Minute
  try {
    BIW4 biw4c(23, 60, 59);
    cerr << "Test 37: Invalid Time exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 37: Passed" << endl;
  }

  // Test 38: BIW4 - Invalid Second
  try {
    BIW4 biw4c(23, 59, 60);
    cerr << "Test 38: Invalid Time exception should be thrown" << endl;
  } catch (std::invalid_argument& e) {
    cout << "Test 38: Passed" << endl;
  }

}
