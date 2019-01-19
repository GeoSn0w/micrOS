// Damn Kernel :P

#ifndef _KERNI_h
#define _KERNI_h
#include "micrOS_Storage.h"
#include "micrOS_Graphics_Cache.h"
#include "micrOS_Power_Management.h"
#include "Kernel_Returns.h"
#include <TouchScreen.h>
#include "Kern_Errors.h"
#define EMILY_KERN_DEBUG
#define kMicroVersion "micrOS.Emily_kernel 1.4 micrOS Kernel Version 1.4 TUE JANUARY 2 DEVELOPMENT"
#define kBootLoaderREV "micrOS BootLoader REV. 1.18.21, TUE December 19 DEVELOPMENT"
#define kUSERNAME ">GeoSn0w"
#define KERN_DEFAULT_CPU "ATmega2560"
#define KERN_SUPPORTED_ARCH "AVR"//Ls20
extern uint16_t BootMode;
typedef int kern_platform_t;
typedef int proc_return_t;
typedef int task_return_t;
typedef uint8_t emily_trap_rv;
typedef int proc_t;
typedef uint8_t ucred_t;
typedef uint8_t proc_lifetime_t;
typedef String ucred_identity_card_t;
kern_return_t kernel_I_haz_panic(String panic_reason);
kern_return_t switchboard_set_bars(uint16_t UIColor);
kern_return_t switchboard_set_misc(void);
kern_return_t switchboard_set_wallpaper(void);
kern_return_t touchEvalAtPoint(TSPoint p);
kern_return_t set_bar_fill(uint16_t ThemeScheme);
void switchboard_integrity_check(void);
kern_return_t micrOS_SwitchBoard(void);
kern_return_t AWAIT_TOUCH_SG(void);
void buildAlert(char message[], char sub[], char title[], int x, int y, int xsub, int ysub, bool dismissable);
kern_return_t kernDisplayReload(void);
kern_return_t sigabrt(kern_return_t panic_reason);
kern_return_t kernRegisterNewApp(void);
kern_return_t sigareport(int signal);
extern int issApp;
kern_return_t get_user_config(const char *config_file_ds);
kern_return_t kernKillActiveApp(void);
kern_return_t shutdown(void);
void loadSettings(void);
kern_return_t setCurrentForeGroundPID(proc_t pid);
struct micro_config_lsz_user_data
{
	String username;
	int current_theme_id;
	bool is_developer_mode;
};
extern struct micro_config_lsz_user_data userdata;
extern proc_t ForegroundPID;
extern int isAlert;
extern bool isMenuOpen;
extern bool SysSdutDownReqConfirm;
extern bool isCharging;
extern bool inApp;
extern bool isWirelessConnected;
#endif

