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

	#define YP A2
	#define XM A1
	#define YM 6
	#define XP 7

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
	#define DarkPurple      0x694D
    #define LessDarkPurple  0xBB38
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
#define MINPRESSURE 6
#define MAXPRESSURE 1000

#define TS_MINX  147
#define TS_MINY  154
#define TS_MAXX  942
#define TS_MAXY  911

#define RESOLUTION_W  480
#define RESOLUTION_H  320

struct registeredTouchFrameService {
	/*
	Overlay 0   -  Desktop, no app open
	Overlay 1   -  Menu open, not in app
	*/
	// Core Storage Media
#define performErase p.x>34 && p.x<447 && p.y>217 && p.y<274 && inApp == 1 // Erase button, it will pop a warning.
#define doErase p.x>34 && p.x<447 && p.y>217 && p.y<274 && inApp == 1 // Erase button, confirmed. This will start the obliteration.
#define cancelErase p.x>34 && p.x<447 && p.y>217 && p.y<274 && inApp == 1 // Cancel button, it will revert back to Core Storage Media

	// Switchboard screen
#define menuButton p.x>10 && p.x<34 && p.y>292 && p.y<316 && inApp == 0 // Cancel button, it will revert back to Core Storage Media
	int currentlyActiveOverlay = 0;
};
#else
	#include "WProgram.h"
#endif


#endif

