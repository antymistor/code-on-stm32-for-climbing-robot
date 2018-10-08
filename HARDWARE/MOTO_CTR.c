#include "CONF.h"
#include "MOTO_CTR.h"
#include "SSI_HAE.h"
#include "MYMISC.h"
#include "usart.h"
float r[8]={0};
void DC_PWM_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	TIM_OCInitTypeDef              TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	
	TIM_DeInit(TIM3);
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Period=1999;                
  TIM_TimeBaseStructure.TIM_Prescaler=71;     
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM4, ENABLE);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                              
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;    
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    
  TIM_OCInitStructure.TIM_Pulse=0;
  
  TIM_OC1Init(TIM3,&TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM3,&TIM_OCInitStructure);   
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC3Init(TIM3,&TIM_OCInitStructure);  
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC4Init(TIM3,&TIM_OCInitStructure);   
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	 TIM_OC1Init(TIM4,&TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM4,&TIM_OCInitStructure);   
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC3Init(TIM4,&TIM_OCInitStructure);  
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC4Init(TIM4,&TIM_OCInitStructure);   
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_Cmd(TIM3,ENABLE);
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
}

void motor_init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   DC_PWM_init();
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE); 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_15; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_15);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   GPIO_SetBits(GPIOB,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	 GPIO_Init(GPIOC, &GPIO_InitStructure);
	 GPIO_SetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	 GPIO_Init(GPIOD, &GPIO_InitStructure);
	 GPIO_SetBits(GPIOD,GPIO_Pin_2);
	 
}
void servomotor_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	TIM_OCInitTypeDef              TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_DeInit(TIM5);
	TIM_TimeBaseStructure.TIM_Period=1999;                
  TIM_TimeBaseStructure.TIM_Prescaler=719;     
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM5, ENABLE);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                              
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;    
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    
  TIM_OCInitStructure.TIM_Pulse=0;
  
  TIM_OC1Init(TIM5,&TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM5,&TIM_OCInitStructure);   
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
  TIM_OC3Init(TIM5,&TIM_OCInitStructure);  
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
  TIM_OC4Init(TIM5,&TIM_OCInitStructure);   
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);

	TIM_Cmd(TIM5,ENABLE);
	TIM_CtrlPWMOutputs(TIM5,ENABLE);

}

void servomotor_ctr(u8 num,u8 angel)
{
	if(num==1)
	{TIM_SetCompare1(TIM5,angel);}
	else if(num==2)
	{TIM_SetCompare2(TIM5,angel);}
	else if(num==3)
	{TIM_SetCompare3(TIM5,angel);}
	else if(num==4)
	{TIM_SetCompare4(TIM5,angel);}
}

void motor_ctr(u8 number,Direction dir,u16 speed)
{
 if(number==1)
	{
		if(dir==forward)
		{
	   GPIO_SetBits(GPIOB,GPIO_Pin_5);
	   GPIO_ResetBits(GPIOB,GPIO_Pin_4);
		}
		else if(dir==backward)
		{
		 GPIO_SetBits(GPIOB,GPIO_Pin_4);
	   GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		}
		else
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_4);
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
		}
		 TIM_SetCompare1(TIM4,speed);
	}
	else if(number==2)
	{
		if(dir==forward)
		{
	   GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	   GPIO_SetBits(GPIOD,GPIO_Pin_2);
		}
		else if(dir==backward)
		{
		 GPIO_ResetBits(GPIOD,GPIO_Pin_2);
	   GPIO_SetBits(GPIOB,GPIO_Pin_3);
		}
		else
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_2);
			GPIO_SetBits(GPIOB,GPIO_Pin_3);
		}
		 TIM_SetCompare2(TIM4,speed);
	}
	else if(number==3)
	{
		if(dir==forward)
		{
	   GPIO_SetBits(GPIOC,GPIO_Pin_11);
	   GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		}
		else if(dir==backward)
		{
		 GPIO_SetBits(GPIOC,GPIO_Pin_12);
	   GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_12);
			GPIO_SetBits(GPIOC,GPIO_Pin_11);
		}
		 TIM_SetCompare3(TIM4,speed);
	}
	else if(number==4)
	{
		if(dir==forward)
		{
	   GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	   GPIO_SetBits(GPIOA,GPIO_Pin_15);
		}
		else if(dir==backward)
		{
		 GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	   GPIO_SetBits(GPIOC,GPIO_Pin_10);
		}
		else
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_15);
			GPIO_SetBits(GPIOC,GPIO_Pin_10);
		}
		 TIM_SetCompare4(TIM4,speed);
	}
	
	
	else if(number==5)
	{
		if(dir==forward)
		{
	   GPIO_SetBits(GPIOC,GPIO_Pin_4);
	   GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		}
		else if(dir==backward)
		{
		 GPIO_SetBits(GPIOC,GPIO_Pin_5);
	   GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_5);
			GPIO_SetBits(GPIOC,GPIO_Pin_4);
		}
		 TIM_SetCompare2(TIM3,speed);
	}
	else if(number==6)
	{
		if(dir==backward)
		{
	   GPIO_SetBits(GPIOA,GPIO_Pin_5);
	   GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		}
		else if(dir==forward)
		{
		 GPIO_SetBits(GPIOA,GPIO_Pin_4);
	   GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		}
		else
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
		}
		 TIM_SetCompare1(TIM3,speed);
	}
	else if(number==7)
	{
		if(dir==forward)
		{
	   GPIO_SetBits(GPIOB,GPIO_Pin_13);
	   GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		}
		else if(dir==backward)
		{
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
	   GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		}
		else
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
		}
		 TIM_SetCompare4(TIM3,speed);
	}
	else if(number==8)
	{
		if(dir==backward)
		{
	   GPIO_SetBits(GPIOB,GPIO_Pin_2);
	   GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		}
		else if(dir==forward)
		{
		 GPIO_SetBits(GPIOB,GPIO_Pin_10);
	   GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		}
		else
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_10);
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
		}
		 TIM_SetCompare3(TIM3,speed);
	}
}

