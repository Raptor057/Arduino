#include <EthernetUdp2.h>

#define INDUSTRUINO_ETHERNET_MODULE_SPI_FREQUENCY 4000000
#define SPI_ETHERNET_SETTINGS SPISettings(INDUSTRUINO_ETHERNET_MODULE_SPI_FREQUENCY, MSBFIRST, SPI_MODE0)
#define UDP_PORT 1984

EthernetUDP udp;

void udpBegin() {
  udp.begin(UDP_PORT);
}

/////////////////////// UDP PING //////////////////////////////////////
// send an UDP message and wait for a response for 100ms. Returns TRUE
// if an answer was received, otherwise, FALSE.
bool pingRemoteIP() {
  static byte data[125];
  static byte emptyPacket[0];
  udp.beginPacket(REMOTE_IP, UDP_PORT);
  udp.write(emptyPacket, 0);
  udp.endPacket();
  delay(100);
  udp.parsePacket();
  if (udp.available()) {
    udp.read(data, 128);
    return true;
  }
  return false;
}

void udpStop() {
  udp.stop();
}
