// IODisplay.h

#ifndef _IODISPLAY_h
#define _IODISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
	#include <gfxfont.h>
	#include <Adafruit_SPITFT_Macros.h>
	#include <Adafruit_SPITFT.h>
	#include <Adafruit_GFX.h>
	#include <TouchScreen.h>
	#include <SD.h>
	#include <MCUFRIEND_kbv.h>
// Display Pinout - Change them accordingly
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
// Colors
	#define BLACK			0x0000
	#define BLUE			0x001F
	#define RED				0xF800
	#define GREEN			0x07E0
	#define CYAN			0x07FF
	#define MAGENTA			0xF81F
	#define YELLOW			0xFFE0
	#define WHITE			0xFFFF
	#define DarkGRAY		0x5AEB
	#define LightGRAY		0x8410
	#define VeryDarkGRAY	0x4208
	#define TestMenuBG		0x09A9
// Test functions
void step2(void);
void step3(void);
void step4(void);
void testFontSizes(void);
void testTriangles(void);
void LCD_Test_Menu(void);
int visuals_pbar(int rest);
//Touch Screen
#define MINPRESSURE 5
#define MAXPRESSURE 1000
#define TS_MINX 1
#define TS_MINY 1
#define TS_MAXX 480
#define TS_MAXY 320
#else
	#include "WProgram.h"
#endif


#endif

