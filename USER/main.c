#include "MYMISC.h"
#include "usart.h"
#include "MOTO_CTR.h"
#include "SSI_HAE.h"
#include "math.h"
#define PI 3.14159265f
//#define L  30.0f
//#define L1 15.0f
//#define L2 15.0f
int main()
{
u16 count;
//double x,y;
//double a,b;
//double temp1,temp2,temp3,temp4,temp5;
//float tx[70];
//float ty[70];
	float a[4]={0};
	u8 i;
	SystemInit();
	initMisc();
	SSI_init();
	motor_init();
  //SSI_init();
	servomotor_init();
	uart_init(9600);
	read_degree(0);read_degree(1);read_degree(2);read_degree(3);read_degree(4);read_degree(5);read_degree(6);read_degree(7);
	//t[6]=90;
//	set_angel(7,45);
//	set_angel(7,45);
//	set_angel(7,45);
//	set_angel(4,45);
//	set_angel(4,45);
//	set_angel(4,45);
//	delay_ms(1000);
//	set_angel(7,45);
//	set_angel(7,45);
//	set_angel(7,45);
//	set_angel(4,45);
//	set_angel(4,45);
//	set_angel(4,45);
//	set_angel(4,45);
//	set_angel(4,45);
//	set_angel(4,45);
//  delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//x=y=45;
time_init();
//for(i=1;i<=80;i++)
//{
//	x=x-0.5;
//	temp1=x*PI/180;
//	b=acos((1.8476f-cos(temp1))/1.613f);
//	temp2=1.613f*cos(temp1-b)+1;
//	temp3=1.613f*sin(temp1-b);
//	temp4=sqrt(temp2*temp2+temp3*temp3);
//	temp5=atan(temp3/temp2);
//	y=acos(1.8476f/temp4)-temp5;
//	y=y*180/PI;
//	tx[i-1]=(float)x;
//	ty[i-1]=(float)y;
////}	
//for(i=1;i<=70;i++)
//{
//	x=x-0.5;
//	temp1=x*PI/180;
//	b=acos((1.9142f-cos(temp1))/1.7071f);
//	temp2=1.7071f*cos(temp1-b)+1;
//	temp3=1.7071f*sin(temp1-b);
//	temp4=sqrt(temp2*temp2+temp3*temp3);
//	temp5=atan(temp3/temp2);
//	y=acos(1.9142f/temp4)-temp5;
//	y=y*180/PI;
//	tx[i-1]=(float)x;
//	ty[i-1]=(float)y;
//}	
//for(i=0;i<=69;i++)
//{
//	t[6]=tx[i];
//	t[3]=ty[i];
//	mod_angel();
//	printf("%.1f %.1f\r\n",read_degree(2),read_degree(4));
//	//printf("%.2f %.2f %.1f %.1f\r\n",t[6],t[3],t[6],t[3]);
//}	
//t[6]=tx[79];t[3]=ty[79];
//set_angel(7,-30);
//delay_ms(1000);






//valve_ctr(3,ON);
//delay_ms(1000);





//set_angel(7,0);
//delay_ms(1000);

//set_angel(5,-30);
//delay_ms(1000);
//valve_ctr(0,ON);
//delay_ms(1000);
//set_angel(5,0);
//delay_ms(1000);

//valve_ctr(3,OFF);
//valve_ctr(0,OFF);
//valve_ctr(1,ON);
//valve_ctr(2,ON);
//delay_ms(1000);

//set_angel(2,-30);
//delay_ms(1000);
//valve_ctr(1,OFF);
//delay_ms(1000);
//set_angel(2,0);
//delay_ms(1000);

//set_angel(4,-30);
//delay_ms(1000);
//valve_ctr(2,OFF);
//delay_ms(1000);
//set_angel(4,0);
//delay_ms(1000);

//motor_ctr(6,backward,1900);
//motor_ctr(1,backward,1900);
//motor_ctr(3,forward,1900);
//motor_ctr(8,backward,1900);
//delay_ms(1000);
//delay_ms(500);

//motor_ctr(6,stop,1900);
//motor_ctr(1,stop,1900);
//motor_ctr(3,stop,1900);
//motor_ctr(8,stop,1900);
//delay_ms(1000);
//delay_ms(1000);
//delay_ms(1000);
//delay_ms(1000);

//motor_ctr(6,forward,1900);
//motor_ctr(1,forward,1900);
//motor_ctr(3,backward,1900);
//motor_ctr(8,forward,1900);
//delay_ms(1000);
//delay_ms(500);

//motor_ctr(6,stop,1900);
//motor_ctr(1,stop,1900);
//motor_ctr(3,stop,1900);
//motor_ctr(8,stop,1900);
//delay_ms(300);

while(1)
	{
//	t[6]=tx[69];t[3]=ty[69];
//	mod_angel();
// intf("%.1f %.1f\r\n",read_degree(2),read_degree(4));
//	for(i=0;i<=69;i++)
//{
//	t[6]=tx[i];
//	t[3]=ty[i];
	//mod_angel();
	 
		if(in[1]>0)
		{
			
			in[1]-=100;
			if(in[2]>=0)
			{motor_ctr((u8)in[0],forward,(u16)(in[2]*20));}
		  else
			{motor_ctr((u8)in[0],backward,(u16)(-in[2]*20));}
			
		}
		else{in[1]=0;
		motor_ctr((u8)in[0],stop,0);
		}
	delay_ms(100);
	//	printf("10.0 %.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0fZ",read_degree(0),read_degree(6),read_degree(2),read_degree(4),a[0],a[1],a[2],a[3]);

	printf("10.0 %.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0fZ",read_degree(0),read_degree(6),read_degree(2),read_degree(4),read_degree(1),read_degree(7),read_degree(3),read_degree(5));
	
		
//	//printf("%.2f %.2f %.1f %.1f\r\n",t[6],t[3],t[6],t[3]);
//}	
//   count=50;
//while(count--){
//	t[6]=tx[69];t[3]=ty[69];
//	mod_angel();
//  printf("%.1f %.1f\r\n",read_degree(2),read_degree(4));
//}
//	for(i=0;i<=69;i++)
//{
//	t[6]=tx[69-i];
//	t[3]=ty[69-i];
//	mod_angel();
//	printf("%.1f %.1f\r\n",read_degree(2),read_degree(4));
//	//printf("%.2f %.2f %.1f %.1f\r\n",t[6],t[3],t[6],t[3]);
//}	
//count=50;
//while(count--){
//	t[6]=45;t[3]=45;
//	mod_angel();
//  printf("%.1f %.1f\r\n",read_degree(2),read_degree(4));
//set_angel(7,-30);
//delay_ms(1000);
//valve_ctr(3,ON);
//delay_ms(1000);
//set_angel(7,0);
//delay_ms(1000);

//set_angel(5,-30);
//delay_ms(1000);
//valve_ctr(0,ON);
//delay_ms(1000);
//set_angel(5,0);
//delay_ms(1000);

//valve_ctr(3,OFF);
//valve_ctr(0,OFF);
//valve_ctr(1,ON);
//valve_ctr(2,ON);
//delay_ms(1000);

//set_angel(2,-30);
//delay_ms(1000);
//valve_ctr(1,OFF);
//delay_ms(1000);
//set_angel(2,0);
//delay_ms(1000);

//set_angel(4,-30);
//delay_ms(1000);
//valve_ctr(2,OFF);
//delay_ms(1000);
//set_angel(4,0);
//delay_ms(1000);
  }
}
  

 