#ifndef EB_COMMON_H
#define EB_COMMON_H

#include <stdbool.h>

//#define EASYBENCH_VERSION "v1.0.0"

#define MAJOR_VERSION 1
#define MINOR_VERSION 0
#define PATCH_VERSION 0

#define DEFAULT_FILE "/var/run/easybench.pid"

#define PCB_TCP_SERVER_IP   "192.168.3.188"
#define PCB_TCP_SERVER_PORT 8000


#define SINGLETON        1

#define QT_VERSION_4     0  /* Recommend to use Qt5 strongly */
#define QT_VERSION_5     1

#define SEAT_TEST        1  /* All of configuration files use test files */

#define LANGUAGE_CHINESE 1  /* All the text show as Chinese, please always enable */

#define FIXED_WINDOWN    1  /* Fixed window size or not */
#define WINDOW_DESKTOP
/* #define WINDOW_EMBEDDED */

#if FIXED_WINDOWN
#define FIXED_WINDOWN_WIDTH 1024
#ifdef WINDOW_DESKTOP
#define FIXED_WINDOWN_HEIGHT 720
#else
#define FIXED_WINDOWN_HEIGHT 768
#endif
#endif
#define TITLE_HEIGHT 40

#define CONNECT_STM32    0  /* Connect to base board (STM32) via ethernet */

#ifdef GY_GLOBAL
#define GY_GLOBAL_EXT
#else
#define GY_GLOBAL_EXT extern
#endif

typedef enum TouchType{
    TOUCH_NONE = 0,
    TOUCH_RESISTIVE,
    TOUCH_CAPACITIVE,
    TOUCH_OTHER
}TouchType;

//GY_GLOBAL_EXT TouchType TOUCH_TYPE;
//GY_GLOBAL_EXT bool HAS_EEPROM;

//GY_GLOBAL_EXT char gMachineTypeStr[80];
GY_GLOBAL_EXT char gSerialPortStr[32];
//GY_GLOBAL_EXT char gVideoInputStr[32];

//GY_GLOBAL_EXT char BACKLIGHT_NAME[32];
//GY_GLOBAL_EXT unsigned int LCD_WIDTH;
//GY_GLOBAL_EXT unsigned int LCD_HEIGHT;

typedef struct Audio_Parameter {
    int frame_size;
    int max_frame_size;
    int sample_rate;
    int buffer_size_ratio;
} Audio_Parameter;

#pragma pack(push)
#pragma pack(1)

typedef struct applyCMD {
    unsigned char head;
    unsigned char size;
    unsigned char type;
    unsigned char snum;
    unsigned char cmdw;
    unsigned char csum;
    unsigned char tail;
}applyCMD;

typedef struct controlCMD {
    unsigned char head;
    unsigned char size;
    unsigned char type;
    unsigned char snum;
    unsigned char cmdw;
    unsigned char mode; // 0x00: Standard, 0x01: Debug
    unsigned char reserve1[2];
    float fanSpeed;
    unsigned char reserve2[4];
    unsigned char csum;
    unsigned char tail;
}controlCMD;

typedef struct readStatusCMD {
    unsigned char head;
    unsigned char size;
    unsigned char type;
    unsigned char snum;
    unsigned char cmdw;
    unsigned char serialStatus; // 0x00: Abnormal, 0x01: Normal
    unsigned char reserve1[2];
    float temperature1;
    float temperature2;
    float fanSpeed;
    unsigned char reserve2[2];
    unsigned char csum;
    unsigned char tail;
 }readStatusCMD;

typedef struct readVersionCMD {
     unsigned char head;
     unsigned char size;
     unsigned char type;
     unsigned char snum;
     unsigned char cmdw;
     unsigned char reserve1[3];
     unsigned char firmwareVer[4];
     unsigned char hardwareVer[2];
     unsigned char reserve2[2];
     unsigned char reserve3[8];
     unsigned char csum;
     unsigned char tail;
}readVersionCMD;

#pragma pack(pop)


#ifdef __cplusplus
extern "C"{
#endif

unsigned char calcCheckSum(unsigned char *data, unsigned int len);
bool is_singleton(void);
int get_timezone(void);

#ifdef __cplusplus
}
#endif


#endif // EB_COMMON_H
