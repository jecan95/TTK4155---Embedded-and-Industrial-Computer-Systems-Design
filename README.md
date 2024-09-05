# TTK4155---Embedded-and-Industrial-Computer-Systems-Design
The TTK4155 Term Project involves creating a computer-controlled electromechanical ping pong game. The project is comprehensive, requiring substantial lab work throughout the semester. It is structured into smaller weekly exercises for manageable progression.

## System Overview
The system is structured into two main parts, Node 1 and Node 2, which communicate via a CAN bus.

- **Node 1**: Consists of a breadboard integrating an ATmega162 microcontroller with various components including an A/D converter for joystick and touch inputs, SRAM for additional memory, an OLED display for user interface, and a MAX233 for RS232 communication.

- **Node 2**: Built around an Arduino Due with an ATSAM3X8e microcontroller and includes a BT840 for Bluetooth connectivity, logic level converters, an OpAmp for signal amplification, and interfaces to control a servo and solenoid for physical movements in the game.

![alt text](https://github.com/jecan95/TTK4155---Embedded-and-Industrial-Computer-Systems-Design/blob/main/Images/20231115_144630.jpg)

## Parts to complete

1. **Initial Microcontroller and RS-232 Setup**: Assemble the microcontroller circuit and establish RS-232 communication for data exchange.

2. **Address Decoding and External RAM**: Implement address decoding for memory mapping and integrate external RAM for expanded data storage.

3. **A/D Conversion and Joystick Input**: Set up analog-to-digital conversion for the joystick, enabling user control of the game.

4. **OLED Display and User Interface**: Create an interface on the OLED display for user interaction and feedback during the game.

5. **SPI and CAN Controller**: Configure the Serial Peripheral Interface (SPI) for component communication and the Controller Area Network (CAN) for inter-node messaging.

6. **ARM Cortex-M3 and Node Communication**: Initialize the ARM Cortex-M3 microcontroller and establish communication protocols between different system nodes.

7. **Servo and IR Control**: Implement pulse width modulation to control servo mechanisms for game actions and integrate infrared sensors for game event detection.

8. **Motor and Solenoid Control**: Utilize encoders and solenoids to manage the motion aspects of the ping pong game, ensuring accurate and responsive play.

[Watch the video](https://www.youtube.com/watch?v=b1AdgdpmUUQ)




