
# Test Bench Listener

  

Reads signals from the test bench (PLC) every time the trigger pin is activated by the same
PCL and sends them to the remote server.
It is divided in 7 files just for the sake of readability:

## ETHERNET

- Initialize the ethernet module.

- Read MAC address from the RTC.

- Check if the device is online.

  

## FSM

- Simple implementation of a finite state machine.

- Transition between offline, connecting, connected and active states:

* offline. Device is not connected to the network.

* disconnected. Remote server is not responding UDP messages.

* connected. Device is waiting for the PLC's trigger.

* active. Device send TCP message to remote server and awaits response.

  

## IO

- Pin setup.

- Monitor trigger pin used by PLC.

- Read inputs from PLC.

- Write result to output pins.

  

## LCD

- Initialize LCD screen.
# Test Bench Listener

  

Reads signals from the test bench (PLC) every time the trigger pin is activated by the same
PCL and sends them to the remote server.
It is divided in 7 files just for the sake of readability:

## ETHERNET

- Initialize the ethernet module.

- Read MAC address from the RTC.

- Check if the device is online.

  

## FSM

- Simple implementation of a finite state machine.

- Transition between offline, connecting, connected and active states:

* offline. Device is not connected to the network.

* disconnected. Remote server is not responding UDP messages.

* connected. Device is waiting for the PLC's trigger.

* active. Device send TCP message to remote server and awaits response.

  

## IO

- Pin setup.

- Monitor trigger pin used by PLC.

- Read inputs from PLC.

- Write result to output pins.

  

## LCD

- Initialize LCD screen.

- Centralize messages displayed.

- Control brightness changes.

  

## TCP

- Send TCP message to remote server.

- Awaits remote server response.

  

## UDP

- Initialize UDP client.

- "Ping" remote server.

  

###  To be able to build the project you will need to

1. Install Arduino IDE (https://www.arduino.cc/en/software)

< Version used during development is 1.8.15 >

2. Copy content in libraries directory to the Arduino directory (My Documents\Arduino\libraries)

3. More Documentation in oficial GitHub page 
-  Click Here --> [Industruino](https://github.com/Industruino/) 

- Centralize messages displayed.

- Control brightness changes.

  

## TCP

- Send TCP message to remote server.

- Awaits remote server response.

  

## UDP

- Initialize UDP client.

- "Ping" remote server.

  

###  To be able to build the project you will need to

1. Install Arduino IDE (https://www.arduino.cc/en/software)

< Version used during development is 1.8.15 >

2. Copy content in libraries directory to the Arduino directory (My Documents\Arduino\libraries)