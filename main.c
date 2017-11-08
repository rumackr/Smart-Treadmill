/**
 * @file main.c
 * @author Reid Rumack (rumackr@msoe.edu)
 * @date 12 Sep 2017
 *
 * PROVIDES:
 * - setup and initalizeastion
 * - sets up and initalizes the LCD
 *   Cap sense pads 
 * - main program loop
 * - state advancement
 *
 */

#include <stdio.h>
#include "project.h"
#include "capSenseCtrl.h"
#include "profiles.h" 
#include "hartdetection.h"
#define USBFS_DEVICE    (0u)  //!< Macro for USB UART device
#define LINE_STR_LENGTH     (20u)
uint8_t capVector = 0x00;
volatile int hartRate = 0;  //!< current hart measured hart rate (in BPM)
volatile uint32_t beatTimes[5] = { 0 };//!<an array of time. each time is the time lapse between pulse

/**  CY_ISR
 * IST handler for the comparator interrupt
 * should execute every time the HARTBEAT signal goes over
 * VDDS/2 (1.65V0). This provides the dedication for the hart beat peak pulse
 * @param compISR Bound IRQ
 *
 */
CY_ISR(compISR) {

	/* Read Status register in order to clear the sticky Terminal Count (TC) bit 
	 * in the status register. Note that the function is not called, but rather 
	 * the status is read directly.
	 */
	COMP_INT_ClearPending();

	uint8_t timeReg[4];
	uint32_t time = 0;

	timeReg[0] = Time_0_Read();
	timeReg[1] = Time_1_Read();
	timeReg[2] = Time_2_Read();
	timeReg[3] = Time_3_Read();
	for (int i = 3; i >= 0; i--) {
		uint32_t tmp = timeReg[i];
		time = time << 8;
		time = (time) | (timeReg[i]);
	}

	for (int i = 4; i >= 0; i--) {
		//0 is newest
		beatTimes[i + 1] = beatTimes[i];
	}
	beatTimes[0] = time;
	ResetReg_Write(1u);
	CyDelay(2);
	ResetReg_Write(0u);

}
/** uartStrPrintLn
 * Tacks a given string at prints a new line over the usb uart.
 * Adjusts the uart setting to that of the receiver
 * @param str string to print
 */
void uartStrPrintLn(char* str) {
	if (str != NULL) {
		if (0u != USBUART_GetConfiguration()) {
			while (0u == USBUART_CDCIsReady())
				;
			USBUART_PutString(str);
			while (0u == USBUART_CDCIsReady())
				;
			USBUART_PutCRLF();
			while (0u == USBUART_CDCIsReady())
				;
			USBUART_PutData(NULL, 0u);
		}
	}

}
/** systemInit
 *  Initializes all systems
 */
void systemInit(){
	// binds isr location for the comparator interrupt
	COMP_INT_StartEx(compISR);
	LCD_Start();
	initHartBeat();
	/* Initialize baselines */
	USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);
	CapSense_Start();
	CapSense_InitializeAllBaselines();
}
/**
 * main fuction for the treadmill. Contains the main system loop.
 * @return program exit code
 */
int main(void) {
	enum state {
		RST, WAIT, SLEEP, RAMPUP, MONITOR, STOP
	} sysState;
	CyGlobalIntEnable; /* Enable global interrupts. */
	systemInit();
	sysState = RST;
	volatile uint16_t val = 0;
	for (;;) {
		/* Host can send double SET_INTERFACE request. */
		if (0u != USBUART_IsConfigurationChanged()) {
			/* Initialize IN endpoints when device is configured. */
			if (0u != USBUART_GetConfiguration()) {
				/* Enumeration is done, enable OUT endpoint to receive data
				 * from host. */
				USBUART_CDC_Init();
			}
		}

		/* Check whether the scanning of all enabled widgets is completed. */
		if (0u == CapSense_IsBusy()) {
			/* Update all baselines */
			CapSense_UpdateEnabledBaselines();

			/* Start scanning all enabled sensors */
			CapSense_ScanEnabledWidgets();
		}

		/* Display CapSense state using LED/LCD */

		switch (sysState) {
		case RST:
			LCD_Position(0, 3);
			LCD_PrintString("Welcome to");
			LCD_Position(1, 2);
			LCD_PrintString("My Treadmill");
			CyDelay(5000);
			LCD_Position(0, 3);
			LCD_PrintString("          ");
			LCD_Position(1, 2);
			LCD_PrintString("            ");

			sysState = WAIT;
			break;
		case WAIT:

			profileHandler();
			profileCycler();

			break;
		case SLEEP:

			LCD_Position(0, 3);
			// LCD_PrintString("          ");

			// LCD_PrintString("            ");

			// Looking for a left to right swipe to wake-up the system
			val = GetSliderPos();
			if (val != 0) {
				capVector = sliderPosition(val, capVector);
			}
			if (capVector == L_TO_R_SWIPE) {
				sysState = WAIT;
				capVector = 0x00;
			}

			break;
		case RAMPUP: 
            for(uint8_t i = 0; i<8; i++){
                // increas speed
                //wait 
                CyDelay(1000);
            }   
			break;
		case MONITOR:
            int newRate = calcHartRate(beatTimes, 5);
			char rateStr[16];
			/* report hart rate over usb uart. */
			sprintf(&rateStr[0], "HR: %d ", newRate);
			if (hartRate != newRate) {
				uartStrPrintLn(&rateStr[0]);
				LCD_Position(1, 0);
				LCD_PrintString(rateStr);
				hartRate = newRate;
			}
			break;
		case STOP:
			break;
		}
		uint8_t adcValue = ADC_SAR_GetResult8();
		dac_SetValue(adcValue);
	}
	return 0;
}

/* [] END OF FILE */
