//Declarations and definitions for Kernel Version, Kernel return codes and BL for micrOS by GeoSn0w (@FCE365)
#include <micrOS_Graphics.h>
#define kMicroVersion "micrOS.local_kernel 1.2 micrOS Kernel Version 1.2 TUE December 19 DEVELOPMENT"
#define kBootLoaderREV "micrOS BootLoader REV. 1.18.21, TUE December 19 DEVELOPMENT"
#define KERN_FAILURE 1
#define KERN_SUCCESS 0
#define DEVICE_OP_VOLTAGE 5 // 5V Applies for both Mega and Uno
#define KERN_MAX_MEMORY_UNO 2048 // -> SRAM
#define KERN_MAX_STORAGE_UNO 32000 // -> FLASH
#define KERN_MAX_CLOCK_SPEED_UNO 16000000 //16 Mhz CPU Clock Speed
#define KERN_EEPROM_UNO 1000 //EEPROM 1KB
#define KERN_UNO_ANALOG_IO 6 // 6 Analog Pins
#define KERN_UNO_DIGITAL_IO 6 // 6 Digital Pins
#define KERN_UNO_CPU "ATmega328P"
#define KERN_MAX_MEMORY_MEGA 8024 // -> SRAM
#define KERN_MAX_STORAGE_MEGA 256000 // -> FLASH
#define KERN_MAX_CLOCK_SPEED_MEGA 16000000 //16 Mhz CPU Clock Speed
#define KERN_EEPROM_MEGA 4000 //EEPROM 4KB
#define KERN_MEGA_ANALOG_IO 16 // 16 Analog Pins
#define KERN_MEGA_DIGITAL_IO 54 // 54 Digital Pins
#define KERN_MEGA_CPU "ATmega2560" //REV 3
#define KERN_ALT_MEGA_CPU "ATmega1280" //1st edition
#define KERN_NAME "micrOS Kernel"
#define KERN_VERSION 1.2
#define KERN_SUPPORTED_DEVICE 0x9486
#define KERN_DEFAULT_ORIENTATION 1
#define KERN_DEFAULT_TXT_SIZE 2
#define KERN_DEFAULT_CPU "ATmega1280"
#define KERN_SUPPORTED_ARCH "AVR"
#define KERN_FUSE "DEVELOPMENT" //should be changed to RELEASE to disable verbose boot
#define KERN_LOADER "micrOS.local_kernel" //defaults to self
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) //We really wanna make sure it is AVR
#define DEBUG_CAPTURE_SIZE 7168
#define CAPTURE_SIZE 7168
#elif defined(__AVR_ATmega328P__)
#define DEBUG_CAPTURE_SIZE 1024
#define CAPTURE_SIZE 1024
#else
#define DEBUG_CAPTURE_SIZE 532
#define CAPTURE_SIZE 532
#endif
#define SWITCHBOARD_ERR 0x264A;
#define APPMENU_ERR 0x221A;
#define BOOTTIME_ERR 0x001F;
#define KERNEL_ERR 0x221F;
#define UNKNOWN_ERR 0x000A;
#define SERIAL_ERR 0x2121;
#define SERIAL_ERR 0x2121;
#define TOUCHSCREEN_ERR 0x41FF;
#define TFT_ERR 0x42FF;
#define DIAG_ERR 0x00FF;
char voltage[10];
char battpercenttxt [10];
int battv;
int battpercent;
int barv;
long readVcc();
int IRQ_PIN_MODE(){
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    return 0;
}
int get_battery_status(){
    battv = readVcc();
    itoa (battv, voltage, 10);
    itoa (battpercent, battpercenttxt, 10);
    kernel.setCursor(375, 3);
    kernel.print(voltage);
    kernel.print("mV");
    kernel.drawRect(451, 4, 20, 12, WHITE); //battery body x, y, w, h
    kernel.fillRect(451, 4, 17, 12, WHITE); //filling
    kernel.fillRect(471, 6, 3, 8, WHITE); // battery tip
    return 0;
}
int switchboard_set_bars(){
    kernel.fillScreen(BG); //fills the screen blue
    kernel.fillRect(0, 0, 480, 20, 0x5454); //Draws a statusbar
    kernel.fillRect(0, 290, 480, 35, 0x5454); //Draws a taskbar
    return 0;
}
int switchboard_set_misc(){
    kernel.setTextColor(WHITE);
    kernel.setCursor(215, 3);
    kernel.println("12:31");
    kernel.drawBitmap(10,292, menu_icn, 24, 24, WHITE);
    kernel.drawBitmap(65,292, cell_pad, 24, 24, WHITE);
    kernel.drawBitmap(130,292, SMS, 24, 24, WHITE);
    kernel.drawBitmap(195,292, settings, 24, 24, WHITE);
    kernel.drawBitmap(260,292, files, 24, 24, WHITE);
    kernel.drawBitmap(325,292, camera_app_icon, 24, 24, WHITE);
    kernel.drawBitmap(390,292, terminal_icon, 24, 24, WHITE);
    kernel.drawBitmap(450,292, shutdown_icon, 24, 24, WHITE);
    kernel.drawBitmap(100,2, signal1, 16, 16, WHITE);
    return 0;
}
long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(6); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}
int switchboard_set_wallpaper(){
    kernel.setTextColor(WHITE);
    /*
    kernel.setCursor(150, 120);
    kernel.println(F("============="));
    kernel.setCursor(115, 150);
    kernel.println(F(">> I ^_^ MINIMAL <<"));
    kernel.setCursor(150, 180);
    kernel.println(F("============="));
     */
    kernel.setCursor(289, 235);
    kernel.setTextSize(5);
    kernel.println(F("micrOS"));
    kernel.setTextSize(2);
    return 0;
}
void buildAlert(char message[], char sub[], char title[], int x, int y, int xsub, int ysub, bool dismissable){ //let's you build custom alerts for micrOS
    kernel.drawRect(44,53,396,204,WHITE);
    kernel.fillRect(46,55,392,200,LightGRAY);
    kernel.drawRect(46,55,392,200,WHITE);
    kernel.drawLine(46,76,435,76,WHITE);
    kernel.drawLine(46,77,435,77,WHITE);
    kernel.drawLine(46,78,435,78,WHITE);
    kernel.setCursor(50,59);
    kernel.setTextColor(WHITE);
    kernel.setCursor(168,110);
    kernel.setTextSize(4);
    kernel.print("[ ! ]");
    kernel.setTextSize(2);
    kernel.setCursor(49,59);
    kernel.print(title);
    kernel.setCursor(x,y);
    kernel.print(message);
    kernel.setCursor(xsub,ysub);
    kernel.print(sub);
    if (dismissable){
        kernel.setCursor(393,59);
        kernel.print("[X]");
    }
}
void kern_panic(){ //Triggered when a fatal exception occurrs!
    buildAlert("A fatal exception occurred!", "Please reboot and try again!", "[!] System Error", 78, 160, 70, 190, false);
}
