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
#include <stdint.h>

void initHartBeat(void);
uint16_t getSample(void);
int calcHartRate(volatile uint32_t beatTimes[], uint8_t numbBeats);
/* [] END OF FILE */
