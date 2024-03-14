
/*
 * Test Bench Listener
 * 
 * Creates a TCP client that communicates with a traceability
 * TCP server. It will send a TCP message every time a signal
 * from the test bench harware is received.
 * 
 * Test Bench Bridge sketch for:
 * > Industruino D21G PROTO
 * > Industruino Ethernet module
 * 
 * Libraries needed:
 * > Ethernet2: Industruino version at https://github.com/Industruino/Ethernet2
 * > UC1701: https://github.com/Industruino/UC1701
 * 
 * This sketch:
 * -
 * 
 * Author:      Eric Silva
 * Create date: 02-Aug-2017
 * 
 * Change History:
 * 01-May-2019 Dagoberto Ceballos: Changed something...
 * 18-Nov-2021 Marcos Vazquez    : Refactoring and support for multiple signals.
 */

////////////////// ETHERNET //////////////////////////////////////
#include <Ethernet2.h>                          // use Industruino version
#define REMOTE_IP IPAddress(192, 168, 0, 46)      // MXSRVAPPS
//#define REMOTE_IP IPAddress(192, 168, 103, 105) // LOCAL DEV TEST

////////////////////////////////////////////////////////////////
// prepare LCD screen, output and input pins, ethernet data and
// start FSM
void setup() {
  // put your setup code here, to run once:
  lcdSetup();
  ioSetup();
  ethSetup(); 
  fsmSetup();
}

////////////////////// MAIN LOOP //////////////////////////////////////
// run the current state and, if transitioned to a new state, update
// accordingly. at the end an animation is used to indicate the script
// is not stuck
void loop() {
  fsmLoop();
  lcdIndicator(); 
}
