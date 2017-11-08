/** ========================================
 * FILENAME: main.c
 * AUTHOR:   Reid Rumack
 * DATE:     12 Sep 2017
 * PROVIDES:
 *   - function for aquiering a Hartbeat
 *   - calculating the beat rate
 * ========================================
 */
#include <project.h>
#include "hartdetection.h"
/**
 *
 */
void initHartBeat() {
	/* Starts PGA component */
	PGA_Start();
	// sets gain to 2
	PGA_SetGain(PGA_GAIN_16);
	//sets to low power (we only need low frq signals) 
	PGA_SetPower(PGA_LOWPOWER);
	dac_Start();

	ADC_SAR_Init();
	//starts ADC
	ADC_SAR_Start();
	ADC_SAR_StartConvert();
	SCCT_Comp_Start();
}
/**
 *
 * @return
 */
uint16_t getSample() {
	uint16 adcVal = 0;
	//start ADC convertion
	//gets the covnerted ADC value
	adcVal = ADC_SAR_GetResult16();

	return adcVal;
}

/**
 *
 * @param beatTimes
 * @param numbBeats
 * @return
 */
int calcHartRate(volatile uint32_t beatTimes[], uint8_t numbBeats) {

	double period = 0;
	uint32_t timeSum = 0;
	uint32_t numbNonZero = 0;
	for (int i = 0; i < numbBeats; i++) {
		if (beatTimes[i] != 0) {
			timeSum += beatTimes[i];
			numbNonZero++;
		}
	}
	// calculates period
	period = (double) timeSum / numbNonZero;
	return (int) ((1 / period) * 60000);
}

/* [] END OF FILE */
