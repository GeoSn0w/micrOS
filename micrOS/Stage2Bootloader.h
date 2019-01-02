// Stage2Bootloader.h

#ifndef _STAGE2BOOTLOADER_h
#define _STAGE2BOOTLOADER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
    #include "kernel.h"
    #include "IODisplay.h"
int boot_verbose(void);
kern_platform_t perform_sanity_chck(void);
#else
	#include "WProgram.h"
#endif


#endif

