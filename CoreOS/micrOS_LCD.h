// LCD Pin Configuration for micrOS by GeoSn0w (@FCE365)
// You may modify these to accommodate your display.
// The default configuration works fine with a 3,5 inch MCUFRIEND TouchScreen Shield

#include <micrOS_Storage.h>
#include <MCUFRIEND_kbv.h>
#define LCD_RST A4
#define LCD_CS A3
#define LCD_RS A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_D0 8
#define LCD_D1 9
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define YP A1
#define XM A2
#define YM 7
#define XP 6
MCUFRIEND_kbv kernel;
void step2();
void step3();
void step4();
void testFontSizes();
void testTriangles();
void LCD_Test_Menu(){
    BG = 0x09A9;
    uint16_t IODisplay = kernel.readID();
    kernel.reset();
    kernel.begin(IODisplay);
    kernel.setRotation(1);
    kernel.fillScreen(BG);
    kernel.setCursor(1, 10);
    kernel.println(" MCU Test Bench");
    kernel.setCursor(1, 30);
    kernel.println(" By GeoSn0w (@FCE365)");
    delay(500);
    kernel.setCursor(1, 60);
    kernel.println(" Detecting kernel System...\n");
    delay(250);
    kernel.setCursor(1, 80);
    kernel.print(" Found kernel ID: 0x");
    kernel.println(IODisplay, HEX);
    kernel.setCursor(1, 100);
    kernel.println(" Testing Inverted Mode...");
    delay(2000);
    kernel.invertDisplay(true);
    delay(500);
    kernel.invertDisplay(false);
    delay(500);
    kernel.invertDisplay(true);
    delay(500);
    kernel.invertDisplay(false);
    delay(500);
    kernel.invertDisplay(true);
    delay(500);
    kernel.invertDisplay(false);
    delay(500);
    kernel.invertDisplay(true);
    delay(500);
    kernel.invertDisplay(false);
    kernel.setCursor(1, 120);
    kernel.println(" Launching Color Test...");
    delay(2000);
    kernel.fillScreen(RED);
    delay(500);
    kernel.fillScreen(GREEN);
    delay(500);
    kernel.fillScreen(BLUE);
    delay(500);
    kernel.fillScreen(WHITE);
    delay(500);
    kernel.fillScreen(BG);
    delay(500);
    kernel.fillScreen(YELLOW);
    delay(500);
    kernel.fillScreen(MAGENTA);
    delay(500);
    kernel.fillScreen(CYAN);
    delay(500);
    kernel.fillScreen(DarkGRAY);
    delay(500);
    step2();
}
void step2(){
    uint16_t IODisplay = kernel.readID();
    if (IODisplay == 0xEFEF) IODisplay = 0x9486;
    kernel.setCursor(1, 10);
    kernel.setTextSize(2);
    kernel.setRotation(1);
    kernel.setTextColor(WHITE);
    kernel.fillScreen(BG);
    kernel.println(F(" MCU Test Bench"));
    kernel.setCursor(1, 30);
    kernel.println(F(" By GeoSn0w (@FCE365)"));
    kernel.setCursor(1, 60);
    kernel.println(F(" Detecting kernel System...\n"));
    kernel.setCursor(1, 80);
    kernel.print(F(" Found kernel ID: 0x"));
    kernel.println(IODisplay, HEX);
    kernel.setCursor(1, 100);
    kernel.println(F(" Testing Inverted Mode..."));
    kernel.setCursor(1, 120);
    kernel.println(F(" Launching Color Test..."));
    kernel.setCursor(1, 140);
    kernel.println(F(" Launching Font Sizes Test..."));
    delay(3000);
    testFontSizes();
}
void testFontSizes(){
    kernel.fillScreen(BG);
    kernel.setTextSize(1);
    kernel.setCursor(1, 10);
    delay(500);
    kernel.println(F(" TEST 0123456@#^&*(%_()^*&^&*-/*=/*+63~±§<>"));
    delay(1000);
    kernel.setTextSize(2);
    kernel.setCursor(1, 30);
    kernel.println(F(" TEST 0123456@#^&*(%"));
    delay(1000);
    kernel.setTextSize(3);
    kernel.setCursor(1, 60);
    kernel.println(F(" TEST 0123456@#^&*(%"));
    delay(1000);
    kernel.setTextSize(4);
    kernel.setCursor(1, 110);
    kernel.println(F(" TEST 0123456@#^+"));
    delay(1000);
    kernel.setTextSize(5);
    kernel.setCursor(1, 160);
    kernel.println(F(" TEST 0123456@#"));
    delay(1000);
    step3();
}
void step3(){
    uint16_t IODisplay = kernel.readID();
    if (IODisplay == 0xEFEF) IODisplay = 0x9486;
    kernel.setCursor(1, 10);
    kernel.setTextSize(2);
    kernel.setRotation(1);
    kernel.setTextColor(WHITE);
    kernel.fillScreen(BG);
    kernel.println(F(" MCU Test Bench"));
    kernel.setCursor(1, 30);
    kernel.println(F(" By GeoSn0w (@FCE365)"));
    kernel.setCursor(1, 60);
    kernel.println(F(" Detecting kernel System...\n"));
    kernel.setCursor(1, 80);
    kernel.print(F(" Found kernel ID: 0x"));
    kernel.println(IODisplay, HEX);
    kernel.setCursor(1, 100);
    kernel.println(F(" Testing Inverted Mode..."));
    kernel.setCursor(1, 120);
    kernel.println(F(" Launching Color Test..."));
    kernel.setCursor(1, 140);
    kernel.println(F(" Launching Font Sizes Test..."));
    kernel.setCursor(1, 160);
    kernel.println(F(" Launching Triangles Test..."));
    delay(3000);
    testTriangles();
}
void step4(){
    uint16_t IODisplay = kernel.readID();
    if (IODisplay == 0xEFEF) IODisplay = 0x9486;
    kernel.setCursor(1, 10);
    kernel.setTextSize(2);
    kernel.setRotation(1);
    kernel.setTextColor(WHITE);
    kernel.fillScreen(BG);
    kernel.println(" MCU Test Bench");
    kernel.setCursor(1, 30);
    kernel.println(" By GeoSn0w (@FCE365)");
    kernel.setCursor(1, 60);
    kernel.println(" Detecting kernel System...\n");
    kernel.setCursor(1, 80);
    kernel.print(" Found kernel ID: 0x");
    kernel.println(IODisplay, HEX);
    kernel.setCursor(1, 100);
    kernel.println(" Testing Inverted Mode...");
    kernel.setCursor(1, 120);
    kernel.println(" Launching Color Test...");
    kernel.setCursor(1, 140);
    kernel.println(" Launching Font Sizes Test...");
    kernel.setCursor(1, 160);
    kernel.println(" Launching Triangles Test...");
    kernel.setCursor(1, 180);
    kernel.println(" Testing Micro SD Data...");
    kernel.setCursor(1, 200);
    if (check_sda() == 0) {
        kernel.println(" Successfully mounted SD Card!");
        kernel.setCursor(1, 220);
        delay(300);
        kernel.println(" TFT Test successfully completed! Please reboot micrOS!");
        delay(1600);
    } else if (check_sda() == 1){
        kernel.println(" Failed to mount SD Card!");
        kernel.setCursor(1, 220);
        delay(300);
        kernel.println(" TFT Test failed! Please reboot micrOS!");
    }
}
void testTriangles() {
    int x = 1;
    do
    {
        unsigned long start;
        int n, i, cx = kernel.width()  / 2 - 1,
        cy = kernel.height() / 2 - 1;
        kernel.fillScreen(BLACK);
        n = min(cx, cy);
        start = micros();
        for (i = 0; i < n; i += 5) {
            kernel.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,kernel.color565(0, 4, i));
        }
        x++;
    } while (x <= 10);
    step4();
}
