${ProjName}:
USART_Wakeup_Master


Intended purpose:
* To demonstrate low power mode wakeup of a slave lpc8xx, by its on-chip USART,
  using externally generated USART activity by a master lpc8xx. 
  Current consumption can be measured on the slave, if desired.


Functional description:
* The master project is intended to run concurrently with project USART_Wakeup_Slave, 
  using two interconnected lpc8xx Max boards, one each for master and slave.
  
* For the master project, user input/output is through the debug UART, which is configured in
  chip_setup.h and Serial.c. Connect a terminal emulator to the appropriate VCOM or USB
  com port.
  
* The slave project communicates with the master via USART.
  
* When the master project runs, the user is prompted to enter '0', '1', or '2'
  to put the slave into Sleep, Deep-sleep, or Power-down mode, respectively.

* The slave board's target enters the low power mode selected, and is awakened by a USART transfer
  generated by the master board, when the user types 'Esc' after a prompt.


External connections:
* The master and slave boards must be connected as per the #defines in the main c files and the SWM settings:
  // SWM settings for USART1 (master board) ... connect to ... SWM settings for USART1 (slave board)
  // SCLK_PIN = U1_SCLK on master board     ... connect to ... SCLK_PIN = U1_SCLK on slave board
  // TXD_PIN = U1_TXD on master board       ... connect to ... RXD_PIN = U1_RXD on slave board


Program Flow (Master board):
* This example runs at 30 MHz. See chip_setup.h and SystemInit().

* main() routine
  1. Clocks are enabled. 
  
  2. The SWM is configured for U1_SCLK, and U1_TXD.
  
  3. USART1 and its clocking are configured for the defined baud rate, synchronous master mode, 8 data bits, no parity, 1 stop bit
     and code execution enters the main while(1) loop.
 
  4. The user is prompted to enter '0', '1', or '2', to put the slave into one of the low power modes
     (Sleep, Deep-sleep, or Power-down respectively).
  
  5. Either '0', '1', or '2' is transmitted by USART1.
  
  6. The user is prompted to type [Esc] to wake up the slave.
  
  7. One byte is transmitted by USART1, which wakes up the slave, and the process repeats.

  
This example runs from Flash. 


To run this code:
  1. Build
  2. Debug
  3. Reset the previously programmed slave board
  4. Run
OR:
  1. Program to flash
  2. Reset the master board
  3. Reset the slave board

Note: It may be necessary to power-cycle the board in order to regain control of the reset button after programming.




