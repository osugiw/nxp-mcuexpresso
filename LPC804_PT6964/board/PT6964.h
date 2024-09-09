/*
 * PT6964.h
 *
 *  Created on: Sep 9, 2022
 *      Author: KDS-LTP-0415
 */

#ifndef PT6964_H_
#define PT6964_H_

#include "board.h"
#include "pin_mux.h"

// GPIO and PORT Number
#define BoardPort	 		0U
#define LED_STROBE			BOARD_INITPINS_LED_STB_PIN
#define LED_CLK				BOARD_INITPINS_LED_CLK_PIN
#define LED_OUTPUT			BOARD_INITPINS_LED_DIO_PIN

// Function Definition
void SysTick_Handler(void);
void SysTick_DelayTicks(uint32_t n);
void writeByte(uint8_t byte);
void writeCommand(uint8_t displayCommand);
void writeData(uint8_t displayData);
void turnOn();
void brightnessSetting(uint8_t level);
uint8_t convertNumber(uint8_t num);
void displayNilai(uint8_t ribuan, uint8_t ratusan, uint8_t puluhan, uint8_t satuan);

// 7 Segment Display settings
#define NOL 0x3f
#define SATU 0x06
#define DUA 0x5b
#define TIGA 0x4f
#define EMPAT 0x66
#define LIMA 0x6d
#define ENAM 0x7d
#define TUJUH 0x07
#define DELAPAN 0x7f
#define SEMBILAN 0x6f

// Digits Settings
#define fourDigits 0x00
#define fiveDigits 0x01
#define sixDigits 0x02
#define sevenDigits 0x03

// Data Settings Command
#define fixedAddress 0x44
#define incrementAddress 0x40

// Address Setting Command - DIGIT0 (LEFT) TO DIGIT13 (RIGHT)
#define clearDisplay 0xc0
#define digit1Seg0 0x00  // REC, RAND, PAUSE, USB, CARD, 0 ARROW:00.00, MIC L-R, MHZ, MUSIC, VIDEO
#define digit1Seg1 0x01 // REC, RAND, PAUSE, USB, CARD, 0:00.00, MIC L-R, MHZ, MUSIC, VIDEO
#define digit2Seg2 0x02 // REC, RAND, PAUSE, USB, CARD, 0 ARROW:00.00, MIC L-R, MHZ, MUSIC, VIDEO
#define digit2Seg3 0x03 // REC, RAND, PAUSE, USB, CARD, 0 ARROW:00.00, MIC L-R, MHZ, MUSIC, VIDEO
#define digit3seg4 0x04 // 0 ARROW 00.00
#define digit3Seg5 0x05 // 0 ARROW 00.00
#define digit4Seg6 0x06 // 0 ARROW 00.00.0
#define digit4Seg7 0x07 // REC, RAND, PLAY, PAUSE, USB, CARD, 0 ARROW:00.00, MIC L-R, BAZZ, MHZ, MUSIC, VIDEO
#define digit5Seg8 0x08 // 0 ARROW 00.00.0
#define digit5Seg9 0x09 // 0 ARROW 00.00.0
#define digit6SegA 0x0a // REC, RAND, PLAY, PAUSE, USB, CARD, 0 ARROW:00.00, MIC L-R, BAZZ, MHZ, MUSIC, VIDEO
#define digit6SegB 0x0b
#define digit7SegC 0x0c
#define digit7SegD 0x0d

// Brightness Setting Command
#define displayOff 0x80
#define brightnessLevel1 0x88
#define brightnessLevel2 0x89
#define brightnessLevel3 0x8a
#define brightnessLevel4 0x8b
#define brightnessLevel5 0x8c
#define brightnessLevel6 0x8d
#define brightnessLevel7 0x8e
#define brightnessLevel8 0x8f

// Timer Value
#define fiveSec 0x05
#define tenSec 0x0a
#define twentySec 0x014
#define thirtySec 0x01e
#define fiftySec 0x32
#define ninetySec 0x5a
#define oneHundredSec 0x64
#define twoHundredSec 0xc8
#endif /* PT6964_H_ */
