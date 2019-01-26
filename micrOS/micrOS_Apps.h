// micrOS_Apps.h

#ifndef _MICROS_APPS_h
#define _MICROS_APPS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
    #include "kernel.h"
kern_return_t menu_init(void);
kern_return_t StorageSettings(void);
kern_return_t CoreSettings(void);
int coreStorageEffaceableAlert(void);
#define micro_App_Active_Ses_CoreMenu                1
#define micro_App_Active_Ses_CoreSettings			 5
#define micro_App_Active_Ses_CoreStorageSettings     10
#define micro_App_Active_Ses_CoreEraseUtils          11
#define micro_App_Active_Ses_CoreSwitchboard         99

// Core Storage
#define performErase TouchPoint.x>34 && TouchPoint.x<447 && TouchPoint.y>217 && TouchPoint.y<274 && inApp == 1 // Erase button, it will pop a warning.
#define doErase TouchPoint.x>47 && TouchPoint.x<234 && TouchPoint.y>218 && TouchPoint.y<268 && inApp == 1 // Erase button, confirmed. This will start the obliteration.
#define cancelErase TouchPoint.x>248 && TouchPoint.x<435 && TouchPoint.y>218 && TouchPoint.y<268 && inApp == 1// Cancel button, it will revert back to Core Storage Media

// Core Settings
#define performQuickResetWDT TouchPoint.x>1 && TouchPoint.x<480 && TouchPoint.y>217 && TouchPoint.y<252 && inApp == 1 //Reboot button

// Switchboard screen
#define menuButton TouchPoint.x>10 && TouchPoint.x<34 && TouchPoint.y>292 && TouchPoint.y<316 && inApp == 0 // Cancel button, it will revert back to Core Storage Media

// Menu objects
#define settingsApp TouchPoint.x>220 && TouchPoint.x<284 && TouchPoint.y>85 && TouchPoint.y<149 && isMenuOpen == true
#define menuExitButton TouchPoint.x>416 && TouchPoint.x<432 && TouchPoint.y>60 && TouchPoint.y<76 && isMenuOpen == true

// Misc objects
#define appExitButton TouchPoint.x>10 && TouchPoint.x<34 && TouchPoint.y>292 && TouchPoint.y<316 && inApp == 1 // Cancel button, it will revert back to Core Storage Media




#else
	#include "WProgram.h"
#endif


#endif

