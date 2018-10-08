#include "SSI_HAE.h"
#include "CONF.h"
u8 CS_fl=1;
u8 CS_count=0;
u32 data_in=0;
u32 data_f=0;
u8  readfinish_f=0;
u8  swi=0;
float pretemp[4]={36.5f,37.8f,37.9f,73.0f};
u8 predex[4]={1,1,1,1};

void SSI_init(void)
{
TIM2_Init();	
CSN_Init();
DO_Init();
}

void CSN_Init(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7| GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_11;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_11);
	GPIO_SetBits(GPIOB, GPIO_Pin_5|GPIO_Pin_15);
	GPIO_SetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7| GPIO_Pin_8|GPIO_Pin_9);
	
}
void DO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void TIM2_Init(void)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE); 
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); 
  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;          
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
	TIM_TimeBaseStructure.TIM_Period = 199;\
	TIM_TimeBaseStructure.TIM_Prescaler =2;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE );		
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  
  TIM_SetCompare4(TIM2,100);
	 
	TIM_Cmd(TIM2, ENABLE); 
}


float read_degree(u8 sw)
{
	float degree=0;
	CS_fl=1;
  CS_count=0;
	readfinish_f=0;
	swi=sw;
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );
	while(!readfinish_f){;}
	degree=((   (float)((data_f&0x0003ffc0)>>6)  )/4096)*360;
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE );
	if(sw==2)
	{degree =(degree-107.8f)*0.9333f;}
	else if(sw==0){ degree=(133.0f-degree)*0.9333f;}
	else if(sw==6){ degree=(degree-140.5f)*0.9333f;}
	else if(sw==4){ degree=(204.2f-degree)*0.9333f;}
	else if(sw==1){ 
		if((degree-pretemp[0])<-300){predex[0]=1;}
    if((degree-pretemp[0])>300){predex[0]=0;}
		pretemp[0]=degree;
	  if(predex[0]==1){
		   degree=(degree-40.f)*0.35f;
		}
		else if(degree>100){degree=((-360.f+degree)-40.f)*0.35f;}
		else{degree=(degree-40.f)*0.35f;}
	}
	else if(sw==7){ 
		if((degree-pretemp[1])<-300){predex[1]=1;}
    if((degree-pretemp[1])>300){predex[1]=0;}
		pretemp[1]=degree;
	  if(predex[1]==1){
		   degree=(37.8f-degree)*0.35f;
		}
		else if(degree>100){degree=((360.f-degree)+37.8f)*0.35f;}
		else{degree=(-degree+37.8f)*0.35f;}
	}
	else if(sw==3){ 
		if((degree-pretemp[2])<-300){predex[2]=1;}
    if((degree-pretemp[2])>300){predex[2]=0;}
		pretemp[2]=degree;
	  if(predex[2]==1){
		   degree=(37.9f-degree)*0.35f;
		}
		else if(degree>100){degree=((360.f-degree)+37.9f)*0.35f;}
		else{degree=(-degree+37.9f)*0.35f;}
	}
	else if(sw==5){ 
		if((degree-pretemp[3])<-300){predex[3]=1;}
    if((degree-pretemp[3])>300){predex[3]=0;}
		pretemp[3]=degree;
	  if(predex[3]==1){
		   degree=(degree-73.0f)*0.35f;
		}
		else if(degree>100){degree=((-360.f+degree)-73.0f)*0.35f;}
		else{degree=(degree-73.0f)*0.35f;}
	}
	return degree; 
}
void TIM2_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  ); 
			if(CS_fl)
			{
				if(CS_count>0)
				{
				 if(!swi)
				 {GPIO_ResetBits(GPIOB,GPIO_Pin_14);}
				 else if(swi==1)
				 { GPIO_ResetBits(GPIOB,GPIO_Pin_15);}
				 else if(swi==2)
				 {GPIO_ResetBits(GPIOC,GPIO_Pin_6);}
				 else if(swi==3)
				 {GPIO_ResetBits(GPIOC,GPIO_Pin_7);}
				 else if(swi==4)
				 {GPIO_ResetBits(GPIOC,GPIO_Pin_8);}
				  else if(swi==5)
				 {GPIO_ResetBits(GPIOC,GPIO_Pin_9);}
				  else if(swi==6)
				 {GPIO_ResetBits(GPIOA,GPIO_Pin_8);}
				  else if(swi==7)
				 {GPIO_ResetBits(GPIOA,GPIO_Pin_11);}
				 CS_count=0;
				 CS_fl=0;
				}
				else
				{
				  CS_count++;
				}
			}
			else
			{
				if(CS_count>16)
				{
				 data_in=(data_in<<1)+GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
				 //data_in=(data_in<<1)+1;
				 data_f=data_in;
				 readfinish_f=1;
				 data_in=0;
				 if(!swi)
				 {GPIO_SetBits(GPIOB,GPIO_Pin_14);}
				 else if(swi==1)
				 {GPIO_SetBits(GPIOB,GPIO_Pin_15);}	
				 else if(swi==2)
				 {GPIO_SetBits(GPIOC,GPIO_Pin_6);}
				 else if(swi==3)
				 {GPIO_SetBits(GPIOC,GPIO_Pin_7);}
				 else if(swi==4)
				 {GPIO_SetBits(GPIOC,GPIO_Pin_8);}
				 else if(swi==5)
				 {GPIO_SetBits(GPIOC,GPIO_Pin_9);}
				 else if(swi==6)
				 {GPIO_SetBits(GPIOA,GPIO_Pin_8);}
				 else if(swi==7)
				 {GPIO_SetBits(GPIOA,GPIO_Pin_11);}
				 CS_count=0;
				 CS_fl=1;
				}
				else
				{
				 CS_count++;
				 data_in=(data_in<<1)+GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
				 //data_in=(data_in<<1)+1;
				}
			}
		}
}
