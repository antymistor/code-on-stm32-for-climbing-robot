#include "CONF.h"
#include "MYMISC.h"

static u8  fac_us=0;									   
static u16 fac_ms=0;
u16 t_us=0;
u16 t_ms=0;
u16 t_sec=0;
u16 t_min=0;
u16 t_hour=0;
void initMisc(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	delay_init();
  beeper_init();
	valve_init();
	//time_init();
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
void valve_init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                                                      
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
}

void valve_ctr(u8 num,Logic p)
{
	if(num==0)
	{
		if(p==ON)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_0);                                                   
		}
	}
	if(num==1)
	{
		if(p==ON)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_1);
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		}
	}
	if(num==2)
	{
		if(p==ON)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_2);
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_2);
		}
	}
	if(num==3)
	{
		if(p==ON)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_3);
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		}
	}
}
void beeper_init()
{
	 GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void beep(u8 a)
{
	if(a)
	{ GPIO_SetBits(GPIOC,GPIO_Pin_13);}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	}
}

void beep_shortly(u16 a)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	delay_ms(a);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void time_init()
{
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
t_us=0;
t_ms=0;
t_sec=0;
t_min=0;
t_hour=0;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 

TIM_TimeBaseStructure.TIM_Period = 999; 
TIM_TimeBaseStructure.TIM_Prescaler = 71;   
TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;  
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
TIM_ITConfig(TIM6,TIM_IT_Update, ENABLE);   
TIM_Cmd(TIM6, ENABLE);     
	
NVIC_InitStructure.NVIC_IRQChannel =TIM6_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
}

void TIM6_IRQHandler(void)
{
if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
{
TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
 t_ms++;
 if(t_ms==1000)
 {t_ms=0;t_sec++;
	 if(t_sec==60)
	 {t_sec=0;t_min++;
		 if(t_min==60)
		 {t_min==0;t_hour++;}
	 }
 }
}
}


void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	fac_us=SystemCoreClock/8000000;				
	fac_ms=(u16)fac_us*1000;					
}								    

void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				
	SysTick->VAL =0x00;							
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
	SysTick->VAL =0X00;       				  
} 
