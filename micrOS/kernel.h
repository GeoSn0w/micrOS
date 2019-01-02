// Damn Kernel :P

#ifndef _KERNI_h
#define _KERNI_h
#include "micrOS_Storage.h"
#include "micrOS_Graphics_Cache.h"
#include "micrOS_Power_Management.h"
#define kMicroVersion "micrOS.Emily_kernel 1.3 micrOS Kernel Version 1.2 TUE JANUARY 2 DEVELOPMENT"
#define kBootLoaderREV "micrOS BootLoader REV. 1.18.21, TUE December 19 DEVELOPMENT"
#define kUSERNAME ">GeoSn0w"
#define KERN_DEFAULT_CPU "ATmega1280"
#define KERN_SUPPORTED_ARCH "AVR"//Ls20
#define KERN_FUSE "DEVELOPMENT" //should be changed to RELEASE to disable verbose boot
extern uint16_t BootMode;
extern uint16_t debug;
typedef int kern_return_t;
typedef int kern_platform_t;
int kernel_I_haz_panic(String panic_reason);
int switchboard_set_bars(uint16_t UIColor);
int switchboard_set_misc(void);
int switchboard_set_wallpaper(void);
void switchboard_integrity_check(void);
int micrOS_SwitchBoard(void);
int AWAIT_TOUCH_SG(void);
void buildAlert(char message[], char sub[], char title[], int x, int y, int xsub, int ysub, bool dismissable);
kern_return_t kernDisplayReload(void);
int kernRegisterNewApp(void);
int sigareport(int signal);
int kernKillActiveApp(void);
int shutdown(void);
extern bool isMenuOpen;
extern bool SysSdutDownReqConfirm;
extern bool isCharging;
extern bool inApp;
extern bool isWirelessConnected;
#endif

