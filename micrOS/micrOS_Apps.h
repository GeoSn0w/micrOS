// micrOS_Apps.h

#ifndef _MICROS_APPS_h
#define _MICROS_APPS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
    #include "kernel.h"
kern_return_t menu_init(void);
#else
	#include "WProgram.h"
#endif


#endif

