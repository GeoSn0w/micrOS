// micrOS_Storage.h.h
#ifndef _MICROS_STORAGE.H_h
#define _MICROS_STORAGE.H_h

#include "Kernel_Returns.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
kern_return_t initialize_storage_driver(void);
kern_return_t getStorageMediaDevice(void);

struct Device {
	char  device_type[24];
	int	  volumeType = 0; // 1 = Fat
	int   volumeTypeDec = 0; // 16 or 32
	long  volumeSizeInKB = 0;
	long  volumeSizeInMB = 0;
	long  volumeSizeInB = 0;
	bool  device_initialized = false;
	uint32_t IOVolumeSize;
};

#else
	#include "WProgram.h"
#endif


#endif

