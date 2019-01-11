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
		Serial.println(F("Failed to initialize the card"));
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
		Serial.println("SD Card initialized ");
	}
	else {
		Serial.println("SD Card Type is not available");
		return KERN_FAILURE;
	}
	LowLevelDeviceProviderForIO.volumeType = 1;
	LowLevelDeviceProviderForIO.volumeTypeDec = IOLowLevelVolume.fatType();
    VolumeSize =  IOLowLevelVolume.blocksPerCluster();     // Clusters = a collection of blocks
	VolumeSize *= IOLowLevelVolume.clusterCount();         // Clusterfuck
	VolumeSize /= 2;                                       // SD card => 512 bytes
	LowLevelDeviceProviderForIO.volumeSizeInKB = VolumeSize;
	LowLevelDeviceProviderForIO.volumeSizeInGB = (float)VolumeSize / 1e+6;
	LowLevelDeviceProviderForIO.BlocksCount = IOLowLevelVolume.blocksPerCluster() * IOLowLevelVolume.clusterCount();
	return KERN_SUCCESS;
}

kern_return_t eraseStorageMediaAtPath() {
	uint32_t const ERASE_SIZE = 262144L;
	uint32_t firstBlock = 0;
	uint32_t lastBlock;
	uint16_t walk = 0;
		do {
			lastBlock = firstBlock + ERASE_SIZE - 1;
			if (lastBlock >= MicroSD.cardSize()) lastBlock = MicroSD.cardSize() - 1;
			if (!MicroSD.erase(firstBlock, lastBlock)) {
				Serial.println(F("[StorageMediad] Failed to format SD card!"));
			}
			if ((walk++) % 32 == 31);
			firstBlock += ERASE_SIZE;
		} while (firstBlock < MicroSD.cardSize());
	Serial.println(F("[StorageMediad] Successfully formatted SD card!"));
	return KERN_SUCCESS;
}

