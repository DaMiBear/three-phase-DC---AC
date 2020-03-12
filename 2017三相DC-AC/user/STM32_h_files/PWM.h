#include "stm32f10x.h"
void time8_init(float D2) ;
void time248_gpio();
void time2_init(float D2,float D3,float D4);

#define			TIM8_OCInit								TIM_OC2Init
#define			TIM8_OCPreload						TIM_OC2PreloadConfig
#define			TIM2_OCInit								TIM_OC4Init
#define			TIM2_OCPreload						TIM_OC4PreloadConfig
#define			GPIO_Clock_PWM1						RCC_APB2Periph_GPIOC
#define			GPIO_Clock_PWM1N					RCC_APB2Periph_GPIOB
#define			GPIO_Clock_PWM2						RCC_APB2Periph_GPIOA
#define			GPIO_PWM1									GPIOC
#define			GPIO_PWM1N								GPIOB
#define			GPIO_PWM2									GPIOA
#define			GPIO_Pin_PWM1							GPIO_Pin_7
#define			GPIO_Pin_PWM1N						GPIO_Pin_0
#define 		GPIO_Pin_PWM2							GPIO_Pin_3

//int main()
//{
//	
//	time_gpio();
//	time8_init(0.1,0.2,0.3,0.4);
//  time2_init(0.9,0.8,0.7,0.6);

//return 0;
//}
//TIM8
//初始化定时器
void time8_init(float D2)     																			 //D---Duty
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//打开外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);

	//*************************************************************************
	//定时器设置           22.5KHz
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 1599;						//用于设置在下一个更新事件装入活动的自动装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 1;					      //设置用来作为TIMx时钟频率除数的预分频值 频率 = (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;					//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			//选择计数模式 TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //
	TIM_TimeBaseInit(TIM8 , &TIM_TimeBaseStructure);				//根据以上功能对定时器进行初始化
	// TIM_ARRPreloadConfig(TIM8, ENABLE); 
	//主定时器为PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;								//TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		//选择输出比较状态，使能输出比较状态
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	//失能输出比较N状态												
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;				//TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			//互补输出极性
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //   //MOE=0时，重置TIM输出比较空闲状态
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//		//MOE=0时，重置TIM输出比较空闲N状态
	//CH1
//	TIM_OCInitStructure .TIM_Pulse = 1600*D1;
//	TIM_OC1Init(TIM8,&TIM_OCInitStructure);							
//	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);

	//CH2
	TIM_OCInitStructure.TIM_Pulse = D2;						//占空比为50%（设置待装入捕获比较寄存器的脉冲值）Pulse=(Period*Duty)
	TIM8_OCInit(TIM8,&TIM_OCInitStructure);													
	TIM8_OCPreload(TIM8,TIM_OCPreload_Enable);								//使能的预装载寄存器	
	
	//CH3	
//	TIM_OCInitStructure .TIM_Pulse = 1600*D3;
//	TIM_OC3Init(TIM8,&TIM_OCInitStructure);							
//	TIM_OC3PreloadConfig(TIM8,TIM_OCPreload_Enable);
	
 
	TIM_Cmd(TIM8,ENABLE);																							//使能定时器
	TIM_CtrlPWMOutputs(TIM8,ENABLE);																//使能TIM8主输出
}
//TIM2
void time2_init(float D2,float D3,float D4)
{
  TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//打开外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

	//*************************************************************************
	//定时器设置
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 1599;													//用于设置在下一个更新事件装入活动的自动装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 1;											//设置用来作为TIMx时钟频率除数的预分频值 频率 (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;									//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			//选择计数模式 TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //
	TIM_TimeBaseInit(TIM2 , &TIM_TimeBaseStructure);								//根据以上功能对定时器进行初始化
	// TIM_ARRPreloadConfig(TIM8, ENABLE); 
	//主定时器为PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;								//TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		//选择输出比较状态，使能输出比较状态
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	//失能输出比较N状态												
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;				//TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			//互补输出极性
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //   //MOE=0时，重置TIM输出比较空闲状态
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//		//MOE=0时，重置TIM输出比较空闲N状态
	
	//CH2
	TIM_OCInitStructure.TIM_Pulse = D2;
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	//CH3
	TIM_OCInitStructure.TIM_Pulse = D3;
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	//CH4
	TIM_OCInitStructure.TIM_Pulse = D4;														//占空比为50%（设置待装入捕获比较寄存器的脉冲值）Pulse=(Period*Duty)
	TIM2_OCInit(TIM2,&TIM_OCInitStructure);													//CH2占空比为50%
	TIM2_OCPreload(TIM2,TIM_OCPreload_Enable);								//使能的预装载寄存器	
	
 
	TIM_Cmd(TIM2,ENABLE);																							//使能定时器
}

void time4_init(float D3,float D4)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//打开外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);

	//*************************************************************************
	//定时器设置
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 1599;													//用于设置在下一个更新事件装入活动的自动装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 1;											//设置用来作为TIMx时钟频率除数的预分频值 频率 (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;									//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			//选择计数模式 TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //
	TIM_TimeBaseInit(TIM4 , &TIM_TimeBaseStructure);								//根据以上功能对定时器进行初始化
	//主定时器为PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;								//TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		//选择输出比较状态，使能输出比较状态
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	//失能输出比较N状态												
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;				//TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			//互补输出极性
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //   //MOE=0时，重置TIM输出比较空闲状态
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//		//MOE=0时，重置TIM输出比较空闲N状态
	
	//CH3
	TIM_OCInitStructure.TIM_Pulse = D3;										//占空比
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	//CH4
	TIM_OCInitStructure.TIM_Pulse = D4;
	TIM_OC4Init(TIM4,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4,ENABLE);	
	
}
//*****************************************************************************
//定义输出引脚
//*****************************************************************************
void time248_gpio()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_Clock_PWM1|GPIO_Clock_PWM2|RCC_APB2Periph_GPIOB,ENABLE);
	
  //TIM2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_PWM2|GPIO_Pin_1|GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PWM2,&GPIO_InitStructure);
	//TIM4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//TIM8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_PWM1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PWM1,&GPIO_InitStructure);
}
