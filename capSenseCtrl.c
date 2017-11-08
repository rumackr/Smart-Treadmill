/**
 * @file: capSenseCtrl.c
 * @author Reid Rumack
 * @date 12 Sep 2017
 * PROVIDES:
 * - cap sense initalizeastion funtion
 * - cap sense slider position getter
 * - Cap sense button interface 
 *
 */
#include <project.h>
#include <stdint.h>
#include "capSenseCtrl.h"
/**GetSliderPos
 * gets and returns the position of the slider
 *
 * @return postion of the slider, 0 if a finger is not on the slider
 * 	else it returns 0x0000 - 0x0064
 */
uint16_t GetSliderPos() {
	uint16_t pos = 0;
	/* Find Slider Position */
	pos = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
	/* Reset position */
	if (pos == 0xFFFFu) {
		pos = 0u;
	}
	return pos;
}
/** GetCapBtn0
 * checks to if the the capsense button 0 is touched
 * @return 1 for touched; 0 for not touched.
 */
uint8_t GetCapBtn0() {
	uint8_t val = 0;
	if (CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN)) {

		val = 1;
	} else {
		val = 0;
	}
	return val;
}
/** GetCapBtn1
 * checks to if the the capsense button 1 is touched
 * @return 1 for touched; 0 for not touched.
 */
uint8_t GetCapBtn1() {
	uint8_t val = 0;
	if (CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN)) {
		val = 1;
	} else {
		val = 0;
	}
	return val;
}
/**
 *
 * @param sliderVal
 * @param sliderFlags
 * @return
 */
uint8_t sliderPosition(volatile uint16_t sliderVal, uint8_t sliderFlags) {
	uint8_t positionVector = 0x00;
	if (sliderFlags == 0x00) {
		if (sliderVal < LEFT_CENTER) {
			positionVector = LEFT_TOUCHED;
		} else if (sliderVal > RIGHT_CENTER) {
			positionVector = RIGHT_TOUCHED;
		} else if ((sliderVal >= LEFT_CENTER) && (sliderVal <= RIGHT_CENTER)) {
			positionVector = (LEFT_TOUCHED | RIGHT_TOUCHED);
		}
	} else {
		positionVector = sliderFlags;
	}
	if ((sliderVal > LEFT_MAX) && (sliderVal < LEFT))
		(positionVector = positionVector | MASK_LEFT_MAX); //
	else if ((sliderVal >= LEFT) && (sliderVal < LEFT_CENTER))
		(positionVector = positionVector | MASK_LEFT_CENTER);
	else if ((sliderVal >= LEFT_CENTER) && (sliderVal < RIGHT_CENTER))
		(positionVector = positionVector | MASK_CENTER);
	else if ((sliderVal >= RIGHT_CENTER) && (sliderVal < RIGHT))
		(positionVector = positionVector | MASK_RIGHT_CENTER);
	else if ((sliderVal >= RIGHT) && (sliderVal < RIGHT_MAX))
		(positionVector = positionVector | MASK_RIGHT_MAX); //      

	return positionVector;
}


/*[] END OF FILE */
