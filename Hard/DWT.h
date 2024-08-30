/**
 *****************************东莞理工学院ACE实验室 *****************************
 * @file DWT.c/h
 * @brief DWT计数器
 * @note 使用前先初始化，此后不能再使用HAL_Delay函数，可使用这里的延时函数
 * @history 2024/7/9
            2024/7/10 添加了结构体
 *
 @verbatim 
 ==============================================================================
使能计数器，延时功能
 ==============================================================================
 @endverbatim
 *****************************东莞理工学院ACE实验室 *****************************
 */

#ifndef __DWT_DELAY_H
#define __DWT_DELAY_H

#include "stm32f1xx_hal.h"

#define  DWT_CYCCNT  *(__IO uint32_t *)0xE0001004

/*记录时间结构体*/
typedef struct{
    uint32_t t_min,t_s,t_ms;
    uint32_t pre;  //上一次记录的时间戳
    uint32_t t_new;  //当前时间戳
    uint32_t err,ms_err;
    uint32_t count;  //屏幕刷新次数
}time_t;

extern time_t time;

/* 内核时钟频率 */
#define SysClockFreq            (72000000)//HAL_RCC_GetSysClockFreq()
/* 为方便使用，在延时函数内部调用CPU_TS_TmrInit函数初始化时间戳寄存器，
   这样每次调用函数都会初始化一遍。
   把本宏值设置为0，然后在main函数刚运行时调用CPU_TS_TmrInit可避免每次都初始化 */  

#define CPU_TS_INIT_IN_DELAY_FUNCTION   0  
#define ONE_MS_TICKS (SysClockFreq / 1000) //1ms的节拍
#define OLED_REFRESH_10Hz (7200000) //屏幕刷新节拍
#define OLED_REFRESH_20Hz (3600000)
#define OLED_REFRESH_25Hz (2880000)
#define OLED_REFRESH_30Hz (2400000)
#define OLED_REFRESH_50Hz (1440000)
#define OLED_REFRESH_60Hz (1200000)
#define OLED_REFRESH_100Hz (720000)
#define OLED_REFRESH_150Hz (480000)

/*******************************************************************************
 * 函数声明
 ******************************************************************************/
uint32_t CPU_TS_TmrRd(void);
void DWT_InitTick(void);

//使用以下函数前必须先调用CPU_TS_TmrInit函数使能计数器，或使能宏CPU_TS_INIT_IN_DELAY_FUNCTION
//最大延时值为8秒

void CPU_TS_Tmr_Delay_US(uint32_t us);
#define CPU_TS_Tmr_Delay_MS(ms)     CPU_TS_Tmr_Delay_US(ms*1000)
#define CPU_TS_Tmr_Delay_S(s)       CPU_TS_Tmr_Delay_MS(s*1000)


#endif
