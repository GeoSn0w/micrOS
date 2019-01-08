#include "kernel.h"
#include <MCUFRIEND_kbv.h>
#include "IODisplay.h"
#include "Kern_Errors.h"
uint16_t BootMode = 0x00000;
uint16_t debug = 0x01;
uint8_t * heapptr, *stackptr, *R31;
int kern_err_count = 0;
MCUFRIEND_kbv IODisplay;
bool isMenuOpen = false;
bool SysSdutDownReqConfirm = false;
bool isCharging = false;
bool inApp = false;
bool isWirelessConnected = false;
proc_return_t PID = 0;
ucred_identity_card_t IdentityCard;
String CURRENT_FOREGROUND_PID = "com.micrOS.kernel";

kern_return_t micrOS_SwitchBoard() { // micrOS Desktop
	IODisplay.fillScreen(TestMenuBG);
	switchboard_set_bars(0x5454);
	IODisplay.setCursor(1, 4);
	IODisplay.setTextColor(WHITE);
	IODisplay.setTextSize(2);
	IODisplay.print(kUSERNAME);
	switchboard_set_misc();
	switchboard_set_wallpaper();
	get_battery_status();
	switchboard_integrity_check();
}
kern_return_t switchboard_set_bars(uint16_t UIColor) { //called from any app that wants to set its own colors.
	IODisplay.fillRect(0, 0, 480, 20, UIColor); //Draws a statusbar
	IODisplay.fillRoundRect(0, 290, 480, 40, 12, UIColor); //Draws the dock
	return KERN_SUCCESS;
}
kern_return_t set_bar_fill(uint16_t ThemeScheme) {
	IODisplay.fillRect(0, 290, 480, 35, ThemeScheme); //Draws background of the dock.
	return KERN_SUCCESS;
}
void switchboard_integrity_check() {
	if (kern_err_count != 0) {
		kernel_I_haz_panic("Error!");
	}
}

kern_return_t kernel_I_haz_panic(String panic_reason) {
	IODisplay.drawRect(44, 53, 396, 204, 0x60C4);
	IODisplay.fillRect(46, 55, 392, 200, 0xC188);
	IODisplay.drawRect(46, 55, 392, 200, 0x60C4);
	IODisplay.setCursor(49, 59);
	IODisplay.setTextColor(WHITE);
	IODisplay.print("micrOS System");
	IODisplay.drawBitmap(200, 110, kern_panic_icon, 64, 64, WHITE);
	IODisplay.setCursor(70, 195);
	IODisplay.print("An unrecoverable kernel issue");
	IODisplay.setCursor(110, 215);
	IODisplay.print("has occurred. (");
	IODisplay.print(panic_reason);
	IODisplay.print(")");
}

kern_return_t switchboard_set_misc() {
	IODisplay.setTextColor(WHITE);
	IODisplay.setCursor(215, 3);
	IODisplay.println("12:31");
	if (inApp) {
		IODisplay.drawBitmap(10, 292, exit_icon, 24, 24, WHITE);
	}
	else {
		IODisplay.drawBitmap(10, 292, menu_icn, 24, 24, WHITE);
	}
	if (!inApp) {
		IODisplay.drawBitmap(65, 292, cell_pad, 24, 24, WHITE);
		IODisplay.drawBitmap(130, 292, SMS, 24, 24, WHITE);
		IODisplay.drawBitmap(195, 292, settings, 24, 24, WHITE);
		IODisplay.drawBitmap(260, 292, files, 24, 24, WHITE);
		IODisplay.drawBitmap(325, 292, camera_app_icon, 24, 24, WHITE);
		IODisplay.drawBitmap(390, 292, terminal_icon, 24, 24, WHITE);
		IODisplay.drawBitmap(450, 292, shutdown_icon, 24, 24, WHITE);
	}
	if (isWirelessConnected) {
		IODisplay.drawBitmap(100, 2, wifi_signal, 16, 16, WHITE); //Connected.
	}
	else {
		IODisplay.drawBitmap(100, 2, no_signal, 16, 16, WHITE); //Not connected.
	}
	return KERN_SUCCESS;
}

