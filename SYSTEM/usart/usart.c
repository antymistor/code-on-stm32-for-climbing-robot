#include "sys.h"
#include "usart.h"	 
#include "MYMISC.h"
#include "MOTO_CTR.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
float t[12]={0};
u16 timed;
u8 modeflag=1;
int in[3]={0};
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
#if 1
#pragma import(__use_no_semihosting)             
 
u8 cnum=0;
u8 dectr[9];
float todegree;
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
 
  
void uart_init(u32 bound){

  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
  
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART1, ENABLE);                    

}
u8 num2set(u8 num)
{
	u8 N=10;
	if(num==0){N=5;}
	else if(num==1){N=2;}
	else if(num==2){N=7;}
	else if(num==3){N=4;}
	else if(num==4){N=1;}
	else if(num==5){N=3;}
	else if(num==6){N=6;}
	else if(num==7){N=8;}
	return N;
}
u8 num3set(u8 num)
{
	u8 N=10;
	if(num==0){N=0;}
	else if(num==1){N=1;}
	else if(num==2){N=3;}
	else if(num==3){N=2;}
	return N;
}
Logic num4set(u8 num)
{
	Logic p=OFF;
	if(num==1){p=ON;}
	return p;
}

void USART1_IRQHandler(void)                	
	{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
		{
		Res =USART_ReceiveData(USART1);	
		if ( (Res>='A')&& (Res<='I') )
		{
			cnum=1;
			dectr[0]=Res;
		}
		else if(cnum>0)
		{
			if ( ( (Res>='0')&& (Res<='9') ) || (Res=='.')||(Res=='+')||(Res=='-')||(Res=='P')||(Res=='T') )
			{
			if( (cnum==1)&&(Res=='T')){modeflag=0;}
			dectr[cnum]=Res;
			cnum++;
			}
			
			else if( (cnum==1)&&(Res=='K'))
			{
				motor_ctr(dectr[0]-'A'+1,forward,1500);
				delay_ms(200);
				motor_ctr(dectr[0]-'A'+1,stop,1);
				cnum=0;
			}
			else if( (cnum==1)&&(Res=='L'))
			{
				motor_ctr(dectr[0]-'A'+1,backward,1500);
				delay_ms(200);
				motor_ctr(dectr[0]-'A'+1,stop,1);
				cnum=0;
			}
			else
			cnum=0;
		}
		
		
		if((cnum==6)&&modeflag)
		{
			cnum=0;
			if( (dectr[0]>='A')&& (dectr[0]<='H') )
			{
				todegree=(float)((dectr[2]-'0')*10+(dectr[3]-'0') )+(float)(dectr[5]-'0')/10;
				if(dectr[1]=='-')
				{todegree=-1*todegree;}
				
				if(dectr[4]=='.')
				{
				t[dectr[0]-'A']=todegree;
				//set_angel(dectr[0]-'A'+1,t[dectr[0]-'A']);
        }
				
				else if(dectr[4]=='P')
				{
					if(todegree>0){
						
						motor_ctr(dectr[0]-'A'+1,forward,1500);
						timed=(u16)(todegree);
						delay_ms(timed*3);
						motor_ctr(dectr[0]-'A'+1,stop,1500);
						
					}
					else{
						
						motor_ctr(dectr[0]-'A'+1,backward,1500);
						timed=(u16)(-1*todegree);
						delay_ms(timed*3);
						motor_ctr(dectr[0]-'A'+1,stop,1500);
						
					}
				}
				
			}
			else if( dectr[0]=='I' )
			{
				t[8]=dectr[1]-'0';
				t[9]=dectr[2]-'0';
				t[10]=dectr[3]-'0';
				t[11]=dectr[4]-'0';
			}
		}
    else if(cnum==9)
		{
			if(modeflag==0&&dectr[5]=='P')
			{
				if(dectr[0]!='I')
				{in[0]=num2set(dectr[0]-'A');
				in[1]=(dectr[2]-'0')*100+(dectr[3]-'0')*10+(dectr[4]-'0');
				in[2]=(dectr[6]-'0')*100+(dectr[7]-'0')*10+(dectr[8]-'0')-99;}
				else
				{
					valve_ctr( 0  ,num4set((u8)(dectr[2]-'0')));
					valve_ctr( 1 ,num4set((u8)(dectr[3]-'0')));
					valve_ctr( 3  ,num4set((u8)(dectr[4]-'0')));
					valve_ctr( 2 ,num4set((u8)(dectr[6]-'0')));
					
				}
				
			}
			modeflag=1;
			cnum=0;
		}			
		
	}
} 






