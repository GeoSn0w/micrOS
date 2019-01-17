// 
// 
// 

#include "micrOS_Apps.h"
#include "IODisplay.h"
#include "kernel.h"
#include "Kernel_Returns.h"
#include "micrOS_Storage.h"

extern MCUFRIEND_kbv IODisplay;

kern_return_t menu_init() {
	if (setCurrentForeGroundPID(1) != KERN_SUCCESS) {
		return KERN_FAILURE;
	}
	isMenuOpen = 1; //We're in app.
	IODisplay.drawRect(45, 54, 394, 202, 0x9CDD);
	IODisplay.fillRect(46, 55, 392, 200, 0x8D3A);
	IODisplay.drawBitmap(416, 60, close_button, 16, 16, WHITE);
	IODisplay.drawRect(44, 53, 396, 204, WHITE);
	IODisplay.setCursor(50, 59);
	IODisplay.setTextColor(WHITE);
	IODisplay.print("MENU"); //Header
	IODisplay.drawBitmap(68, 85, terminal_icon_big, 64, 64, WHITE);
	IODisplay.drawBitmap(150, 85, files_big, 64, 64, WHITE);
	IODisplay.drawBitmap(220, 85, settings_big, 64, 64, WHITE);
	IODisplay.drawBitmap(285, 85, music, 64, 64, WHITE);
	IODisplay.drawBitmap(355, 85, calc_app, 64, 64, WHITE);
	//No more icons.
	AWAIT_TOUCH_SG(); //Wait for touch input.
	return KERN_SUCCESS;
}

int coreStorageEffaceableAlert() {
	isAlert = 1;
	setCurrentForeGroundPID(11);
	IODisplay.fillRoundRect(34, 36, 413, 240, 10, LessDarkPurple);
	IODisplay.fillRoundRect(47, 218, 187, 50, 15, DarkPurple); // Erase card
	IODisplay.setCursor(95, 231);
	IODisplay.setTextSize(3);
	IODisplay.print("Erase");
	IODisplay.fillRoundRect(248, 218, 187, 50, 15, DarkPurple); // Cancel
	IODisplay.setCursor(291, 231);
	IODisplay.print("Cancel");
	IODisplay.setTextSize(2);
	IODisplay.setCursor(104, 140);
	IODisplay.print(F("The card will be erased!"));
	IODisplay.setCursor(101, 170);
	IODisplay.print(F("Do you want to continue?"));
	IODisplay.drawBitmap(214, 75, info_icon, 32, 32, WHITE);
	isAlert = 0;
}
kern_return_t StorageSettings() {
	setCurrentForeGroundPID(10);
	inApp = 1; //Will change the dock, prevent accidental touches on other stuff and listen to the app
	set_bar_fill(LessDarkPurple);
	switchboard_set_bars(LessDarkPurple);
	IODisplay.fillRect(0, 20, 480, 270, DarkPurple);
	kernDisplayReload();
	//App begins
	extern struct Device LowLevelDeviceProviderForIO;
	IODisplay.setTextSize(3);
	IODisplay.setCursor(12, 30);
	IODisplay.print("micrOS Storage Media"); //Label	
	IODisplay.setTextSize(2);
	IODisplay.setCursor(12, 70);
	IODisplay.print("Micro SD Card Type: ");
	IODisplay.print(LowLevelDeviceProviderForIO.device_type);
	IODisplay.setCursor(12, 100);
	IODisplay.print("Partition Style: FAT");
	IODisplay.print(LowLevelDeviceProviderForIO.volumeTypeDec);
	IODisplay.setCursor(12, 130);
	IODisplay.print("Volume Size: ");
	IODisplay.print(LowLevelDeviceProviderForIO.volumeSizeInGB);
	IODisplay.print(" Gigabytes");
	IODisplay.setCursor(12, 160);
	IODisplay.print("Total Blocks: ");
	IODisplay.print(LowLevelDeviceProviderForIO.BlocksCount);
	IODisplay.fillRoundRect(34, 217, 413, 57, 10, LessDarkPurple);
	IODisplay.setTextSize(3);
	IODisplay.setCursor(184, 236);
	IODisplay.print("Erase Card");
	//IODisplay.drawBitmap(50, 220, MicroSDCard, 50, 50, WHITE);
	IODisplay.drawBitmap(128, 221, MicroSDCard, 50, 50, WHITE);
	//No more icons.
	AWAIT_TOUCH_SG(); //Wait for touch input.
	return KERN_SUCCESS;
}