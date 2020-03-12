#include "stm32f10x.h"

//������ʹ������(����stm32f10x_adc.h)
//int main()
//{
//  ADCx_Init();
//	
// 
//   
//  read_ADC();
//  OLED_ShowNum(32,0,AD_a,1,12);            // y  x   number length    bits
//          OLED_ShowNum(48,0,AD_b,1,12);
//          OLED_ShowNum(56,0,AD_c,1,12);
//          OLED_ShowNum(65,0,AD_d,1,12);
//          delay(10);

//return 0;
//}

#define uint unsigned int 
#define uchar unsigned char

void ADCx_Init();
void read_ADC();
uchar AD_a,AD_b,AD_c,AD_d;
float  AD_Result=0;
//�����Ӷ˿ڸı�ʱ����Ҫ�ı�һ�º궨��   
#define		AD_GPIO								GPIOA				//ADCʹ�õ�IO

#define   AD1                   GPIO_Pin_4	//IO����
#define   AD_Channel						ADC_Channel_4//��Ӧͨ��


void ADCx_Init()
{
  ADC_InitTypeDef ADC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
  //ADC��������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             //����Ϊģ������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_InitStructure.GPIO_Pin = AD1|GPIO_Pin_5;
  GPIO_Init(AD_GPIO,&GPIO_InitStructure);
  
  ADC_DeInit(ADC1);                                       //������ADCx��ȫ���Ĵ�������ΪĬ��ֵ
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         //ADC�����ڶ���ģʽ
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     //�Ҷ���
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;        //����ģʽ
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���崥����ʽ���˴�Ϊ�������
  ADC_InitStruct.ADC_NbrOfChannel = 1;                    //����ADC���й���ת����ADCͨ����Ŀ
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;              //��ͨ��
  ADC_Init(ADC1,&ADC_InitStruct);
  
  
  //********************************************
  //����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
  //ʹ��ADCx   ģ��ͨ��y  ������� ����ʱ��
  //********************************************
  ADC_RegularChannelConfig(ADC1,AD_Channel,1,ADC_SampleTime_71Cycles5);

   ADC_Cmd(ADC1,ENABLE);                                 //ADCʹ��
   ADC_ResetCalibration (ADC1);                         //����ָ����ADC1��У׼�Ĵ���
   while(ADC_GetResetCalibrationStatus(ADC1));          //��ȡADC1����У׼�Ĵ�����״̬��ֱ��У׼�Ĵ����������
   ADC_StartCalibration(ADC1);                          //��ʼָ��ADC��У׼״̬
   while(ADC_GetCalibrationStatus(ADC1));               //��ȡָ��ADC��У׼����ֱ��У׼���
   ADC_SoftwareStartConvCmd(ADC1,ENABLE);                //ʹ��ADCx�����ת����������
}

//��ȡ�ɼ�����ADC����
void read_ADC()
{
  uchar i;
  unsigned short result=0;
  unsigned short id;
  for(i=0;i<8;i++)
  {
     ADC_SoftwareStartConvCmd(ADC1,ENABLE);             //����ADCת��
    do
    {
      id = ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC);        //��ȡת����־
    }while(!id);
    
    result +=ADC_GetConversionValue(ADC1);
  }
    result = result >>3;                              //ȡ8�β�����ƽ��ֵ
    result = (unsigned int)(((unsigned long)result)*3300>>12);//�Ѳɼ�������ֵת���ɵ�ѹ����
		AD_Result = (float) result/1000;
    AD_a = result/1000;                //a.bcd
    AD_b = (result-AD_a*1000)/100;
    AD_c = (result-AD_a*1000-AD_b*100)/10;
    AD_d = result%10;
}

