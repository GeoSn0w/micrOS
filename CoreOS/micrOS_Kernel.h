#include <micrOS_Graphics.h>
#include <micrOS_Power_Management.h>
#include <memory_man.h>
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
#define RW_MOUNT_SD_ERR 0x01FF;
#define MINPRESSURE 5
#define MAXPRESSURE 1000
#define TS_MINX 1
#define TS_MINY 1
#define TS_MAXX 480
#define TS_MAXY 320
#define kUSERNAME ">GeoSn0w"
char OSName[12] = "micrOS"; //Why not
uint16_t KERN_ERROR = 0x0000;
uint16_t BootMode = 0x0080;
uint16_t debug = 0x01;
bool MKOS = true;
bool isMenuOpen = false;
bool SysSdutDownReqConfirm = false;
bool isCharging = false;
bool inApp = false;
bool check_bundle();
bool check_BaseBand();
bool isWirelessConnected = false;
int micrOS_SwitchBoard();
int getMKOS();
int bootstrap();
int respring();
int boot_verbose();
int shutdown();
int boot_vanilla();
int kernel_I_haz_panic();
int switchboard_set_bars(uint16_t UIColor);
int switchboard_set_misc();
int switchboard_set_wallpaper();
void switchboard_integrity_check();
void buildAlert(char message[], char sub[], char title[], int x, int y, int xsub, int ysub, bool dismissable);
void menu();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int IRQ_PIN_MODE(){
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    return 0;
}
int switchboard_set_bars(uint16_t UIColor){
    kernel.fillRect(0, 0, 480, 20, UIColor); //Draws a statusbar
    kernel.fillRect(0, 290, 480, 35, UIColor); //Draws the dock
    return 0;
}
int bootstrap(){
  if (debug == 0x01 && KERN_FUSE == "DEVELOPMENT"){
      Serial.begin(9600); //Initializes Serial only if debugging is enabled and the fusing is DEVELOPMENT
      boot_verbose();
  } else {
      boot_vanilla(); //Normal Mode, no serial printing.
  }
}
int getMKOS(){
  return true;
}
bool check_bundle() {
  return true;
}
int respring(){
  kernel.setCursor(1, 4);
  kernel.setTextColor(WHITE);
  kernel.setTextSize(2);
  kernel.print(kUSERNAME);
  switchboard_set_misc();
  get_battery_status();
  return;
}
int shutdown(){
  kernel.drawRect(45,54,394,202,0xE2EE);
  kernel.fillRect(46,55,392,200,0xC188);
  kernel.setCursor(50,60);
  kernel.setTextColor(WHITE);
  kernel.print("micrOS System");
  kernel.setCursor(393,59);
  kernel.drawBitmap(416,60, close_button, 16, 16, WHITE);
  kernel.drawBitmap(200,110, switch_off, 64, 64, WHITE);
  kernel.fillRect(52,220,379,30,0x60C4);
  kernel.setCursor(100,226);
  kernel.print("Confirm System Shutdown");
  return;
}
int switchboard_set_misc(){
    kernel.setTextColor(WHITE);
    kernel.setCursor(215, 3);
    kernel.println("12:31");
    if(inApp){
      kernel.drawBitmap(10,292, exit_icon, 24, 24, WHITE);
    } else {
      kernel.drawBitmap(10,292, menu_icn, 24, 24, WHITE);
    }
    if(!inApp){
      kernel.drawBitmap(65,292, cell_pad, 24, 24, WHITE);
      kernel.drawBitmap(130,292, SMS, 24, 24, WHITE);
      kernel.drawBitmap(195,292, settings, 24, 24, WHITE);
      kernel.drawBitmap(260,292, files, 24, 24, WHITE);
      kernel.drawBitmap(325,292, camera_app_icon, 24, 24, WHITE);
      kernel.drawBitmap(390,292, terminal_icon, 24, 24, WHITE);
      kernel.drawBitmap(450,292, shutdown_icon, 24, 24, WHITE);
    }
    if(isWirelessConnected){
      kernel.drawBitmap(100,2, wifi_signal, 16, 16, WHITE); //Connected.
    } else {
      kernel.drawBitmap(100,2, no_signal, 16, 16, WHITE); //Not connected.
    }
    return 0;
}

