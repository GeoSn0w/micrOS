// 
// micrOS Storage Media System
// 
#include <SD.h>
#include "micrOS_Storage.h"
#include "kernel.h"
#include "Kernel_Returns.h"

Sd2Card MicroSD;
SdVolume IOLowLevelVolume;
uint32_t VolumeSize;

 //Pin 10 for MCUFRIEND's SDCard! Change accordingly.

kern_return_t initialize_storage_driver() {
	SPI.begin();
	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);
	if (!SD.begin(10, 11, 12, 13)) {
#ifdef EMILY_KERN_DEBUG
		Serial.println(F("Failed to initialize the card"));
#endif
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
#ifdef EMILY_KERN_DEBUG
		Serial.println(F("Failed to initialize the card, please make sure it is plugged in, and the Chip Select is properly specified!"));
#endif
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
#ifdef EMILY_KERN_DEBUG
		Serial.println("SD Card Type is not available");
#endif
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
#ifdef EMILY_KERN_DEBUG
	Serial.println("[storagemediad] SD Card initialized.");
	Serial.print("[storagemediad] Mounted Storage Media type: ");
	Serial.println(LowLevelDeviceProviderForIO.device_type);
	Serial.print("[storagemediad] Partition Style: FAT");
	Serial.println(LowLevelDeviceProviderForIO.volumeTypeDec);
	Serial.print("[storagemediad] Volume size: ");
	Serial.print(LowLevelDeviceProviderForIO.volumeSizeInKB);
	Serial.println(" Kilobytes");
	Serial.print("[storagemediad] Volume size: ");
	Serial.print(LowLevelDeviceProviderForIO.volumeSizeInGB);
	Serial.println(" Gigabytes");
	Serial.print("[storagemediad] Clusters: ");
	Serial.println(IOLowLevelVolume.clusterCount());
	Serial.print("[storagemediad] Blocks per cluster: ");
	Serial.println(LowLevelDeviceProviderForIO.BlocksCount);
#endif
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
#ifdef EMILY_KERN_DEBUG
				Serial.println(F("[StorageMediad] Failed to format SD card!"));
#endif
				return KERN_FAILURE;
			}
			if ((walk++) % 32 == 31);
			firstBlock += ERASE_SIZE;
		} while (firstBlock < MicroSD.cardSize());
	return KERN_SUCCESS;
}

