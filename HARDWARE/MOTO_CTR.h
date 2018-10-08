#ifndef _MOTO_CTR_H_
#define _MOTO_CTR_H_
#include "CONF.h"
#include "stm32f10x.h"

void DC_PWM_init(void);
void motor_init(void);
void motor_ctr(u8 number,Direction dir,u16 speed);
void servomotor_init(void);
void servomotor_ctr(u8 num,u8 angel);
void mod_angel(void);
void set_angel(u8 num, float angel);
#endif

