
#include "DeviceTree.h"
#include "Kern_Errors.h"
#include "micrOS_Apps.h"
#include "micrOS_Graphics_Cache.h"
#include <Vcc.h>
#include "micrOS_Power_Management.h"
#include <SD.h>
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
	extern struct registeredTouchFrameService RegisteredPolicies;
	RegisteredPolicies.currentlyActiveOverlay = 0;
}

// the loop function runs over and over again until power down or reset
void loop() {
	wdt_reset(); // Reset the watchdog
	TSPoint p = ts.getPoint();
	AWAIT_TOUCH_SG();
	if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
		p.x = map(p.x, TS_MINX, TS_MAXX, 0, RESOLUTION_W);  //This is necessary to be able to have proper touch control. Wish I knew this earlier...
		p.y = map(p.y, TS_MAXY, TS_MINY, 0, RESOLUTION_H);
		Serial.print(F("[TouchEvent] Registered touch at X = ")); Serial.print(p.x); Serial.print(F(" | Y = ")); Serial.println(p.y);
		touchEvalAtPoint(p);
		//Moved to the kern.
	}
	/*
	else if (p.x>317 && p.x<344 && p.y>454 && p.y<342 && isMenuOpen == true) {
		Serial.print("\nMenu Close button pressed.");
		IODisplay.fillRect(44, 53, 396, 172, TestMenuBG);
		switchboard_set_wallpaper();
		isMenuOpen = false;
		AWAIT_TOUCH_SG();
	}
	else if (p.x>458 && p.x<335 && p.y>262 && p.y<452 && SysSdutDownReqConfirm == true) {
		Serial.print("\nShutdown Pop-up Close button pressed.");
		SysSdutDownReqConfirm = false;
		AWAIT_TOUCH_SG();
		IODisplay.fillRect(44, 53, 450, 172, TestMenuBG);
		switchboard_set_wallpaper();

	}
	else if (p.x>858 && p.x<905 && p.y>216 && p.y<260 && inApp == false) {
		Serial.print("\nShutdown button pressed.");
		AWAIT_TOUCH_SG();
		isMenuOpen = false;
		SysSdutDownReqConfirm = true;
		shutdown();
	}
	else if (p.x>710 && p.x<760 && p.y>297 && p.y<870 && SysSdutDownReqConfirm == true) {
		Serial.print("\nShutdown button pressed.");
		sleepNow();
		AWAIT_TOUCH_SG();

	}
	*/
}
