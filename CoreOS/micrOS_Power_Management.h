#include <Vcc.h>
#include <avr/sleep.h>
const float VccMin = 0.0;
const float VccMax = 5.0;
const float VccCorrection = 1.0/1.0;
Vcc vcc(VccCorrection);
int wakePin = 2;
int sleepStatus = 0;
int count = 0;
bool low_battery_popup = false;
int battery_exhausted(){
  low_battery_popup = true;
  kernel.drawRect(45,54,394,202,0xE2EE);
  kernel.fillRect(46,55,392,200,0xC188);
  kernel.setCursor(50,60);
  kernel.setTextColor(WHITE);
  kernel.print("micrOS System");
  kernel.setCursor(393,59);
  kernel.drawBitmap(416,60, close_button, 16, 16, WHITE);
  kernel.drawBitmap(200,110, low_batt, 64, 64, WHITE);
  kernel.setCursor(80,200);
  kernel.print("Battery exhausted! Recharge.");
  return;
}
int get_battery_status(){
    kernel.drawRect(451, 4, 20, 12, WHITE); //battery body x, y, w, h
    kernel.fillRect(451, 4, 17, 12, WHITE); //filling
    kernel.fillRect(471, 6, 3, 8, WHITE); // battery tip
    kernel.setCursor(402, 3);
    float perc = vcc.Read_Perc(VccMin, VccMax);
    int batt = (int) perc;
    kernel.print(batt);
    kernel.print("%");
    return 0;
}
void sleepNow()
{
    kernel.fillScreen(BLACK);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Want beef?
    sleep_enable();
    sleep_mode();
}
