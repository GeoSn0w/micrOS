// DeviceTree.h

#ifndef _DEVICETREE_h
#define _DEVICETREE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#if defined (__AVR_ATmega2560__)
#  define __CPUNAME "ATmega2560"
#else
#  if !defined(__COMPILING_AVR_LIBC__)
#    warning "Could not detect device type"
#  endif
#endif

#else
	#include "WProgram.h"
#endif


#endif



