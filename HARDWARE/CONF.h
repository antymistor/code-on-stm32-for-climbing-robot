#ifndef _CONF_H_
#define _CONF_H_
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
extern u16 t_us;
extern u16 t_ms;
extern u16 t_sec;
extern u16 t_min;
extern u16 t_hour;
extern float t[12];
typedef enum
{
	ON,
	OFF
}Logic;


typedef enum
{
	forward,
	backward,
	stop
}Direction;
#endif

