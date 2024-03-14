#define TCP_PORT 1982
EthernetClient tcp;

// send a byte to the TCP server containing the state
// of the 3 input signals
uint8_t tcpSend(uint8_t ioState) {
  static uint8_t intentNo = 0;
  static uint8_t response = 0;
  static char data[2]     = { 0, 0 };

  data[0] = data[1] = ioState;

  response = 0;

  //for (intentNo = 1; intentNo <= 1 && response != 1; intentNo++)
  {
    // add some delay after the first try
    if (intentNo > 1) delay(100);

    if (!tcp.connect(REMOTE_IP, TCP_PORT)) {
      // disconnected
      return 3;
    }

    tcp.write(data);
    tcp.flush();
    response = tcpResponse();
    tcp.stop();
  }

  lcdCounter();

  return response;
}

// wait for the TCP server to respond to our message, the value of 1 means
// success (1) and any other value will be considered as failure (2), in
// case of timeout the resulting value will be 0 (NO RESPONSE)
uint8_t tcpResponse() {
  // give a little time for the server to respond
  delay(100);
  if (tcp.available()) {
    if (tcp.read() == 1) {
      // success
      return 1;
    }
    else {
      // failure
      return 0;
    }
  }
  else {
    // no response
    return 2;
  }
}
