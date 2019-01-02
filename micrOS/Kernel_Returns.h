// Kernel_Returns.h

#ifndef _KERNEL_RETURNS_h
#define _KERNEL_RETURNS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#define KERN_SUCCESS 0
#define KERN_FAILURE -1
#define KERN_INVALID_OPERATION 9
#else
	#include "WProgram.h"
#endif


#endif

