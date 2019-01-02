// 
// 
// 

#include "micrOS_Apps.h"
#include "IODisplay.h"
#include "kernel.h"
extern MCUFRIEND_kbv IODisplay;
void menu_init() {
	isMenuOpen = true; //We're in app.
	IODisplay.drawRect(45, 54, 394, 202, 0x9CDD);
	IODisplay.fillRect(46, 55, 392, 200, 0x8D3A);
	IODisplay.drawBitmap(416, 60, close_button, 16, 16, WHITE);
	IODisplay.drawRect(44, 53, 396, 204, WHITE);
	IODisplay.setCursor(50, 59);
	IODisplay.setTextColor(WHITE);
	IODisplay.print("MENU"); //Header
						  //Icons beging now. Touch register knows what to look for because of isMenuOpen.
	IODisplay.drawBitmap(68, 85, terminal_icon_big, 64, 64, WHITE);
	IODisplay.drawBitmap(150, 85, files_big, 64, 64, WHITE);
	IODisplay.drawBitmap(220, 85, settings_big, 64, 64, WHITE);
	IODisplay.drawBitmap(285, 85, music, 64, 64, WHITE);
	IODisplay.drawBitmap(355, 85, calc_app, 64, 64, WHITE);
	//No more icons.
	AWAIT_TOUCH_SG(); //Wait for touch input.
	return;
}

