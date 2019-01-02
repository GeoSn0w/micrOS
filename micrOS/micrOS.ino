#include "micrOS_Apps.h"
#include "micrOS_Graphics_Cache.h"
#include <Vcc.h>
#include "micrOS_Power_Management.h"
#include <SD.h>
#include "micrOS_Storage.h"
#include "Kernel_Returns.h"
#include "Stage2Bootloader.h"
#include "kernel.h"
#include "IODisplay.h"
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
extern MCUFRIEND_kbv IODisplay;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 200); //Touch Panel initialization

void setup() {
	boot_verbose();
	micrOS_SwitchBoard();
}

// the loop function runs over and over again until power down or reset
void loop() {
	TSPoint p = ts.getPoint();
	AWAIT_TOUCH_SG();
	if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
		Serial.print("\nRegistered touch at X = "); Serial.print(p.x); Serial.print(" | Y = "); Serial.print(p.y);
		if (p.x>919 && p.x<939 && p.y>887 && p.y<890 && inApp == 0) {
			menu_init();
		}
		else if (p.x>875 && p.x<894 && p.y>907 && p.y<942 && inApp == 1) {
			kernKillActiveApp();
		}
		else if (p.x>457 && p.x<420 && p.y>450 && p.y<870 && isMenuOpen == true) {
			//
		}
		else if (p.x>450 && p.x<495 && p.y>788 && p.y<860 && isMenuOpen == true) {
			Serial.print("\nTerminal App launched.");
			AWAIT_TOUCH_SG();
			inApp = 1;
			//terminal_app();
		}
	}
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
	else if (p.x>458 && p.x<335 && p.y>262 && p.y<452 && low_battery_popup == true) {
		Serial.print("\nClose button pressed.");
		IODisplay.fillRect(44, 53, 396, 172, TestMenuBG);
		switchboard_set_wallpaper();
		low_battery_popup = false;
		AWAIT_TOUCH_SG();

	}
	else if (p.x>458 && p.x<335 && p.y>262 && p.y<452 && isMenuOpen == true) {
		Serial.print("\nMenu Close button pressed.");
		IODisplay.fillRect(44, 53, 396, 172, TestMenuBG);
		switchboard_set_wallpaper();
		isMenuOpen = false;
		AWAIT_TOUCH_SG();

	}
	else if (p.x>861 && p.x<895 && p.y>329 && p.y<369 && inApp == false) {
		Serial.println("\nLaunching Terminal app...\n");
		inApp = 1;
		isMenuOpen = false;
		//terminal_app();
		AWAIT_TOUCH_SG();

	}
	else if (p.x>391 && p.x<453 && p.y>453 && p.y<520 && isMenuOpen == true) {
		
		// Claculator ->
	}

}
