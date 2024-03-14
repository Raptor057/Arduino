#include <SPI.h>                                // for Ethernet

////////////////////////// REAL-TIME CLOCK (RTC) MAC //////////////////////////////////////
// the D21G has a built-in RTC with a EUI-64 number that can be used as MAC address stored
// in the EEPROM, this 8-byte MAC is retrieved and formatted to 6 bytes for IPv4
#include <Wire.h>                                                         // for RTC MAC

#define I2C_ADDRESS 0x57
#define INDUSTRUINO_ETHERNET_MODULE_SPI_FREQUENCY 4000000
#define SPI_ETHERNET_SETTINGS SPISettings(INDUSTRUINO_ETHERNET_MODULE_SPI_FREQUENCY, MSBFIRST, SPI_MODE0)

byte mac[6];                                    // data from RTC

/////////////////////////////////////////////////////////////////////////////////////
// https://static.industruino.com/downloads/quickstart/Ethernet_quickstart_July2017.pdf
// https://github.com/arduino-libraries/Ethernet/blob/481f960bbef10e4b006fada962434d309c2b99b4/src/utility/w5100.cpp#L285
// https://github.com/jayacotton/inettools-z80/blob/dae5a26473f0c63228b10c5bf21c1d73cd5af3be/w5500.c#L175
bool is_online() {
  uint32_t result = 0;
  SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
  digitalWrite(10, LOW);
  uint32_t address = 11776;
  SPI.transfer((unsigned char)((address >> 16) & 0xff));
  SPI.transfer((unsigned char)((address >> 8) & 0xff));
  SPI.transfer((unsigned char)(address & 0xff));
  result = SPI.transfer((unsigned char)0x00);
  digitalWrite(10, HIGH);
  SPI.endTransaction();
/*
  lcd.setCursor(50, 6);
  lcd.print(result);
  lcd.print(" - ");
  static int counter = 0;
  lcd.print(++counter);
*/
  return result == 191;
}

void ethSetup() {
  readMACfromRTC(mac);
  lcdMac(mac);
}

byte* ethMac() {
  return mac;
}

bool ethBegin() {
  return Ethernet.begin(mac);
}

IPAddress ethLocalIP() {
  return Ethernet.localIP();
}

//////////////////////////// MAC ADDRESS ////////////////////////////////////////////
// the RTC has a MAC address stored in EEPROM - 8 bytes 0xf0 to 0xf7
// 8 bytes of 64-bit MAC address, 3 bytes valid OUI, 5 bytes unique EI
void readMACfromRTC(byte mac[6]) {
  Wire.begin();                        // I2C for RTC MAC
  mac[0] = readByteFromRtcI2CAddress(0xf0);
  mac[1] = readByteFromRtcI2CAddress(0xf1);
  mac[2] = readByteFromRtcI2CAddress(0xf2);
  // for 6-bytes MAC, skip first 2 bytes of EI (it is not explained why)
  mac[3] = readByteFromRtcI2CAddress(0xf5);
  mac[4] = readByteFromRtcI2CAddress(0xf6);
  mac[5] = readByteFromRtcI2CAddress(0xf7);
}

//////////////////////////// MAC ADDRESS /////////////////////////////////////////////
// the RTC has a MAC address stored in EEPROM
uint8_t readByteFromRtcI2CAddress(uint8_t dataAddr) {
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(dataAddr);
  Wire.endTransmission(false); // don't send stop
  Wire.requestFrom(I2C_ADDRESS, 1);
  return Wire.read();
}
