#include "micrOS_Power_Management.h"
#include "micrOS_Graphics_Cache.h"
#include "IODisplay.h"
#include <Vcc.h>
#include <avr/sleep.h>
const float VccMin = 0.0;
const float VccMax = 5.0;
const float VccCorrection = 1.0 / 1.0;
Vcc vcc(VccCorrection);
int wakePin = 2;
int sleepStatus = 0;
int count = 0;
bool low_battery_popup = false;
extern MCUFRIEND_kbv IODisplay;
int battery_exhausted() {
	low_battery_popup = true;
	IODisplay.drawRect(45, 54, 394, 202, 0xE2EE);
	IODisplay.fillRect(46, 55, 392, 200, 0xC188);
	IODisplay.setCursor(50, 60);
	IODisplay.setTextColor(WHITE);
	IODisplay.print("micrOS System");
	IODisplay.setCursor(393, 59);
	IODisplay.drawBitmap(416, 60, close_button, 16, 16, WHITE);
	IODisplay.drawBitmap(200, 110, low_batt, 64, 64, WHITE);
	IODisplay.setCursor(80, 200);
	IODisplay.print("Battery exhausted! Recharge.");
	return;
}
int get_battery_status() {
	IODisplay.drawRect(451, 4, 20, 12, WHITE); //battery body x, y, w, h
	IODisplay.fillRect(451, 4, 17, 12, WHITE); //filling
	IODisplay.fillRect(471, 6, 3, 8, WHITE); // battery tip
	IODisplay.setCursor(402, 3);
	float perc = vcc.Read_Perc(VccMin, VccMax);
	int batt = (int)perc;
	IODisplay.print(batt);
	IODisplay.print("%");
	return 0;
}
void sleepNow()
{
	IODisplay.fillScreen(BLACK);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Want beef?
	sleep_enable();
	sleep_mode();
}


