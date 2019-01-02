// micrOS_Apps.h

#ifndef _MICROS_APPS_h
#define _MICROS_APPS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
void menu_init(void);
#else
	#include "WProgram.h"
#endif


#endif

