// Damn Kernel :P

#ifndef _KERNI_h
#define _KERNI_h
#include "micrOS_Storage.h"
#include "micrOS_Graphics_Cache.h"
#include "micrOS_Power_Management.h"
#include "Kernel_Returns.h"
#include "Kern_Errors.h"

#define kMicroVersion "micrOS.Emily_kernel 1.3 micrOS Kernel Version 1.2 TUE JANUARY 2 DEVELOPMENT"
#define kBootLoaderREV "micrOS BootLoader REV. 1.18.21, TUE December 19 DEVELOPMENT"
#define kUSERNAME ">GeoSn0w"
#define KERN_DEFAULT_CPU "ATmega1280"
#define KERN_SUPPORTED_ARCH "AVR"//Ls20
#define KERN_FUSE "DEVELOPMENT" //should be changed to RELEASE to disable verbose boot
extern String CURRENT_FOREGROUND_PID;
extern uint16_t BootMode;
extern uint16_t debug;
typedef int kern_return_t;
typedef int kern_platform_t;
typedef int proc_return_t;
typedef int task_return_t;
typedef uint8_t emily_trap_rv;
typedef int proc_t;
typedef uint8_t ucred_t;
typedef uint8_t proc_lifetime_t;
typedef String ucred_identity_card_t;
extern ucred_identity_card_t IdentityCard;
ucred_t check_entitlements(bool isDebugged, bool isSystemApp, bool hasCustomTheme, bool hasFileSystemAccess, bool writesEEPROM, bool readsEEPROM, bool hasGPIOAccess);
kern_return_t kernel_I_haz_panic(String panic_reason);
kern_return_t switchboard_set_bars(uint16_t UIColor);
kern_return_t switchboard_set_misc(void);
kern_return_t switchboard_set_wallpaper(void);
void switchboard_integrity_check(void);
kern_return_t micrOS_SwitchBoard(void);
kern_return_t AWAIT_TOUCH_SG(void);
void buildAlert(char message[], char sub[], char title[], int x, int y, int xsub, int ysub, bool dismissable);
kern_return_t kernDisplayReload(void);
kern_return_t sigabrt(kern_return_t panic_reason);
kern_return_t kernRegisterNewApp(void);
kern_return_t sigareport(int signal);
kern_return_t kernKillActiveApp(void);
kern_return_t shutdown(void);
bool checkID(ucred_identity_card_t);
extern bool isMenuOpen;
extern bool SysSdutDownReqConfirm;
extern bool isCharging;
extern bool inApp;
extern bool isWirelessConnected;
#endif

