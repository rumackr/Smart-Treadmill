/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <stdio.h>
#include <inttypes.h>
#include "project.h"

#include "buzzer.h"

void buzzerPlayTone(const uint32_t ms_duration,  uint16_t frq) {

    // put a boundary on the frequency
//    if(frq < 300){
//        frq = 300;
//    }
    if(frq > 3000){
        frq = 3000;
    }
    
   	uint32_t delay = (uint32_t)1000000.0 / (2.0 * frq);
    uint32_t duration =  (delay/1000)*ms_duration;
    for(int i = 0; i < duration; i++){
	  BUZZ_Write(1);
	  CyDelayUs(delay);
	  BUZZ_Write(0);
	  CyDelayUs(delay);
	}

}
/* [] END OF FILE */
