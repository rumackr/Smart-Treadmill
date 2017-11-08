/* ========================================
 * FILENAME: capSenseCtrl.h
 * AUTHOR:   Reid Rumack
 * DATE:     12 Sep 2017
 * PROVIDES:
 * - cap sense initalizeastion funtion
 * - cap sense slider position getter
 * - Cap sense button interface 
 * ========================================
 */
#include <stdint.h>
#define LEFT_TOUCHED      0x40
#define MASK_LEFT_MAX     0x20
#define MASK_LEFT_CENTER  0x10
#define MASK_CENTER       0x08          
#define MASK_RIGHT_CENTER 0x04
#define MASK_RIGHT_MAX    0x02
#define RIGHT_TOUCHED     0x01
#define L_TO_R_SWIPE      0x7E //left-to-right swipe
#define R_TO_L_SWIPE      0x77 //right-to-left swipe
#define MASK_CENTER_TAP   0x81      

#define LEFT_MAX     0
#define LEFT         14
#define LEFT_CENTER  28       
#define RIGHT_CENTER 42
#define RIGHT        56
#define RIGHT_MAX    100

uint8_t capVector = 0x00;    //!< a vector that provides information about cap sense gestures


uint16_t GetSliderPos();
uint8_t GetCapBtn0();
uint8_t GetCapBtn1();
uint8_t sliderPosition(volatile uint16_t sliderVal, uint8_t sliderFlags);
/* [] END OF FILE */
