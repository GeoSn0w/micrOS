// Kern_Errors.h

#ifndef _KERN_ERRORS_h
#define _KERN_ERRORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#define SWITCHBOARD_ERR "0x264A"
#define APPMENU_ERR "0x221A"
#define BOOTTIME_ERR "0x001F"
#define KERNEL_ERR "0x221F"
#define UNKNOWN_ERR "0x000A"
#define SERIAL_ERR "0x2121"
#define ENTITLEMENT_ERROR "0xFF69"
#define APPID_ERR "0x000FF"
#define SERIAL_ERR "0x2121"
#define TOUCHSCREEN_ERR "0x41FF"
#define TFT_ERR "0x42FF"
#define DIAG_ERR "0x00FF"
#define RW_MOUNT_SD_ERR "0x01FF"
#define KERN_FAILURE 1
#define KERN_SUCCESS 0
#define KERN_ERR_11 "Fatal exception occured in the CoreOS."
extern char generalMessage[];
extern char generalAdvice[];
extern char generalTitle[];
#else
	#include "WProgram.h"
#endif


#endif

