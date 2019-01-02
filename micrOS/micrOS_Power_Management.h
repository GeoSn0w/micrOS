// micrOS_Power_Management.h

#ifndef _MICROS_POWER_MANAGEMENT_h
#define _MICROS_POWER_MANAGEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
int battery_exhausted(void);
int get_battery_status(void);
void sleepNow();
extern bool low_battery_popup;
#else
	#include "WProgram.h"
#endif


#endif