kern_return_t switchboard_set_wallpaper() {
	IODisplay.setTextColor(WHITE);
	IODisplay.setCursor(289, 235);
	IODisplay.setTextSize(5);
	IODisplay.println(F("micrOS"));
	IODisplay.setTextSize(2);
	return KERN_SUCCESS;
}
void buildAlert(char message[], char sub[], char title[], int x, int y, int xsub, int ysub, bool dismissable) { //let's you build custom alerts for micrOS
	IODisplay.drawRect(44, 53, 396, 204, WHITE);
	IODisplay.fillRect(46, 55, 392, 200, LightGRAY);
	IODisplay.drawRect(46, 55, 392, 200, WHITE);
	IODisplay.drawLine(46, 76, 435, 76, WHITE);
	IODisplay.drawLine(46, 77, 435, 77, WHITE);
	IODisplay.drawLine(46, 78, 435, 78, WHITE);
	IODisplay.setCursor(50, 59);
	IODisplay.setTextColor(WHITE);
	IODisplay.setCursor(168, 110);
	IODisplay.setTextSize(4);
	IODisplay.print("[ ! ]");
	IODisplay.setTextSize(2);
	IODisplay.setCursor(49, 59);
	IODisplay.print(title);
	IODisplay.setCursor(x, y);
	IODisplay.print(message);
	IODisplay.setCursor(xsub, ysub);
	IODisplay.print(sub);
	if (dismissable) {
		IODisplay.setCursor(393, 59);
		IODisplay.print("[X]");
	}
}
void kern_panic() { //Triggered when a fatal exception occurrs!
	buildAlert("A fatal exception occurred!", generalAdvice, generalTitle, 78, 160, 70, 190, false);
}
kern_return_t dump() {
	IODisplay.fillScreen(TestMenuBG);
	IODisplay.setTextSize(1);
	IODisplay.setCursor(0, 2);
	delay(1000);
	//dumpRam(kernel, 0x800, 1200);
	IODisplay.println();
	return;
}
kern_return_t dump_memory() {
	stackptr = (uint8_t *)malloc(4);
	heapptr = stackptr;
	free(stackptr);
	stackptr = (uint8_t *)(SP);
	R31 = (uint8_t *)(EIND);
	return KERN_SUCCESS;
}
kern_return_t getAvailableMemory() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
	return KERN_SUCCESS;
}
kern_return_t shutdown() {
	IODisplay.drawRect(45, 54, 394, 202, 0xE2EE);
	IODisplay.fillRect(46, 55, 392, 200, 0xC188);
	IODisplay.setCursor(50, 60);
	IODisplay.setTextColor(WHITE);
	IODisplay.print("micrOS System");
	IODisplay.setCursor(393, 59);
	IODisplay.drawBitmap(416, 60, close_button, 16, 16, WHITE);
	IODisplay.drawBitmap(200, 110, switch_off, 64, 64, WHITE);
	IODisplay.fillRect(52, 220, 379, 30, 0x60C4);
	IODisplay.setCursor(100, 226);
	IODisplay.print("Confirm System Shutdown");
	return;
}
kern_return_t AWAIT_TOUCH_SG() {
	pinMode(XM, OUTPUT);
	pinMode(YP, OUTPUT);
	return KERN_SUCCESS;
}
kern_return_t sigareport(int signal) {
	if (debug == 0x01 && KERN_FUSE == "DEVELOPMENT") {
		Serial.println("[FAILURE] The application was terminated. SIGABRT ");
		Serial.print(signal);
	}
	return KERN_SUCCESS;
}
kern_return_t kernRegisterNewApp() {
	inApp = true;
	kernDisplayReload();
	return;
}
kern_return_t kernKillActiveApp() {
	inApp = false;
	IODisplay.setTextSize(2);
	micrOS_SwitchBoard();
	return;
}
kern_return_t kernDisplayReload() {
	IODisplay.setCursor(1, 4);
	IODisplay.setTextColor(WHITE);
	IODisplay.setTextSize(2);
	IODisplay.print(kUSERNAME);
	switchboard_set_misc();
	get_battery_status();
	return KERN_SUCCESS;
}
bool checkID(ucred_identity_card_t ID) {
	Serial.print(F("[KERNEL] Performing Identity Check for app: "));
	Serial.println(ID);
	int overlay = 0;
	if (ID == "PurpleCalc") {
		overlay = 4;
	}
	else if (ID == "PurplePlayer") {
		overlay = 5;
	}
	else if (ID == "PurpleFiles") {
		overlay = 6;
	}
	else if (ID == "PurpleTerminal") {
		overlay = 3;
	}
	else if (ID == "PurpleTest") {
		overlay = 7;
	}
	else if (ID == "PurpleSettings") {
		overlay = 8;
	}
	else if (ID == "PurpleMenu") {
		overlay = 9;
	}
	else {
		overlay = 0;
	}
	Serial.print("[KERNEL] New App Overlay is  ");
	Serial.println(overlay);
	switch (overlay) {
	case 4: CURRENT_FOREGROUND_PID = "com.micrOS.purplecalc";
		PID = 4;
		return KERN_SUCCESS;
	case 5: CURRENT_FOREGROUND_PID = "com.micrOS.purpleplayer";
		PID = 5;
		return KERN_SUCCESS;
	case 6: CURRENT_FOREGROUND_PID = "com.micrOS.purplefiles";
		PID = 6;
		return KERN_SUCCESS;
	case 3: CURRENT_FOREGROUND_PID = "com.micrOS.terminal";
		PID = 3;
		return KERN_SUCCESS;
	case 7: CURRENT_FOREGROUND_PID = "com.micrOS.FactoryFA";
		PID = 7;
		return KERN_SUCCESS;
	case 8: CURRENT_FOREGROUND_PID = "com.micrOS.Settings";
		PID = 8;
		return KERN_SUCCESS;
	case 9: CURRENT_FOREGROUND_PID = "com.micrOS.PurpleMenu";
		PID = 9;
		return KERN_SUCCESS;
	case 0: CURRENT_FOREGROUND_PID = "com.micrOS.kernel";
		PID = 0; // PID 0 => The kernel itself, so yeah...
		return KERN_FAILURE; //Something is not right down here.
	}
}
ucred_t check_entitlements(bool isDebugged, bool isSystemApp, bool hasCustomTheme, bool hasFileSystemAccess, bool writesEEPROM, bool readsEEPROM, bool hasGPIOAccess) {
	Serial.print(F("[KERNEL] Performing entitlements check for "));
	Serial.println(IdentityCard);
	if (checkID(IdentityCard) != KERN_SUCCESS) {
		kernel_I_haz_panic(APPID_ERR);
		return KERN_FAILURE;
	}
	bool appShouldRun = true;
	if (isDebugged && debug == 0x1 && KERN_FUSE == "DEVELOPMENT") {
		appShouldRun = true;
	}
	else if (isDebugged && debug != 0x1 || KERN_FUSE != "DEVELOPMENT") {
		appShouldRun = false;
		kernel_I_haz_panic(ENTITLEMENT_ERROR);
		return 0x00000000;
	}
	else if (!isDebugged) {
		appShouldRun = true;
	}
	if (isSystemApp) {
		appShouldRun = true;
	}
	else if (!isSystemApp && hasGPIOAccess) {
		appShouldRun = false;
		kernel_I_haz_panic(ENTITLEMENT_ERROR);
		return 0x00000000;
	}
	if (hasGPIOAccess && isSystemApp) {
		appShouldRun = true;
	}
	else if (!hasGPIOAccess && isSystemApp) {
		appShouldRun = true;
	}
	else if (hasGPIOAccess && !isSystemApp) {
		appShouldRun = false;
		kernel_I_haz_panic(ENTITLEMENT_ERROR);
		return 0x00000000;
	}
	if (hasCustomTheme) {
		//In this case, the App will specify a custom color scheme at runtime.
		appShouldRun = true;
	}
	else {
		switchboard_set_bars(0x5454); //We default to micrOS Blue.
		appShouldRun = true;
	}
	if (hasFileSystemAccess && isSystemApp) {
		appShouldRun = true;
	}
	else {
		kernel_I_haz_panic(ENTITLEMENT_ERROR);
		return 0x00000000; //You're not allowed to access the ROOT FS.
	}
	if (writesEEPROM && isSystemApp) {
		appShouldRun = true;
	}
	else {
		appShouldRun = false;
		kernel_I_haz_panic(ENTITLEMENT_ERROR);
		return 0x00000000; //You're not allowed to access the EEPROM
	}
	if (readsEEPROM && isSystemApp) {
		appShouldRun = true;
	}
	else {
		kernel_I_haz_panic(ENTITLEMENT_ERROR);
		return 0x00000000; //You're not allowed to access the EEPROM
	}
	if (appShouldRun) {
		Serial.println(F("[KERNEL] App successfully passed sanity checks in kernel. App is starting now..."));
		return 1;
	}
	else {
		Serial.println(F("[KERNEL] App failed sanity checks in kernel and it will not start."));
		kernel_I_haz_panic(ENTITLEMENT_ERROR);
		return 0x00000000;
		sigabrt(9);
	}
}
kern_return_t sigabrt(kern_return_t panic_reason) {
	
	switch (panic_reason) {
	case 1: buildAlert("Something went damn wrong!!", "Please restart your program.", "[!] Application Error", 78, 160, 70, 190, true);
		sigareport(1);
	case 2: buildAlert(generalMessage, generalAdvice, generalTitle, 78, 160, 70, 190, false);
		sigareport(2);
	case 3: buildAlert(generalMessage, generalAdvice, generalTitle, 78, 160, 70, 190, true);
		sigareport(3);
	case 4: buildAlert(generalMessage, generalAdvice, generalTitle, 78, 160, 70, 190, false);
		sigareport(4);
	case 5: buildAlert(generalMessage, generalAdvice, generalTitle, 78, 160, 70, 190, false);
		sigareport(5);
	case 6: buildAlert(generalMessage, generalAdvice, generalTitle, 78, 160, 70, 190, true);
		sigareport(6);
	case 7: kernel_I_haz_panic(ENTITLEMENT_ERROR);
		sigareport(7);
	case 8: buildAlert(generalMessage, generalAdvice, generalTitle, 78, 160, 70, 190, false);
		sigareport(8);
	case 9: kernel_I_haz_panic(ENTITLEMENT_ERROR); //Entitlements not corresponding.
		sigareport(9);
	}
	return KERN_FAILURE;
}