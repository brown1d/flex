#include "flex.hh"
#include "message.hh"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
  try {
    Message message(1, MessageType::AlphaNum, 1, "test1234");
    cout << message.getNumberOfContentCodewords() << endl;
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }
  
  return 0;
}

