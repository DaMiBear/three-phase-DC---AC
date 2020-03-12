#include "stm32f10x.h"

//主函数使用如下(包含stm32f10x_adc.h)
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
//在连接端口改变时，需要改变一下宏定义   
#define		AD_GPIO								GPIOA				//ADC使用的IO

#define   AD1                   GPIO_Pin_4	//IO引脚
#define   AD_Channel						ADC_Channel_4//对应通道


void ADCx_Init()
{
  ADC_InitTypeDef ADC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
  //ADC输入引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             //配置为模拟输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_InitStructure.GPIO_Pin = AD1|GPIO_Pin_5;
  GPIO_Init(AD_GPIO,&GPIO_InitStructure);
  
  ADC_DeInit(ADC1);                                       //将外设ADCx的全部寄存器重设为默认值
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         //ADC工作在独立模式
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     //右对齐
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;        //单次模式
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//定义触发方式，此处为软件触发
  ADC_InitStruct.ADC_NbrOfChannel = 1;                    //设置ADC进行规则转换的ADC通道数目
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;              //单通道
  ADC_Init(ADC1,&ADC_InitStruct);
  
  
  //********************************************
  //设置指定ADC的规则组通道，设置他们的转换顺序和采样时间
  //使用ADCx   模拟通道y  采样序号 采样时间
  //********************************************
  ADC_RegularChannelConfig(ADC1,AD_Channel,1,ADC_SampleTime_71Cycles5);

   ADC_Cmd(ADC1,ENABLE);                                 //ADC使能
   ADC_ResetCalibration (ADC1);                         //重置指定的ADC1的校准寄存器
   while(ADC_GetResetCalibrationStatus(ADC1));          //获取ADC1重置校准寄存器的状态，直到校准寄存器重设完成
   ADC_StartCalibration(ADC1);                          //开始指定ADC的校准状态
   while(ADC_GetCalibrationStatus(ADC1));               //获取指定ADC的校准程序，直到校准完成
   ADC_SoftwareStartConvCmd(ADC1,ENABLE);                //使能ADCx的软件转换启动功能
}

//读取采集到的ADC数据
void read_ADC()
{
  uchar i;
  unsigned short result=0;
  unsigned short id;
  for(i=0;i<8;i++)
  {
     ADC_SoftwareStartConvCmd(ADC1,ENABLE);             //启动ADC转换
    do
    {
      id = ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC);        //读取转换标志
    }while(!id);
    
    result +=ADC_GetConversionValue(ADC1);
  }
    result = result >>3;                              //取8次采样的平均值
    result = (unsigned int)(((unsigned long)result)*3300>>12);//把采集到的数值转换成电压数据
		AD_Result = (float) result/1000;
    AD_a = result/1000;                //a.bcd
    AD_b = (result-AD_a*1000)/100;
    AD_c = (result-AD_a*1000-AD_b*100)/10;
    AD_d = result%10;
}

