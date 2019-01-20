#include <SDConfigFile.h>
#include <SD.h>
#include "DeviceTree.h"
#include "Kern_Errors.h"
#include "micrOS_Apps.h"
#include "micrOS_Graphics_Cache.h"
#include <Vcc.h>
#include "micrOS_Power_Management.h"
#include "micrOS_Storage.h"
#include "Kernel_Returns.h"
#include "Stage2Bootloader.h"
#include <avr/wdt.h>
#include "kernel.h"
#include "IODisplay.h"
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Flash.h>
#include <avr/boot.h>
#include <EEPROM.h>
#include "DeviceTree.h"
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>

extern MCUFRIEND_kbv IODisplay;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //Touch Panel initialization

void setup() {
	wdt_reset();
	boot_verbose();
	micrOS_SwitchBoard();
	inApp = 0;
}

void loop() {
	wdt_reset(); // Reset the watchdog
	TSPoint p = ts.getPoint();
	AWAIT_TOUCH_SG();
	if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
		p.x = constrain(map(p.x, TS_MAXX, TS_MINX, 0, RESOLUTION_W),0, RESOLUTION_W); //This is necessary to be able to have proper touch control. Wish I knew this earlier...
		p.y = constrain(map(p.y, TS_MINY, TS_MAXY, 0, RESOLUTION_H),0, RESOLUTION_H);
#ifdef EMILY_KERN_DEBUG
		Serial.print(F("[TouchEvent] Registered touch at X = ")); Serial.print(p.x); Serial.print(F(" | Y = ")); Serial.println(p.y);
#endif
		touchEvalAtPoint(p);
		//Moved to the kern.
	}
}
