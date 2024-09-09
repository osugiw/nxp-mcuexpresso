#include "PT6964.h"

// Variables declaration
volatile uint32_t g_systickCounter;

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

uint8_t convertNumber(uint8_t num)
{
	uint8_t converted;
	switch (num)
	{
		case (0x00):
			converted = NOL;
			break;
		case (0x01):
			converted = SATU;
			break;
		case (0x02):
			converted = DUA;
			break;
		case (0x03):
			converted = TIGA;
			break;
		case (0x04):
			converted = EMPAT;
			break;
		case (0x05):
			converted = LIMA;
			break;
		case (0x06):
			converted = ENAM;
			break;
		case (0x07):
			converted = TUJUH;
			break;
		case (0x08):
			converted = DELAPAN;
			break;
		case (0x09):
			converted = SEMBILAN;
			break;
	}
	return converted;
}

void writeByte(uint8_t byte)
{
  for (int i=0; i<8; i++)
	{
	  GPIO_PinWrite(GPIO, BoardPort, LED_CLK, 0);
	  GPIO_PinWrite(GPIO, BoardPort, LED_OUTPUT, byte&0x01);	// Write from LSB
	  byte = byte >> 1;
	  GPIO_PinWrite(GPIO, BoardPort, LED_CLK, 1);
	}
}

void writeCommand(uint8_t displayCommand)
{
	GPIO_PinWrite(GPIO, BoardPort, LED_STROBE, 0);
	writeByte(displayCommand);
	GPIO_PinWrite(GPIO, BoardPort, LED_STROBE, 1);
}

void writeData(uint8_t displayData)
{
	GPIO_PinWrite(GPIO, BoardPort, LED_STROBE, 0);
	writeByte(displayData);
	SysTick_DelayTicks(10U);
}

void turnOn()
{
	writeCommand(incrementAddress);	// Command 2 - Set Write data
	writeCommand(clearDisplay); // Command 3 - Clear RAM Display
	writeCommand(fourDigits); // Command 1
	writeCommand(displayOff); // Command 4 - Display off
	writeCommand(fourDigits); // Command 1
	writeCommand(brightnessLevel1);	// Command 4 - Display on
}

void brightnessSetting(uint8_t level)
{
	writeCommand(incrementAddress);	// Command 2 - Set Write data
	writeCommand(clearDisplay); // Command 3 - Clear RAM Display
	writeCommand(fourDigits); // Command 1
	writeCommand(displayOff); // Command 4 - Display off
	writeCommand(fourDigits); // Command 1
	writeCommand(level);	// Command 4 - Display on
}

void displayNilai(uint8_t ribuan, uint8_t ratusan, uint8_t puluhan, uint8_t satuan)
{
	writeCommand(incrementAddress);		// Command 2 - Set Write data
	GPIO_PinWrite(GPIO, BoardPort, LED_STROBE, 1);
	writeData(digit1Seg1);					// Command 3 - Set Address of 7 Segment
	writeData(ribuan);
	writeData(digit2Seg3);					// Command 3 - Set Address of 7 Segment
	writeData(ratusan);
	writeData(digit3Seg5);					// Command 3 - Set Address of 7 Segment
	writeData(puluhan);
	writeData(digit4Seg7);						// Command 3 - Set Address of 7 Segment
	writeData(satuan);
	GPIO_PinWrite(GPIO, BoardPort, LED_STROBE, 1);
	writeCommand(fourDigits); 				// Command 1
	writeCommand(brightnessLevel8);		// Command 4 - Display on
	SysTick_DelayTicks(40000U);
}
