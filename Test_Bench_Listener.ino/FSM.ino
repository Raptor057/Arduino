/////////////////// FSM ///////////////////////////
enum StateTypes { OFFLINE_STATE, CONNECTING_STATE, CONNECTED_STATE, ACTIVE_STATE };
enum StateTypes curState = OFFLINE_STATE;
enum StateTypes newState;

StateTypes onOffline();
StateTypes onConnecting();
StateTypes onConnected();
StateTypes onActive();
StateTypes (*stateTable[4])() = { onOffline, onConnecting, onConnected, onActive };

///////////////// STATE SETUP //////////////////////
// run once every time the FSM changes state
void onEnterState() {
  switch (curState) {
    case OFFLINE_STATE:
      lcdIP();
      lcdOffline();
      udpStop();
      break;
    case CONNECTING_STATE:
      lcdIP();
      lcdConnecting();
      udpBegin();
      break;
    case CONNECTED_STATE:
      lcdConnected();
      break;
    case ACTIVE_STATE:
      break;
  }
}

void fsmSetup() {
  newState = curState = OFFLINE_STATE;
  onEnterState();
}

void fsmLoop() {
  newState = stateTable[curState]();
  if (newState != curState) {
    curState = newState;
    onEnterState();
  }
}

///////////////////// OFFLINE STATE //////////////
// try to get an IP address from the DHCP server
// using the RTC MAC address
StateTypes onOffline() {
  if (ethBegin()) {
    // DISCONNECTED
    return CONNECTING_STATE;
  }
  return OFFLINE_STATE;
}

//////////////////// CONNECTING STATE ////////////////////
// try to stablish communication with the windows service
// through the UDP server
StateTypes onConnecting() {
  if (!is_online()) {
    // OFFLINE
    return OFFLINE_STATE;
  }
  else if (pingRemoteIP()) {
    // CONNECTED
    return CONNECTED_STATE;
  }

  lcdUpdateBrightness();

  return CONNECTING_STATE;
}

////////////////////// CONNECTED STATE ////////////////////
// monitoring of the trigger pin, if the ping is activated
// the device starts sending information to the TCP server
StateTypes onConnected() {
  /*
  if (!is_online()) {
    // OFFLINE
    return OFFLINE_STATE;
  }
  else
  */
  if (!pingRemoteIP()) {
    // DISCONNECTED
    return CONNECTING_STATE;
  }
  else if (ioTriggerIsActive()) {
    // ACTIVATED
    return ACTIVE_STATE;
  }
/*
  lcd.setCursor(0, 5);
  lcd.print(digitalRead(0));

  static char c[4] = { '|', '/', '-', '\\' };
  static int i = 0;
  lcd.print(c[i]);
  i = (i + 1) % 4;
*/
  return CONNECTED_STATE;
}

////////////////////////// ACTIVE STATE //////////////////////////////
// device is communicating with the TCP server, it sends the state of
// the three designated input pins and updates the two output pins
StateTypes onActive() {
  static uint8_t inputs;
  static uint8_t response = 0;

  // send two bytes to do some validation server side
  inputs = ioState();
  if (inputs == 0) {
    // no data
    response = 4;
  }
  else {
    response = tcpSend(inputs);
  }

  while (ioTriggerIsActive());

  if (!showTcpResult(inputs, response)) {
    // DISCONNECTED
    return CONNECTING_STATE;
  }

  // DEACTIVATED
  return CONNECTED_STATE;
}

/////////////////////////////////////////////////////
// wait the TCP server response and print the result
bool showTcpResult(uint8_t data, uint8_t response) {
  ioResponse(response);
  lcdResponse(response, data);
  return response == 4;
}
