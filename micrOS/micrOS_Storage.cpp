// 
// micrOS Storage Media System
// 

#include "micrOS_Storage.h"
#include "kernel.h"
#include "Kernel_Returns.h"
#include <SD.h>

Sd2Card MicroSD;
SdVolume IOLowLevelVolume;
uint32_t VolumeSize;

const int SD_CS = 10; //Pin 10 for MCUFRIEND's SDCard! Change accordingly.

kern_return_t initialize_storage_driver() {
	pinMode(SS, OUTPUT); //has to be set as output.
	if (!SD.begin(SD_CS, 11, 12, 13)) {
		return KERN_FAILURE; //We failed...
	}
	else {
		if (getStorageMediaDevice() == KERN_SUCCESS) {
			return KERN_SUCCESS; //Yay
		}
		return KERN_FAILURE;
	}
}

struct Device LowLevelDeviceProviderForIO;

kern_return_t getStorageMediaDevice() {
	while (!MicroSD.init(SPI_HALF_SPEED, 10, 11, 12, 13)) {
		Serial.println(F("Failed to initialize the card, please make sure it is plugged in, and the Chip Select is properly specified!"));
		return KERN_FAILURE;
	}
	switch (MicroSD.type()) {
		case SD_CARD_TYPE_SD1:
			strcpy(LowLevelDeviceProviderForIO.device_type, "SD1");
			break;
		case SD_CARD_TYPE_SD2:
			strcpy(LowLevelDeviceProviderForIO.device_type, "SD2");
			break;
		case SD_CARD_TYPE_SDHC:
			strcpy(LowLevelDeviceProviderForIO.device_type, "SDHC");
			break;
		default:
			strcpy(LowLevelDeviceProviderForIO.device_type, "NIL");
			return KERN_FAILURE;
	}
	if (IOLowLevelVolume.init(MicroSD)) {
		LowLevelDeviceProviderForIO.device_initialized = true;
	}
	else {
		return KERN_FAILURE;
	}
	LowLevelDeviceProviderForIO.volumeType = 1;
	LowLevelDeviceProviderForIO.volumeTypeDec = (IOLowLevelVolume.fatType(), DEC);
    VolumeSize =  IOLowLevelVolume.blocksPerCluster();     // Clusters = a collection of blocks
	VolumeSize *= IOLowLevelVolume.clusterCount();         // Clusterfuck
	VolumeSize *= 512;                                     // SD card blocks are always 512 bytes in size
	LowLevelDeviceProviderForIO.volumeSizeInB = VolumeSize;
	VolumeSize /= 1024;
	LowLevelDeviceProviderForIO.volumeSizeInKB = VolumeSize;
	VolumeSize /= 1024;
	LowLevelDeviceProviderForIO.volumeSizeInMB = VolumeSize;
	return KERN_SUCCESS;
}

