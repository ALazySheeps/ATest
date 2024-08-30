#ifndef __BU_H
#define __BU_H

#include "main.h"
#include <stdint.h>
#include "DWT.h"

//#include "stm32f10x.h"
#define Buzzer_ON() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)
#define Buzzer_OFF() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)

void play_music(void);


#endif

