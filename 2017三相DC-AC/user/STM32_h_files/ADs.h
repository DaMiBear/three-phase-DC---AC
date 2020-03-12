#include "stm32f10x.h"
#include "OLED.h"
#define  ADC1_DR_Address    ((u32)0x40012400+0x4c)
/*�����������ADC_ConvertedValue[4],�ֱ��AD1ͨ��10��11ת��������*/
__IO uint16_t ADC_ConvertedValue[4];


//������ʹ������
/*int main()
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
	OLED_Init();
	OLED_Clear();
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
			
      //  OLED_ShowNum(68,0,ADC_ConvertedValue[0],4,12);
	}
	return 0;
}*/
/*
* ��������ADC1_GPIO_Config
* ���� ��ʹ��ADC1��DMA1��ʱ��,����PC0��PC1Ϊģ������
* ���� : ��
* ��� ����
* ���� ���ڲ�����
*/
static void ADC1_GPIO_Config(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
	/* Enable DMA clock */
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
 /* Enable ADC1 and GPIOC clock */
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/* ��������ADC1_Mode_Config
* ���� ������ADC1�Ĺ���ģʽΪMDAģʽ
* ���� : ��
* ��� ����
* ���� ���ڲ�����
*/
static void ADC1_Mode_Config(void)
{
 DMA_InitTypeDef  DMA_InitStructure;
 ADC_InitTypeDef  ADC_InitStructure;
 /* DMA channel1 configuration */
 DMA_DeInit(DMA1_Channel1);
 /*����DMA�������ַ,��Ϊ���ת������ļĴ���*/
 DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Address;
 /*�����ڴ����ַ*/
 DMA_InitStructure.DMA_MemoryBaseAddr =(u32)&ADC_ConvertedValue;
 /*����AD������Ϊ���ݴ������Դ*/
 DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
 /*ָ��DMAͨ����DMA����Ĵ�С,����Ҫ���ټ����ڴ�ռ䣬��ʵ��������ת��ͨ�������Կ�������*/
 DMA_InitStructure.DMA_BufferSize = 4;
	/*�趨�Ĵ�����ַ�̶�*/
 DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
 /*�趨�ڴ��ַ�ݼӣ���ÿ��DMA���ǽ�������Ĵ����е�ֵ�����ĸ��ڴ�ռ���*/
 DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
/*�趨�������ݿ��*/	
 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	/*�趨�ڴ�ĵĿ��*/
 DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	/*�趨DMA������ѭ������ģʽ*/
 DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
 /*�趨DMAѡ����ͨ��������ȼ�*/
 DMA_InitStructure.DMA_Priority = DMA_Priority_High;
 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
 DMA_Init(DMA1_Channel1, &DMA_InitStructure);
 /* Enable DMA channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
	
	// ADC_DeInit(ADC1);//��ʼ��ADC1
	/*����ADC�����ڶ���ģʽ*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
/*�涨ADת��������ɨ��ģʽ�����Զ��ͨ������*/	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;
	/*�趨ADת��������ģʽ*/
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	/*��ʹ���ⲿ�ٷ�ת��*/
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	/*�ɼ��������ڼĴ��������Ҷ���ķ�ʽ���*/
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	/*�趨Ҫת����ADͨ����Ŀ*/
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_Init(ADC1, &ADC_InitStructure);
	/*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9MHz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
/*����ADC1��ͨ��10��11��ת���Ⱥ�˳���Լ�����ʱ��ΪΪ55.5���������� */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_13Cycles5);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/*��λУ׼�Ĵ��� */
	ADC_ResetCalibration(ADC1);
	/*�ȴ�У׼�Ĵ�����λ��� */
	while(ADC_GetResetCalibrationStatus(ADC1));
	/* ADCУ׼ */
	ADC_StartCalibration(ADC1);
	/* �ȴ�У׼���*/
	while(ADC_GetCalibrationStatus(ADC1));
	/* ����û�в����ⲿ����������ʹ���������ADCת�� */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
uchar AD1_a,AD1_b,AD1_c;
uchar AD2_a,AD2_b,AD2_c;
uchar AD3_a,AD3_b,AD3_c;
uchar AD4_a,AD4_b,AD4_c;
//�趨ȫ�ֱ������ڷ�������
 int AD_Result1=0,AD_Result2 = 0,AD_Result3 = 0,AD_Result4 = 0;		
void read_ADC()
{
  uchar i;
  unsigned int result1=0,result2 = 0,result3 = 0,result4 = 0;

  for(i=0;i<4;i++)
  {
     result1 +=ADC_ConvertedValue[0];
		 result2 +=ADC_ConvertedValue[1];
		 result3 +=ADC_ConvertedValue[2];
		 result4 +=ADC_ConvertedValue[3];
  }
    result1 = result1 >>2;                              //ȡ4�β�����ƽ��ֵ
		result2 = result2 >>2;
		result3 = result3 >>2;
		result4 = result4 >>2;
	
    result1 = (unsigned int)(((unsigned long)result1)*3300>>12);//�Ѳɼ�������ֵת���ɵ�ѹ����
		result2 = (unsigned int)(((unsigned long)result2)*3300>>12);
		result3 = (unsigned int)(((unsigned long)result3)*3300>>12);
		result4 = (unsigned int)(((unsigned long)result4)*3300>>12);

		AD_Result1 = result1;
		AD_Result2 = result2;
		AD_Result3 = result3;
		AD_Result4 = result4;
		
		//��ΪС����ʾ
    AD1_a = result1/1000;                //a.bc
    AD1_b = (result1-AD1_a*1000)/100;
    AD1_c = (result1-AD1_a*1000-AD1_b*100)/10;
	
		AD2_a = result2/1000;                //a.bc
    AD2_b = (result2-AD2_a*1000)/100;
    AD2_c = (result2-AD2_a*1000-AD2_b*100)/10;
	
		AD3_a = result3/1000;                //a.bc
    AD3_b = (result3-AD3_a*1000)/100;
    AD3_c = (result3-AD3_a*1000-AD3_b*100)/10;
		
		AD4_a = result4/1000;                //a.bc
    AD4_b = (result4-AD4_a*1000)/100;
    AD4_c = (result4-AD4_a*1000-AD4_b*100)/10;

}