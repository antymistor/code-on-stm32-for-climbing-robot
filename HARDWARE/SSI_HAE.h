#ifndef __SSI_HAE_H
#define __SSI_HAE_H
#include "sys.h"
void CSN_Init(void);
void DO_Init(void);
void TIM2_Init(void);
void SSI_init(void);
float read_degree(u8 sw);
#endif

