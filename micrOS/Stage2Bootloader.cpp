
#include "Stage2Bootloader.h"
#include "Kernel_Returns.h"
#include <Flash.h>
#include <avr/boot.h>
#include <EEPROM.h>
#include "DeviceTree.h"

extern MCUFRIEND_kbv IODisplay;
byte signature1, signature2, signature3;

void print_signature()
{
	signature1 = boot_signature_byte_get(0);
	signature2 = boot_signature_byte_get(2);
	signature3 = boot_signature_byte_get(4);

	IODisplay.print(F("Device Signature: "));
	IODisplay.print("0x");
	IODisplay.print(signature1, HEX);
	IODisplay.print(signature2, HEX);
	IODisplay.print(signature3, HEX);
	IODisplay.setCursor(2, 163);

	if (signature1 == 0x1E) { // Got ATMEL!
		switch (signature2) {
		case 0x95:
			if (signature3 == 0x0F)
				IODisplay.print(F("Found Device: ATmega328P)"));
			else if (signature3 == 0x14)
				IODisplay.print(F("Found Device: ATmega328)"));
			break;
		case 0x98: // Got Mega?
			if (signature3 == 0x1)
				IODisplay.print(F("Found Device: ATmega2560)"));
		    break;
		}
	}
	else {
		IODisplay.print(F("Could not parse device signature."));
	}
}
int boot_verbose() {
	if (debug == 0x1) {
		Serial.begin(9600);
		Serial.println(F("micrOS Bootloader v1.003"));
	}
	uint16_t DisplayEngine = IODisplay.readID();
	if (DisplayEngine == 0xEFEF) DisplayEngine = 0x9486;
	Serial.println(F("micrOS is booting..."));
		IODisplay.reset();
		IODisplay.begin(DisplayEngine);
		IODisplay.setRotation(1);
		IODisplay.setTextSize(4);
		IODisplay.fillScreen(BLACK);
	    IODisplay.setTextColor(WHITE);
		IODisplay.setCursor(170, 150);
		IODisplay.print(F("micrOS"));
		delay(3000);
		IODisplay.fillScreen(BLACK);
		IODisplay.setTextSize(1);
		IODisplay.setCursor(2, 3);
		IODisplay.print(F("micrOS for Arduino MEGA"));
		delay(1000);
		IODisplay.setCursor(2, 13);
		IODisplay.print(kMicroVersion);
		delay(200);
		IODisplay.setCursor(2, 23);
		IODisplay.print(F(kBootLoaderREV));
		delay(200);
		IODisplay.setCursor(2, 33);
		IODisplay.print(F("Detecting device in Kernel Mode..."));
		delay(200);
		IODisplay.setCursor(2, 43);
		IODisplay.print(F("Loaded kernel Display for IODisplay component with ID: 0x"));
		IODisplay.println(DisplayEngine, HEX);
		delay(200);
		IODisplay.setCursor(2, 53);
		IODisplay.print(F("Loading micrOS RGB Color Descriptors for IODisplay..."));
		IODisplay.setCursor(2, 63);
		delay(400);
		IODisplay.print(F("Loading micrOS RED Color Descriptor for IODisplay with ID: 0xF800"));
		IODisplay.setCursor(2, 73);
		delay(400);
		IODisplay.print(F("Loading micrOS Green Color Descriptor for IODisplay with ID: 0x07E0"));
		IODisplay.setCursor(2, 83);
		delay(400);
		IODisplay.print(F("Loading micrOS Blue Color Descriptor for IODisplay with ID: 0x001F"));
		IODisplay.setCursor(2, 93);
		delay(400);
		IODisplay.print(F("Waiting for Platform Check..."));
	if (perform_sanity_chck() != 0) {
		IODisplay.setCursor(2, 103);
		delay(400);
		IODisplay.print(F("Checking /dev/sda1..."));
		IODisplay.setCursor(2, 113);
		delay(400);
		if (check_sda() == KERN_SUCCESS) {
			IODisplay.print(F("Successfully mounted /dev/sda1!"));
			delay(400);
		}
		else {
			IODisplay.setCursor(2, 113);
			IODisplay.print(F("Failed to mount /dev/sda1! Storage media not ready!"));
			delay(400);
		}
		IODisplay.setCursor(2, 123);
		IODisplay.print(F("Platform config has arrived!"));
		delay(1000);
	}
	else {
		IODisplay.setCursor(2, 103);
		delay(400);
		IODisplay.print(F("Checking /dev/sda1..."));
		IODisplay.setCursor(2, 113);
		delay(400);
		if (0) {
			IODisplay.print(F("Successfully mounted /dev/sda1!"));
			delay(400);
		}
		else {
			IODisplay.setCursor(2, 113);
			IODisplay.print(F("[!] Failed to mount /dev/sda1! Storage media not ready!"));
			delay(400);
		}
		IODisplay.setCursor(2, 123);
		IODisplay.print(F("Platform config is missing!"));
		delay(400);
		IODisplay.setCursor(2, 133);
		IODisplay.print(F("[!] Cannot boot micrOS. Incompatible platform or microcontroller."));
		return -1;
	}
	delay(400);
	IODisplay.setCursor(2, 133);
	IODisplay.print(F("Preparing micrOS Environment..."));
	delay(400);
	if (true) {
		IODisplay.setCursor(2, 143);
		IODisplay.print(F("Successfully micrOS."));
		delay(200);
	}
	else {
		IODisplay.setCursor(2, 143);
		IODisplay.print(F("MOFI: The process com.geosn0w.switchboard has been terminated with signal -1"));
		IODisplay.setCursor(2, 153);
		IODisplay.print(F("MOFI: Incorrect signature for com.geosn0w.switchboard. Aborting..."));
		delay(400);
		IODisplay.setCursor(2, 163);
		IODisplay.print(F("CPU_HALTED"));
		return -1;
	}
		IODisplay.setCursor(2, 153);
		print_signature();
	    delay(3000);
		Serial.println(F("micrOS Environment is ready!"));
	return;
}
kern_platform_t perform_sanity_chck() {
#ifdef __AVR_ATmega2560__
	return 7; //Arduino Mega 2560 or compatible clones.
#endif
	return 0; //Invalid platform. Even if you made it to execute this, it is not advised to boot.
}
