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
#ifndef HARTDETECTION_H
#define HARTDETECTION_H
#include <stdint.h>

void initHartBeat(void);
uint16_t getSample(void);
int calcHartRate(volatile uint32_t beatTimes[], uint8_t numbBeats);
#endif /* HARTDETECTION_H */   
/* [] END OF FILE */