u8 num_set(u8 num)
{
	u8 N;
	if(num==7){N=2;}
	else if(num==5){N=0;}
	else if(num==2){N=6;}
	else if(num==4){N=4;}
	else {N=10;}
	return N;
}

void mod_angel(void)
{
	u8 num;
	u16 power;
	float P;
	float de;
	//printf("%.1f %.1f\r\n",t[6],t[3]);
	for(num=1;num<9;num++)
	{
		if(num_set(num)<9)
		{
		  if( (t[num-1]<=90)&&(t[num-1]>=-90) )
	    {
//	      if((de=read_degree( num_set(num) ))>(t[num-1]+0.3))
//	     {
//		    power=(u16) ((de-t[num-1])*200.f+200);
//		    if(power>1990){power=1990;}
//		    motor_ctr(num,backward,power);
//	     }
//	     else if((de=read_degree( num_set(num) ))<(t[num-1]-0.3))
//	     {
//		   power=(u16) ((t[num-1]-de)*200.f+200);
//		   if(power>1990){power=1990;}
//		   motor_ctr(num,forward,power);
//	     }
				de=read_degree( num_set(num) );
				P=(t[num-1]-de)*50.f -(de-r[num-1])*50;
				r[num-1]=de;
				if(P>10)
					{power=(u16)(P+200.f); 
					 if(power>1990){power=1990;}
					 motor_ctr(num,forward,power);
				  }
				else if(P<-10)
				  {power=(u16)(-1*P+200.f); 
					 if(power>1990){power=1990;}
					 motor_ctr(num,backward,power);
				  }
			 else{   motor_ctr(num,stop,1);  }
			}
			else{   motor_ctr(num,stop,1);  }
	  }
   }
	if(t[8]==0){valve_ctr(3,OFF);}else{valve_ctr(3,ON);}
	if(t[9]==0){valve_ctr(0,OFF);}else{valve_ctr(0,ON);}
	if(t[10]==0){valve_ctr(2,OFF);}else{valve_ctr(2,ON);}
	if(t[11]==0){valve_ctr(1,OFF);}else{valve_ctr(1,ON);}
	delay_ms(20);
	//printf("%.1f %.1f\r\n",read_degree(2),read_degree(4));
 }

 
void set_angel(u8 num, float angel)
{
	float de;
	u16 power;
	if(num_set(num)<9)
	{
	if( (angel>90)||(angel<-90) )
	  {return ;
	  }
	while((de=read_degree( num_set(num) ))>(angel+0.3))
	  {
			//printf("%.1f %.1f\r\n",de,angel);
			//delay_ms(100);
		 power=(u16) ((de-angel)*50.f+300);
		 if(power>1990){power=1990;}
		 motor_ctr(num,backward,power);
		 delay_ms(40);
	  }
	 while((de=read_degree( num_set(num) ))<(angel-0.3))
	  {
		 //printf("%.1f %.1f\r\n",de,angel);
			//delay_ms(100);
		 power=(u16) ((angel-de)*50.f+250);
		 if(power>1990){power=1990;}
		 motor_ctr(num,forward,power);
		 delay_ms(40);
	  }
	   motor_ctr(num,stop,1);
		//printf("%.1f %.1f\r\n",read_degree( num_set(num) ),angel);
   }
}