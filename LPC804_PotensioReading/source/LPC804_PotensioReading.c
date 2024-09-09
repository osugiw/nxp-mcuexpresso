/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    LPC804_PotensioReading.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC804.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_power.h"

// ADC Configuration
#define ADC_POTENTIO		ADC
#define ADC_CHANNEL			3U				// A1 Pin
#define ADC_CLOCK_SOURCE	kCLOCK_Fro
#define ADC_CLOCK_DIVIDER	1U

// Function
static void adcInit(void);
void SysTick_Handler(void);
void SysTick_DelayTicks(uint32_t n);

// Variables
adc_result_info_t potentioReading;
const uint32_t adc_12bitFullRange = 4096U;
volatile uint32_t g_systickCounter;

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	// Attach 12 MHz clock to USART0 for debug console
	CLOCK_Select(BOARD_DEBUG_USART_CLK_ATTACH);

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    // Delay Setup for 1 ms
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
    	while(1){}
    }

    // Attach Free Running Oscillator to ADC0
    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1U);

    // Power on ADC by disabling peripheral
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);
    PRINTF("Potensio Reading Example from Arduino Pin A0\r\n");

	#if !(defined(FSL_FEATURE_ADC_HAS_NO_CALIB_FUNC) && FSL_FEATURE_ADC_HAS_NO_CALIB_FUNC)
		uint32_t frequency = 0U;
		/* Calibration after power up. */
	#if defined(FSL_FEATURE_ADC_HAS_CALIB_REG) && FSL_FEATURE_ADC_HAS_CALIB_REG
		ADC_POTENTIO->CTRL |= ADC_CTRL_BYPASSCAL_MASK;
		frequency = CLOCK_GetFreq(kCLOCK_BusClk);
		if (true == ADC_DoOffsetCalibration(ADC_POTENTIO, frequency))
	#else
	#if defined(SYSCON_ADCCLKDIV_DIV_MASK)
		frequency = CLOCK_GetFreq(DEMO_ADC_CLOCK_SOURCE) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
	#else
		frequency = CLOCK_GetFreq(DEMO_ADC_CLOCK_SOURCE);
	#endif /* SYSCON_ADCCLKDIV_DIV_MASK */
		if (true == ADC_DoSelfCalibration(ADC_POTENTIO, frequency))
	#endif /* FSL_FEATURE_ADC_HAS_CALIB_REG */
		{
			PRINTF("ADC Calibration Done.\r\n");
		}
		else
		{
			PRINTF("ADC Calibration Failed.\r\n");
		}
	#endif /* FSL_FEATURE_ADC_HAS_NO_CALIB_FUNC */

	adcInit();
	PRINTF("Configuration done!\r\n");

	#if defined(FSL_FEATURE_ADC_HAS_CTRL_RESOL) & FSL_FEATURE_ADC_HAS_CTRL_RESOL
		PRINTF("ADC Full Range: %d\r\n", adc_12bitFullRange);
	#endif /* FSL_FEATURE_ADC_HAS_CTRL_RESOL */
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
    	//GETCHAR();	// Get input from terminal and trigger the converter by software
    	ADC_DoSoftwareTriggerConvSeqA(ADC_POTENTIO);

    	while(!ADC_GetChannelConversionResult(ADC_POTENTIO, ADC_CHANNEL, &potentioReading)){}
    	PRINTF("potentioReading.result		= %d\r\n", potentioReading.result);
    	PRINTF("potentioReading.channelNumber	= %d\r\n", potentioReading.channelNumber);
    	PRINTF("\r\n");
    	SysTick_DelayTicks(1000U);
    }
}

static void adcInit(void)
{
	adc_config_t adcConfigStruct;
	adc_conv_seq_config_t adcConvSeqConfigStruct;

	/* Configure the converter. */
	#if defined(FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE) & FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE
	    adcConfigStruct.clockMode = kADC_ClockSynchronousMode; /* Using sync clock source. */
	#endif                                                     /* FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE */
	    adcConfigStruct.clockDividerNumber = ADC_CLOCK_DIVIDER;
	#if defined(FSL_FEATURE_ADC_HAS_CTRL_RESOL) & FSL_FEATURE_ADC_HAS_CTRL_RESOL
	    adcConfigStruct.resolution = kADC_Resolution12bit;
	#endif /* FSL_FEATURE_ADC_HAS_CTRL_RESOL */
	#if defined(FSL_FEATURE_ADC_HAS_CTRL_BYPASSCAL) & FSL_FEATURE_ADC_HAS_CTRL_BYPASSCAL
	    adcConfigStruct.enableBypassCalibration = false;
	#endif /* FSL_FEATURE_ADC_HAS_CTRL_BYPASSCAL */
	#if defined(FSL_FEATURE_ADC_HAS_CTRL_TSAMP) & FSL_FEATURE_ADC_HAS_CTRL_TSAMP
	    adcConfigStruct.sampleTimeNumber = 0U;
	#endif /* FSL_FEATURE_ADC_HAS_CTRL_TSAMP */
	#if defined(FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE) & FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE
	    adcConfigStruct.enableLowPowerMode = false;
	#endif /* FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE */
	#if defined(FSL_FEATURE_ADC_HAS_TRIM_REG) & FSL_FEATURE_ADC_HAS_TRIM_REG
	    adcConfigStruct.voltageRange = kADC_HighVoltageRange;
	#endif /* FSL_FEATURE_ADC_HAS_TRIM_REG */
	ADC_Init(ADC_POTENTIO, &adcConfigStruct);

	// Includes channel DEMO_ADC_SAMPLE_CHANNEL_NUMBER
	adcConvSeqConfigStruct.channelMask 		= (1U << ADC_CHANNEL);		// assigning ADC pin or channel with masking
	adcConvSeqConfigStruct.triggerMask 		= 0U;
	adcConvSeqConfigStruct.triggerPolarity  = kADC_TriggerPolarityPositiveEdge;
	adcConvSeqConfigStruct.enableSingleStep = false;
	adcConvSeqConfigStruct.enableSyncBypass = false;
	adcConvSeqConfigStruct.interruptMode    = kADC_InterruptForEachSequence;

	ADC_SetConvSeqAConfig(ADC_POTENTIO, &adcConvSeqConfigStruct);	// Assigning sequence configuration for ADC_POTENTIO to SEQA
	ADC_EnableConvSeqA(ADC_POTENTIO, true);			// Enable sequence A conversion
	ADC_DoSoftwareTriggerConvSeqA(ADC_POTENTIO);	// Clear the result register.

	// Reading adc conversion reading from potensio
	while(!ADC_GetChannelConversionResult(ADC_POTENTIO, ADC_CHANNEL, &potentioReading)){}
	ADC_GetConvSeqAGlobalConversionResult(ADC_POTENTIO, &potentioReading);
}

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
