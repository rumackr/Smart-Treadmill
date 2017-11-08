/**
 * @file profiles.c
 * @author Reid Rumack
 * @date 12 Sep 2017
 * PROVIDES:
 * - cap sense initalizeastion funtion
 * - cap sense slider position getter
 * - Cap sense button interface
 *
 */
#include "capSenseCtrl.h"
#include "project.h"
#include "profiles.h"
/**
 *
 */
void profileCycler() {
	if (GetCapBtn0()) {
		if (sysProfile == prof4) {
			sysProfile = prof0;
		} else {
			sysProfile++;
		}
		CyDelay(250);
	} else if (GetCapBtn1()) {
		if (sysProfile == prof0) {
			sysProfile = prof4;
		} else {
			sysProfile--;
		}
		CyDelay(250);
	}

}

void profileHandler() {
	switch (sysProfile) {
	case prof0:
		LCD_Position(0, 5);
		//    LCD_PrintString("prof0");
		break;
	case prof1:
		LCD_Position(0, 5);
		LCD_PrintString("prof1");
		break;
	case prof2:
		LCD_Position(0, 5);
		LCD_PrintString("prof2");
		break;
	case prof3:
		LCD_Position(0, 5);
		LCD_PrintString("prof3");
		break;
	case prof4:
		LCD_Position(0, 5);
		LCD_PrintString("prof4");
		break;
	}

}

/* [] END OF FILE */
