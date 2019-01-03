/*
micrOS Arduino Operating System by GeoSn0w (@FCE365)
- Stage Two Bootloader
- First code to run after the Stage One Bootloader passes control.
- Performs the sanity checks, reads fuses, reads lock bits, reads device signature and serial number, sets the watchdog, detects the display adapter, 
  initializes the verbose or graphical boot UI then jumps back to micrOS.ino which then displays the micrOS Desktop through kernel.cpp

  The watchdog
*/

#include "Stage2Bootloader.h"
#include "Kernel_Returns.h"
#include <Flash.h>
#include <avr/boot.h>
#include <EEPROM.h>
#include <avr/wdt.h>
#include "DeviceTree.h"


extern MCUFRIEND_kbv IODisplay;
byte signature1, signature2, signature3, lockBits, HighFuse, LowFuse, ExtFuse;
#define _GET_LOCK_BITS() __AddrToZByteToSPMCR_LPM( (void flash *) 0x0001, 0x09 )
#define _GET_LOW_FUSES() __AddrToZByteToSPMCR_LPM( (void flash *) 0x0000, 0x09 )
#define _GET_HIGH_FUSES() __AddrToZByteToSPMCR_LPM( (void flash *) 0x0003, 0x09 )
#define _GET_EXTENDED_FUSES() __AddrToZByteToSPMCR_LPM( (void flash *) 0x0002, 0x09 )
// I defined these for you so that you don't have to mess with the register too much.
// If you have any questions, drop me a line at @FCE365
#define WatchDog16ms (1 << WDIE) | (1 << WDE) | (0 << WDP3) | (0 << WDP2) | (0 << WDP1) |(0 << WDP0) // 16ms
#define WatchDog32ms (1 << WDIE) | (1 << WDE) | (0 << WDP3) | (0 << WDP2) | (0 << WDP1) |(1 << WDP0) // 32ms
#define WatchDog64ms (1 << WDIE) | (1 << WDE) | (0 << WDP3) | (0 << WDP2) | (1 << WDP1) |(0 << WDP0) // 64ms
#define WatchDog4Secs (1 << WDIE) | (1 << WDE) | (1 << WDP3) | (1 << WDP2) | (0 << WDP1) |(0 << WDP0) // 4 seconds
#define WatchDog8Secs (1 << WDIE) | (1 << WDE) | (1 << WDP3) | (0 << WDP2) | (0 << WDP1) |(1 << WDP0) // 8 Seconds, default on micrOS.

void setup_WatchDog_ForSession() {
	cli(); // Disable all interrupts to prevent accidental failure in configuration!
	wdt_reset(); //Reset the Watchdog to prevent an accidental reset during config
				 /*
				 The Watchdog is controlled via the WDTCSR register which is a 1 byte (8-Bit) register.
				 WDTCSR configuration:
				 WDIE = 1: Interrupt Enable
				 WDE = 1 :Reset Enable
				 The current configuration is WDP3 1, WDP2 0, WDP1 0, WDP0 1 - This means 8000ms watchdog timeout, maximum possible on this platform.
			    */
	WDTCSR |= (1 << WDCE) | (1 << WDE); //Set the watchdog to Config mode
	//It's advised to do the settings right after entering the configuration mode because it has to be done in 4 CPU cycles.

	WDTCSR = WatchDog8Secs;
	sei(); // Re-enable all interrupts. The configuration is done. Do keep in mind that the Watchdog itself creates interrupts so we must re-enable these.
	// You can also set an interrupt with ISR(WDT_vect){ // }; but avoid Serial stuff as it may prevent the watchdog from resetting properly.
	return;
}
void get_device_signature()
{
	//Parse data from the flash chip
	signature1 = boot_signature_byte_get(0);
	signature2 = boot_signature_byte_get(2);
	signature3 = boot_signature_byte_get(4);
	LowFuse    = boot_lock_fuse_bits_get(0);
	HighFuse   = boot_lock_fuse_bits_get(3);
	ExtFuse    = boot_lock_fuse_bits_get(2);
	lockBits   = boot_lock_fuse_bits_get(1);

	//Display it during boot via IODisplay
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
	IODisplay.setCursor(2, 173);
	IODisplay.print("LockBits = 0x");
	IODisplay.print(lockBits, HEX);
	IODisplay.setCursor(2, 183);
	IODisplay.print("Extended Fuse = 0x");
	IODisplay.print(ExtFuse, HEX);
	IODisplay.setCursor(2, 193);
	IODisplay.print("High Fuse = 0x");
	IODisplay.print(HighFuse, HEX);
	IODisplay.print(" | Low Fuse = 0x");
	IODisplay.print(LowFuse, HEX);
	IODisplay.setCursor(2, 203);
	IODisplay.print("Device Serial Number : ");

	for (uint8_t i = 14; i < 24; i += 1) {
		IODisplay.print(" 0x");
		IODisplay.print(boot_signature_byte_get(i), HEX);
	}
	return;
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
	if (true) { //Disabled for the moment because I have to reimplement these checks somewhere else.
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
		get_device_signature();
	    delay(3000); // Just enough to be able to read the fuses.
		setup_WatchDog_ForSession(); // Do not set earlier unless you perfectly time the resets of the watchdog timer.
		Serial.println(F("micrOS Environment is ready!"));
	return;
}
kern_platform_t perform_sanity_chck() {
#ifdef __AVR_ATmega2560__
	return 7; //Arduino Mega 2560 or compatible clones.
#endif
	return 0; //Invalid platform. Even if you made it to execute this, it is not advised to boot.
}
