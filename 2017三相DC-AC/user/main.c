#include "stm32f10x.h"
#include "PWM.h"
#include "Update_Interrupt.h"
#include "ADs.h"
#include "Key_Scan.h"
int main()
{
	float Uref=0.5;
	float Iref=1;
	time3_init();										//更新中断初始化
	ADC1_GPIO_Config();								//AD初始化
	ADC1_Mode_Config();		
	OLED_Init();									//OLED初始化
	OLED_Clear();	
	Key_Scan_Init();							//4*4按键初始化
	time248_gpio();										//PWM
	time8_init(SPWM_TABLE[0]);				//TIM8 的CH2通道		（PC7）
	time4_init(SPWM_TABLE[149],SPWM_TABLE[299]);//TIM4的CH3通道		（PB8）		和 CH4通道		（PB9）
	
	
  time2_init(SPWM_TABLE[0],SPWM_TABLE[149],SPWM_TABLE[299]);
//		OLED_ShowString(0,0,"Please Scanf Uref");
	//检测OK键是否按下 即K是否赋值?
//	while(1)
//	{
//		if(Uref !=0)
//		{
//		break;
//		}
//	}



	OLED_ShowString(0,0,"u1= 0.00");
	OLED_ShowString(0,2,"u2= 0.00");
	OLED_ShowString(0,4,"u3= 0.00");
	OLED_ShowString(0,6,"u4= 0.00");
	while(1)
	{
				read_ADC();
				OLED_ShowNum(32,0,AD1_a,1,12);           
        OLED_ShowNum(48,0,AD1_b,1,12);
				OLED_ShowNum(56,0,AD1_c,1,12);
		
				OLED_ShowNum(32,2,AD2_a,1,12);           
        OLED_ShowNum(48,2,AD2_b,1,12);
				OLED_ShowNum(56,2,AD2_c,1,12);
		
				OLED_ShowNum(32,4,AD3_a,1,12);           
        OLED_ShowNum(48,4,AD3_b,1,12);
				OLED_ShowNum(56,4,AD3_c,1,12);
		
				OLED_ShowNum(32,6,AD4_a,1,12);           
        OLED_ShowNum(48,6,AD4_b,1,12);
				OLED_ShowNum(56,6,AD4_c,1,12);
		//逆变器1
		//电压反馈控制
		//如果采集到的电压比参考电压大，则减小逆变器1的调制比
//		if(AD_Result1 - Uref >0.5)
//		{
//			m1-=0.1;
//		}
//		//反之，增加调制比
//		if(AD_Result1 -Uref < -0.5)
//		{
//			m1+=0.1;
//		}
//		if((AD_Result1  - Uref >0)&&(AD_Result1 - Uref <=0.5))
//		{
//			m1 -=0.02;
//		}
//		if((AD_Result1  - Uref <0)&&(AD_Result1 - Uref >=-0.5))
//		{
//			m1 -=0.02;
//		}
//if(AD_Result1 - Uref >0)
//{
////	t1 ++;
////	t2++;
////	t3++;
//	m1-=0.02;
//}
//if(AD_Result1 - Uref <0)
//{
////	t1--;
////	t2--;
////	t3--;
//	m1+=0.02;
//}
		
			//逆变器2
		//电流反馈控制
		//如果采集到的电流比参考电流大，则减小逆变器2的调制比
//		if(AD_Result3 > Iref)
//		{
//			m2 -=0.1;
//		}
//		//反之，增加调制比
//		if(AD_Result3 < Iref)
//		{
//			m2+=0.1;
//		}
		
	}
	
}