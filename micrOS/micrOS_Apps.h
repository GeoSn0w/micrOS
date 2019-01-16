// micrOS_Apps.h

#ifndef _MICROS_APPS_h
#define _MICROS_APPS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
    #include "kernel.h"
kern_return_t menu_init(void);
kern_return_t StorageSettings(void);
int coreStorageEffaceableAlert(void);
#define performErase p.x>34 && p.x<447 && p.y>217 && p.y<274 && inApp == 1 // Erase button, it will pop a warning.
#define doErase p.x>34 && p.x<447 && p.y>217 && p.y<274 && inApp == 1 // Erase button, confirmed. This will start the obliteration.
#define cancelErase p.x>248 && p.x<435 && p.y>219 && p.y<269 && inApp == 1 // Cancel button, it will revert back to Core Storage Media

// Switchboard screen
#define menuButton p.x>10 && p.x<34 && p.y>292 && p.y<316 && inApp == 0 // Cancel button, it will revert back to Core Storage Media

// Menu objects
#define settingsApp p.x>220 && p.x<284 && p.y>85 && p.y<149 && isMenuOpen == true

#else
	#include "WProgram.h"
#endif


#endif