int switchboard_set_wallpaper(){
    kernel.setTextColor(WHITE);
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
int dump(){
  kernel.fillScreen(BG);
  kernel.setTextSize(1);
  kernel.setCursor(0,2);
  delay(1000);
  dumpRam(kernel,0x800,1200);
  kernel.println();
  return;
}
int boot_verbose(){
    uint16_t IODisplay = kernel.readID();
    if (IODisplay == 0xEFEF) IODisplay = 0x9486; // ILI panel
    kernel.begin(IODisplay);
    kernel.setRotation(1);
    kernel.setTextSize(4);
    kernel.fillScreen(BLACK);
    kernel.setTextColor(WHITE);
    kernel.setCursor(170, 150);
    kernel.print(F("micrOS"));
    delay(2000);
    kernel.fillScreen(BLACK);
    kernel.setTextSize(1);
    kernel.setCursor(2, 3);
    kernel.print(F("micrOS for Arduino MEGA"));
    delay(1000);
    kernel.setCursor(2, 13);
    kernel.print(kMicroVersion);
    delay(200);
    kernel.setCursor(2, 23);
    kernel.print(F(kBootLoaderREV));
    delay(200);
    kernel.setCursor(2, 33);
    kernel.print(F("Detecting device in Kernel Mode..."));
    delay(200);
    kernel.setCursor(2, 43);
    kernel.print(F("Loaded kernel Display for IODisplay component with ID: 0x"));
    kernel.println(IODisplay, HEX);
    delay(200);
    kernel.setCursor(2, 53);
    kernel.print(F("Loading micrOS RGB Color Descriptors for IODisplay..."));
    kernel.setCursor(2, 63);
    delay(400);
    kernel.print(F("Loading micrOS RED Color Descriptor for IODisplay with ID: 0xF800"));
    kernel.setCursor(2, 73);
    delay(400);
    kernel.print(F("Loading micrOS Green Color Descriptor for IODisplay with ID: 0x07E0"));
    kernel.setCursor(2, 83);
    delay(400);
    kernel.print(F("Loading micrOS Blue Color Descriptor for IODisplay with ID: 0x001F"));
    kernel.setCursor(2, 93);
    delay(400);
    kernel.print(F("Waiting for MKOS..."));
    getMKOS();
    kernel.setCursor(2, 103);
    delay(400);
    kernel.print(F("Checking /dev/sda1..."));
    kernel.setCursor(2, 113);
    delay(400);
    if (check_sda() == KERN_SUCCESS){
      kernel.print(F("Successfully mounted /dev/sda1!"));
      delay(400);
    } else {
      kernel.setCursor(2, 113);
      kernel.print(F("Failed to mount /dev/sda1! Storage media not ready!"));
      delay(400);
    }
    if(MKOS == true){
        kernel.setCursor(2, 123);
        kernel.print(F("MKOS has arrived!"));
        delay(1000);
        #define MKOS LEGIT
    } else {
        kernel.setCursor(2, 123);
        kernel.print(F("MKOS is missing!"));
        return KERN_FAILURE;
    }
    delay(400);
    kernel.setCursor(2, 133);
    kernel.print(F("Bootstrapping com.geosn0w.switchboard..."));
    delay(400);
    if(check_bundle()){
      kernel.setCursor(2, 143);
      kernel.print(F("Successfully loaded com.geosn0w.switchboard."));
      delay(200);
    } else {
      kernel.setCursor(2, 143);
      kernel.print(F("MOFI: The process com.geosn0w.switchboard has been terminated with signal -1"));
      kernel.setCursor(2, 153);
      kernel.print(F("MOFI: Incorrect signature for com.geosn0w.switchboard. Aborting..."));
      delay(400);
      kernel.setCursor(2, 163);
      kernel.print(F("CPU_HALTED"));
      return KERN_FAILURE;
    }
    if (check_BaseBand()){
      kernel.setCursor(2, 153);
      kernel.print(F("Successfully loaded baseband module."));
      delay(400);
    } else {
      kernel.setCursor(2, 153);
      kernel.print(F("Failed to load baseband module. Aborting..."));
      return KERN_FAILURE;
    }
    kernel.setTextSize(2);
    delay(2000);
    micrOS_SwitchBoard(); //We can open the UI now.
}
int boot_vanilla(){
    //Normal Boot begins
    uint16_t IODisplay = kernel.readID();
    if (IODisplay == 0xEFEF) IODisplay = 0x9486;
    kernel.begin(IODisplay);
    kernel.setRotation(1);
    kernel.setTextSize(4);
    kernel.setTextColor(WHITE);
    kernel.fillScreen(BLACK);
    kernel.setCursor(157,157);
    kernel.print(OSName);
    kernel.fillRect(0, 0, 10, 10, WHITE);
    delay(200);
    kernel.fillRect(0, 0, 20, 10, WHITE);
    delay(220);
    kernel.fillRect(0, 0, 30, 10, WHITE);
    delay(220);
    kernel.fillRect(0, 0, 40, 10, WHITE);
    delay(220);
    kernel.fillRect(0, 0, 50, 10, WHITE);
    delay(200);
    kernel.fillRect(0, 0, 80, 10, WHITE);
    delay(200);
    kernel.fillRect(0, 0, 120, 10, WHITE);
    delay(300);
    kernel.fillRect(0, 0, 130, 10, WHITE);
    delay(200);
    kernel.fillRect(0, 0, 140, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 150, 10, WHITE);
    delay(200);
    kernel.fillRect(0, 0, 170, 10, WHITE);
    delay(200);
    kernel.fillRect(0, 0, 200, 10, WHITE);
    delay(400);
    kernel.fillRect(0, 0, 220, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 240, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 260, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 280, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 300, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 330, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 350, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 380, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 400, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 420, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 440, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 460, 10, WHITE);
    delay(100);
    kernel.fillRect(0, 0, 480, 10, WHITE);
    delay(100);
    kernel.setTextSize(2);
    micrOS_SwitchBoard(); //ProgressBar ends. Device Boots.
}
int micrOS_SwitchBoard(){ ////////////// <==
  kernel.fillScreen(BG);
  switchboard_set_bars(0x5454);
  kernel.setCursor(1, 4);
  kernel.setTextColor(WHITE);
  kernel.setTextSize(2);
  kernel.print(kUSERNAME);
  switchboard_set_misc();
  switchboard_set_wallpaper();
  get_battery_status();
  switchboard_integrity_check();
}
void switchboard_integrity_check(){
  if(KERN_ERROR = 0) {
    kernel_I_haz_panic();
  }
}
bool check_BaseBand() {
  /*
    Requires a SIM900 Quad GSM shield so we return true for the moment so we can boot.
  */
  return true;
}
int kernel_I_haz_panic(){
  kernel.drawRect(44,53,396,204,0x60C4);
  kernel.fillRect(46,55,392,200,0xC188);
  kernel.drawRect(46,55,392,200,0x60C4);
  kernel.drawLine(46,76,435,76,0x60C4);
  kernel.drawLine(46,77,435,77,0x60C4);
  kernel.drawLine(46,78,435,78,0x60C4);
  kernel.setCursor(49,59);
  kernel.setTextColor(WHITE);
  kernel.print("micrOS System");
  kernel.drawBitmap(200,110, kern_panic_icon, 64, 64, WHITE);
  kernel.setCursor(70,195);
  kernel.print("An unrecoverable kernel issue");
  kernel.setCursor(110,215);
  kernel.print("has occurred at 0x");
  kernel.print(KERN_ERROR);
  return 1;
}
void menu(){
  isMenuOpen = true;
  kernel.drawRect(45,54,394,202,0x9CDD);
  kernel.fillRect(46,55,392,200,0x8D3A);
  kernel.drawBitmap(416,60, close_button, 16, 16, WHITE);
  kernel.drawRect(44,53,396,204,WHITE);
  kernel.setCursor(50,59);
  kernel.setTextColor(WHITE);
  kernel.print("MENU");
  kernel.drawBitmap(60,85, terminal_icon_big, 64, 64, WHITE);
  kernel.drawBitmap(140,85, files_big, 64, 64, WHITE);
  kernel.drawBitmap(210,85, settings_big, 64, 64, WHITE);
  kernel.drawBitmap(275,85, music, 64, 64, WHITE);
  IRQ_PIN_MODE();
}
