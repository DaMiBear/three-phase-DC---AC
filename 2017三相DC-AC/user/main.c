#include "stm32f10x.h"
#include "PWM.h"
#include "Update_Interrupt.h"
#include "ADs.h"
#include "Key_Scan.h"
int main()
{
	float Uref=0.5;
	float Iref=1;
	time3_init();										//�����жϳ�ʼ��
	ADC1_GPIO_Config();								//AD��ʼ��
	ADC1_Mode_Config();		
	OLED_Init();									//OLED��ʼ��
	OLED_Clear();	
	Key_Scan_Init();							//4*4������ʼ��
	time248_gpio();										//PWM
	time8_init(SPWM_TABLE[0]);				//TIM8 ��CH2ͨ��		��PC7��
	time4_init(SPWM_TABLE[149],SPWM_TABLE[299]);//TIM4��CH3ͨ��		��PB8��		�� CH4ͨ��		��PB9��
	
	
  time2_init(SPWM_TABLE[0],SPWM_TABLE[149],SPWM_TABLE[299]);
//		OLED_ShowString(0,0,"Please Scanf Uref");
	//���OK���Ƿ��� ��K�Ƿ�ֵ?
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
		//�����1
		//��ѹ��������
		//����ɼ����ĵ�ѹ�Ȳο���ѹ�����С�����1�ĵ��Ʊ�
//		if(AD_Result1 - Uref >0.5)
//		{
//			m1-=0.1;
//		}
//		//��֮�����ӵ��Ʊ�
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
		
			//�����2
		//������������
		//����ɼ����ĵ����Ȳο����������С�����2�ĵ��Ʊ�
//		if(AD_Result3 > Iref)
//		{
//			m2 -=0.1;
//		}
//		//��֮�����ӵ��Ʊ�
//		if(AD_Result3 < Iref)
//		{
//			m2+=0.1;
//		}
		
	}
	
}