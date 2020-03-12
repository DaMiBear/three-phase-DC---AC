#include "stm32f10x.h"
#include "OLED.h"
#define  ADC1_DR_Address    ((u32)0x40012400+0x4c)
/*定义数组变量ADC_ConvertedValue[4],分别放AD1通道10和11转换的数据*/
__IO uint16_t ADC_ConvertedValue[4];


//主函数使用如下
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
* 函数名：ADC1_GPIO_Config
* 描述 ：使能ADC1和DMA1的时钟,设置PC0，PC1为模拟输入
* 输入 : 无
* 输出 ：无
* 调用 ：内部调用
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
/* 函数名：ADC1_Mode_Config
* 描述 ：配置ADC1的工作模式为MDA模式
* 输入 : 无
* 输出 ：无
* 调用 ：内部调用
*/
static void ADC1_Mode_Config(void)
{
 DMA_InitTypeDef  DMA_InitStructure;
 ADC_InitTypeDef  ADC_InitStructure;
 /* DMA channel1 configuration */
 DMA_DeInit(DMA1_Channel1);
 /*定义DMA外设基地址,即为存放转换结果的寄存器*/
 DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Address;
 /*定义内存基地址*/
 DMA_InitStructure.DMA_MemoryBaseAddr =(u32)&ADC_ConvertedValue;
 /*定义AD外设作为数据传输的来源*/
 DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
 /*指定DMA通道的DMA缓存的大小,即需要开辟几个内存空间，本实验有两个转换通道，所以开辟两个*/
 DMA_InitStructure.DMA_BufferSize = 4;
	/*设定寄存器地址固定*/
 DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
 /*设定内存地址递加，即每次DMA都是将该外设寄存器中的值传到四个内存空间中*/
 DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
/*设定外设数据宽度*/	
 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	/*设定内存的的宽度*/
 DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	/*设定DMA工作再循环缓存模式*/
 DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
 /*设定DMA选定的通道软件优先级*/
 DMA_InitStructure.DMA_Priority = DMA_Priority_High;
 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
 DMA_Init(DMA1_Channel1, &DMA_InitStructure);
 /* Enable DMA channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
	
	// ADC_DeInit(ADC1);//初始化ADC1
	/*设置ADC工作在独立模式*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
/*规定AD转换工作在扫描模式，即对多个通道采样*/	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;
	/*设定AD转化在连续模式*/
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	/*不使用外部促发转换*/
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	/*采集的数据在寄存器中以右对齐的方式存放*/
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	/*设定要转换的AD通道数目*/
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_Init(ADC1, &ADC_InitStructure);
	/*配置ADC时钟，为PCLK2的8分频，即9MHz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
/*配置ADC1的通道10和11的转换先后顺序以及采样时间为为55.5个采样周期 */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_13Cycles5);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/*复位校准寄存器 */
	ADC_ResetCalibration(ADC1);
	/*等待校准寄存器复位完成 */
	while(ADC_GetResetCalibrationStatus(ADC1));
	/* ADC校准 */
	ADC_StartCalibration(ADC1);
	/* 等待校准完成*/
	while(ADC_GetCalibrationStatus(ADC1));
	/* 由于没有采用外部触发，所以使用软件触发ADC转换 */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
uchar AD1_a,AD1_b,AD1_c;
uchar AD2_a,AD2_b,AD2_c;
uchar AD3_a,AD3_b,AD3_c;
uchar AD4_a,AD4_b,AD4_c;
//设定全局变量用于反馈控制
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
    result1 = result1 >>2;                              //取4次采样的平均值
		result2 = result2 >>2;
		result3 = result3 >>2;
		result4 = result4 >>2;
	
    result1 = (unsigned int)(((unsigned long)result1)*3300>>12);//把采集到的数值转换成电压数据
		result2 = (unsigned int)(((unsigned long)result2)*3300>>12);
		result3 = (unsigned int)(((unsigned long)result3)*3300>>12);
		result4 = (unsigned int)(((unsigned long)result4)*3300>>12);

		AD_Result1 = result1;
		AD_Result2 = result2;
		AD_Result3 = result3;
		AD_Result4 = result4;
		
		//化为小数显示
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