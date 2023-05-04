/**
 * Author: David Brown <dave@bagpuss.nu>
 * File:   main.cpp
 *
 * Main Class
 */

#include "flex.hh"
#include "message.hh"
#include "frame.hh"
#include <iostream>
#include <stdexcept>

using namespace std;

const uint32_t CYCLES_PER_HOUR = 15;
const uint32_t FRAMES_PER_CYCLE = 128;

vector<uint8_t> framesHton(vector<Frame> frames) {
  vector<uint8_t> reversedBytes;
  for (int i = 0; i < frames.size() ; i++) {
    vector<uint8_t> bytes = frames[i].getBytes();
    for (int j = 0; j < bytes.size() ; j++) {
      //             reversed_bytes.push(byte.swap_bits());
      //reversedBytes.push_back(bytes[j].
    }
  }

  return reversedBytes;
}

void print(std::vector<uint8_t> const &input)
{
    for (auto it = input.cbegin(); it != input.cend(); it++) {
        std::cout << hex << *it << ' ';
    }
}
 

int main() {
  try {
    vector<Message> messages;
    messages.push_back(Message(0, MessageType::AlphaNum, 0x0001, "test"));
    cout << messages[0].getNumberOfContentCodewords() << endl;

    tuple<uint32_t, uint32_t> cycleNrFrameNr = Frame::calculateCycleAndFrame(0, 0);
    cout << "Cycle: " << get<0>(cycleNrFrameNr) << " Frame " << get<1>(cycleNrFrameNr) << endl;

    Frame frame = Frame(get<0>(cycleNrFrameNr),  get<1>(cycleNrFrameNr));

    for (auto it = messages.begin(); it != messages.end(); it++) {
      if (it->getNumberOfMessageCodewords() < frame.spaceLeft()) {
        cout << "Frame still has space" << endl;
        frame.addMessage(*it);
      }
    }   

    print(frame.getBytes());
    
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}

