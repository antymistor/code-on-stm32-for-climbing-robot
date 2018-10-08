#ifndef _MYMISC_H_
#define _MYMISC_H_
#include "CONF.h"
void initMisc(void);
void beeper_init(void);
void beep(u8 a);
void beep_shortly(u16 a);
void valve_init(void);
void valve_ctr(u8 num,Logic p);
void time_init(void);
void delay_init(void);
void delay_ms(u16 nms);
#endif

