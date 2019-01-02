// 
// 
// 

#include "micrOS_Storage.h"
#include "kernel.h"
#include "Kernel_Returns.h"
#include <SD.h>

Sd2Card MicroSD;
SdVolume sda1;
const int SD_CS = 10; //Pin 10 for MCUFRIEND's SDCard! Change accordingly.

int check_sda() {
	pinMode(SS, OUTPUT); //has to be set as output.
	if (!SD.begin(SD_CS, 11, 12, 13)) {
		return KERN_FAILURE; //We failed...
	}
	else {
		return KERN_SUCCESS; //Yay
	}
}

