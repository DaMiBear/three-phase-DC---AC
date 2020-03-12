#include "stm32f10x.h"


//主函数使用如下
//int main()
//{
//	Key_Scan_Init();
//	
//	while(1)
//	{	
//		Key_Scan();
//	}	
//	return 0;
//}

#define uint unsigned int 
#define uchar unsigned char
#define 		X1_H			GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define 		X2_H			GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define 		X3_H			GPIO_SetBits(GPIOA,GPIO_Pin_10)
#define 		X4_H			GPIO_SetBits(GPIOA,GPIO_Pin_9)


#define			X1_L			GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define			X2_L			GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define			X3_L			GPIO_ResetBits(GPIOA,GPIO_Pin_10)
#define			X4_L			GPIO_ResetBits(GPIOA,GPIO_Pin_9)

void Key_Scan_Init();
void Ket_Scan();


extern  void OLED_ShowNum(uchar x,uchar y,unsigned long num,uchar len,uchar size);
extern  void OLED_ShowString(uchar x,uchar y,uchar *chr);
extern  void OLED_Clear(void);
void Key_Scan_Init()
{
	
	
	//选中引脚为推挽输出
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			
	GPIO_Init(GPIOA,&GPIO_InitStructure);		

	//选中引脚为浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			
	GPIO_Init(GPIOA,&GPIO_InitStructure);		
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			
	GPIO_Init(GPIOC,&GPIO_InitStructure);		
	
}

int number[9]={0,0,0,0,0,0,0,0,0};
int Nu=0;
float  K=0;
void Key_Delay()
{
	int i,j;
	for(i=0;i<=100000;i++)
	{
			for(j=0;j<=100;j++);
	}
} 
 //float Uref=0;
void Key_Scan()
{
		X1_H;
		X2_L;X3_L;X4_L;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8))		{number[Nu]=7;Nu++;OLED_ShowNum(32,0,7,1,12);Key_Delay();       }
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9))   {number[Nu]=8;Nu++;OLED_ShowNum(32,0,8,1,12); Key_Delay();	  	}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))   {number[Nu]=9;Nu++;OLED_ShowNum(32,0,9,1,12); Key_Delay();			}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)) 
			{
//			K=number[0]+(float)number[1]/10+(float)number[2]/100;
//				OLED_ShowString(0,0,"U = 0.00");
//				OLED_ShowNum(32,0,number [0],1,12);
//				OLED_ShowNum(48,0,number [1],1,12);
//				OLED_ShowNum(56,0,number [2],1,12);
//				Key_Delay();
				
				}
		
		X2_H;
		X1_L;X3_L;X4_L;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8))		{number[Nu]=4;Nu++;OLED_ShowNum(32,0,4,1,12);  Key_Delay();     }
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9))   {number[Nu]=5;Nu++;OLED_ShowNum(32,0,5,1,12); 	Key_Delay();		}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))   {number[Nu]=6;Nu++;OLED_ShowNum(32,0,6,1,12);	  Key_Delay();   	}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))   {	  	}
		
		X3_H;
		X1_L;X2_L;X4_L;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8))		{number[Nu]=1;Nu++;OLED_ShowNum(32,0,1,1,12); Key_Delay();      }
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9))   {number[Nu]=2;Nu++;OLED_ShowNum(32,0,2,1,12);   Key_Delay();		}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))   {number[Nu]=3;Nu++;OLED_ShowNum(32,0,3,1,12); 	Key_Delay();  	}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))   {  		}
		
		X4_H;
		X1_L;X2_L;X3_L;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8))		{     }
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9))   {  	number[Nu]=0;Nu++;OLED_ShowNum(32,0,0,1,12);Key_Delay(); 	}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))   {	 		}
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))   {  OLED_Clear();		}
}
