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
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
      printf("%x ", *it);
    }
    printf("\n");
}

uint8_t reverseBits(uint8_t b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int main() {
  sockaddr_in servaddr;
  int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (fd < 0) {
    cerr << ("Cannot open UDP socket") << endl;
    return -1;
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  inet_pton(AF_INET, "192.168.64.2", &(servaddr.sin_addr));
  servaddr.sin_port = htons(3000);
  
  try {
    vector<Message> messages;
    messages.push_back(Message(0, MessageType::AlphaNum, 0xd155d, "test1234567890-"));

    // Current datae and time based on the system clock
    time_t now = time(0);
    tm *ltm = localtime(&now);

    tuple<uint32_t, uint32_t> cycleNrFrameNr = Frame::calculateCycleAndFrame(ltm->tm_min, ltm->tm_sec);
    cout << "Time: " << ltm->tm_min << ":" << ltm->tm_sec << " Cycle: " << get<0>(cycleNrFrameNr) << " Frame " << get<1>(cycleNrFrameNr) << endl;

    Frame frame = Frame(get<0>(cycleNrFrameNr),  get<1>(cycleNrFrameNr));

    for (auto it = messages.begin(); it != messages.end(); it++) {
      if (it->getNumberOfMessageCodewords() < frame.spaceLeft()) {
        frame.addMessage(*it);
      }
    }   


    vector<uint8_t> msg = frame.getBytes();
    //print(msg.getBytes());
    for (auto it = msg.begin(); it != msg.end(); it++) {
      *it = reverseBits(*it);
    }
    //print(msg.getBytes());

    if (sendto(fd, msg.data(), msg.size(), 0, (sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
      perror("Unable to send datagram");
      cerr << "Unable to send UDP datagram to radio host" << endl;
      return -2;
    }

  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}

