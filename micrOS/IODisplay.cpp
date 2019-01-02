#include "IODisplay.h"
#include "kernel.h"
#include <MCUFRIEND_kbv.h>
extern MCUFRIEND_kbv IODisplay;

void LCD_Test_Menu() {
	uint16_t DisplayEngine = IODisplay.readID();
	if (DisplayEngine == 0xEFEF) DisplayEngine = 0x9486;
	IODisplay.reset();
	IODisplay.begin(DisplayEngine);
	IODisplay.setRotation(1);
	IODisplay.fillScreen(0x09A9);
	IODisplay.setCursor(1, 10);
	IODisplay.println(" MCU Test Bench");
	IODisplay.setCursor(1, 30);
	IODisplay.println(" By GeoSn0w (@FCE365)");
	delay(500);
	IODisplay.setCursor(1, 60);
	IODisplay.println(" Detecting IODisplay System...\n");
	delay(250);
	IODisplay.setCursor(1, 80);
	IODisplay.print(" Found IODisplay ID: 0x");
	IODisplay.println(DisplayEngine, HEX);
	IODisplay.setCursor(1, 100);
	IODisplay.println(" Testing Inverted Mode...");
	delay(2000);
	IODisplay.invertDisplay(true);
	delay(500);
	IODisplay.invertDisplay(false);
	delay(500);
	IODisplay.invertDisplay(true);
	delay(500);
	IODisplay.invertDisplay(false);
	delay(500);
	IODisplay.invertDisplay(true);
	delay(500);
	IODisplay.invertDisplay(false);
	delay(500);
	IODisplay.invertDisplay(true);
	delay(500);
	IODisplay.invertDisplay(false);
	IODisplay.setCursor(1, 120);
	IODisplay.println(" Launching Color Test...");
	delay(2000);
	IODisplay.fillScreen(RED);
	delay(500);
	IODisplay.fillScreen(GREEN);
	delay(500);
	IODisplay.fillScreen(BLUE);
	delay(500);
	IODisplay.fillScreen(WHITE);
	delay(500);
	IODisplay.fillScreen(TestMenuBG);
	delay(500);
	IODisplay.fillScreen(YELLOW);
	delay(500);
	IODisplay.fillScreen(MAGENTA);
	delay(500);
	IODisplay.fillScreen(CYAN);
	delay(500);
	IODisplay.fillScreen(DarkGRAY);
	delay(500);
	step2();
}
void step2() {
	uint16_t IODisplayEngine = IODisplay.readID();
	if (IODisplayEngine == 0xEFEF) IODisplayEngine = 0x9486;
	IODisplay.setCursor(1, 10);
	IODisplay.setTextSize(2);
	IODisplay.setRotation(1);
	IODisplay.setTextColor(WHITE);
	IODisplay.fillScreen(TestMenuBG);
	IODisplay.println(F(" MCU Test Bench"));
	IODisplay.setCursor(1, 30);
	IODisplay.println(F(" By GeoSn0w (@FCE365)"));
	IODisplay.setCursor(1, 60);
	IODisplay.println(F(" Detecting kernel System...\n"));
	IODisplay.setCursor(1, 80);
	IODisplay.print(F(" Found kernel ID: 0x"));
	IODisplay.println(IODisplayEngine, HEX);
	IODisplay.setCursor(1, 100);
	IODisplay.println(F(" Testing Inverted Mode..."));
	IODisplay.setCursor(1, 120);
	IODisplay.println(F(" Launching Color Test..."));
	IODisplay.setCursor(1, 140);
	IODisplay.println(F(" Launching Font Sizes Test..."));
	delay(3000);
	testFontSizes();
}
void testFontSizes() {
	IODisplay.fillScreen(TestMenuBG);
	IODisplay.setTextSize(1);
	IODisplay.setCursor(1, 10);
	delay(500);
	IODisplay.println(F(" TEST 0123456@#^&*(%_()^*&^&*-/*=/*+63~��<>"));
	delay(1000);
	IODisplay.setTextSize(2);
	IODisplay.setCursor(1, 30);
	IODisplay.println(F(" TEST 0123456@#^&*(%"));
	delay(1000);
	IODisplay.setTextSize(3);
	IODisplay.setCursor(1, 60);
	IODisplay.println(F(" TEST 0123456@#^&*(%"));
	delay(1000);
	IODisplay.setTextSize(4);
	IODisplay.setCursor(1, 110);
	IODisplay.println(F(" TEST 0123456@#^+"));
	delay(1000);
	IODisplay.setTextSize(5);
	IODisplay.setCursor(1, 160);
	IODisplay.println(F(" TEST 0123456@#"));
	delay(1000);
	step3();
}
void step3() {
	uint16_t IODisplayEngine = IODisplay.readID();
	if (IODisplayEngine == 0xEFEF) IODisplayEngine = 0x9486;
	IODisplay.setCursor(1, 10);
	IODisplay.setTextSize(2);
	IODisplay.setRotation(1);
	IODisplay.setTextColor(WHITE);
	IODisplay.fillScreen(TestMenuBG);
	IODisplay.println(F(" MCU Test Bench"));
	IODisplay.setCursor(1, 30);
	IODisplay.println(F(" By GeoSn0w (@FCE365)"));
	IODisplay.setCursor(1, 60);
	IODisplay.println(F(" Detecting kernel System...\n"));
	IODisplay.setCursor(1, 80);
	IODisplay.print(F(" Found kernel ID: 0x"));
	IODisplay.println(IODisplayEngine, HEX);
	IODisplay.setCursor(1, 100);
	IODisplay.println(F(" Testing Inverted Mode..."));
	IODisplay.setCursor(1, 120);
	IODisplay.println(F(" Launching Color Test..."));
	IODisplay.setCursor(1, 140);
	IODisplay.println(F(" Launching Font Sizes Test..."));
	IODisplay.setCursor(1, 160);
	IODisplay.println(F(" Launching Triangles Test..."));
	delay(3000);
	testTriangles();
}
void step4() {
	uint16_t IODisplayEngine = IODisplay.readID();
	if (IODisplayEngine == 0xEFEF) IODisplayEngine = 0x9486;
	IODisplay.setCursor(1, 10);
	IODisplay.setTextSize(2);
	IODisplay.setRotation(1);
	IODisplay.setTextColor(WHITE);
	IODisplay.fillScreen(TestMenuBG);
	IODisplay.println(F(" MCU Test Bench"));
	IODisplay.setCursor(1, 30);
	IODisplay.println(F(" By GeoSn0w (@FCE365)"));
	IODisplay.setCursor(1, 60);
	IODisplay.println(F(" Detecting kernel System...\n"));
	IODisplay.setCursor(1, 80);
	IODisplay.print(F(" Found kernel ID: 0x"));
	IODisplay.println(IODisplayEngine, HEX);
	IODisplay.setCursor(1, 100);
	IODisplay.println(F(" Testing Inverted Mode..."));
	IODisplay.setCursor(1, 120);
	IODisplay.println(F(" Launching Color Test..."));
	IODisplay.setCursor(1, 140);
	IODisplay.println(F(" Launching Font Sizes Test..."));
	IODisplay.setCursor(1, 160);
	IODisplay.println(" Launching Triangles Test...");
	IODisplay.setCursor(1, 180);
	IODisplay.println(" Testing Micro SD Data...");
	IODisplay.setCursor(1, 200);
	IODisplay.println(" TFT Test successfully completed!");
	IODisplay.setCursor(1, 220);
	IODisplay.println(" [i] Please reboot micrOS!");
	return;
}
void testTriangles() {
	int x = 1;
	do
	{
		unsigned long start;
		int n, i, cx = IODisplay.width() / 2 - 1,
			cy = IODisplay.height() / 2 - 1;
		IODisplay.fillScreen(BLACK);
		n = min(cx, cy);
		start = micros();
		for (i = 0; i < n; i += 5) {
			IODisplay.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, BLUE);
			IODisplay.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, RED);
			IODisplay.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, MAGENTA);
		}
		x++;
	} while (x <= 5);
	step4();
}
int visuals_pbar(int rest) {
	IODisplay.fillRect(0, 0, 10, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 20, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 30, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 40, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 50, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 80, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 120, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 130, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 140, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 150, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 170, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 200, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 220, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 240, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 260, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 280, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 300, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 330, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 350, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 380, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 400, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 420, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 440, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 460, 10, WHITE);
	delay(rest);
	IODisplay.fillRect(0, 0, 480, 10, WHITE);
	return;
}
