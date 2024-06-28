This mini project deals with writing a baremetal code using c for UART communication between two 8051 microcontrollers.

Circuitary:
    There are two mcu's in the circuit, mcu1 and mcu2 are connected, Tx of mcu1 is connected to Rx of mcu2 and vice-versa.
    mcu2 is connected with a LCD display, it displays the receicved message here.

Working:
    The mcu1 Initiates the communication and transmits the message byte by byte.
    The Serial interrupt recognizes the reception of data and stores SBUF register into a array as the bytes arrives.
    When active low hardware interrupt is occured by making pin13 low. The mcu2 display the stored data in the LCD display.

Code requirements:
    To get the proper result we need to programm the Timers and Counters of 8051.
    We need to configure the mode of UART in 8051, here we used mode1 which transfers 8bits with a starting and ending bits, it do not include parity bits.
    We need to configure the Serial Interrupt in order to receive data.

Note:
    The devices may have different commands and may have different pin confige read the datasheet carefully, in this project i have used multisim as simulation software.

