#include "stm32f10x.h"

int SPWM_TABLE[] = {
6, 17, 28, 39, 50, 61, 72, 83, 94, 106,
117, 128, 139, 150, 160, 171, 182, 193, 204, 215,
225, 236, 247, 257, 268, 278, 289, 299, 309, 319,
330, 340, 350, 360, 370, 380, 389, 399, 409, 418,
428, 437, 446, 455, 465, 474, 482, 491, 500, 509,
517, 526, 534, 542, 550, 558, 566, 574, 582, 589,
597, 604, 611, 618, 625, 632, 639, 646, 652, 658,
665, 671, 677, 683, 688, 694, 699, 705, 710, 715,
720, 724, 729, 733, 738, 742, 746, 750, 754, 757,
761, 764, 767, 770, 773, 776, 778, 781, 783, 785,
787, 789, 790, 792, 793, 794, 795, 796, 797, 797,
798, 798, 798, 798, 798, 797, 797, 796, 795, 794,
793, 792, 790, 789, 787, 785, 783, 781, 778, 776,
773, 770, 767, 764, 761, 757, 754, 750, 746, 742,
738, 733, 729, 724, 720, 715, 710, 705, 699, 694,
688, 683, 677, 671, 665, 658, 652, 646, 639, 632,
625, 618, 611, 604, 597, 589, 582, 574, 566, 558,
550, 542, 534, 526, 517, 509, 500, 491, 482, 474,
465, 455, 446, 437, 428, 418, 409, 399, 389, 380,
370, 360, 350, 340, 330, 319, 309, 299, 289, 278,
268, 257, 247, 236, 225, 215, 204, 193, 182, 171,
160, 150, 139, 128, 117, 106, 94, 83, 72, 61,
50, 39, 28, 17, 6, -6, -17, -28, -39, -50,
-61, -72, -83, -94, -106, -117, -128, -139, -150, -160,
-171, -182, -193, -204, -215, -225, -236, -247, -257, -268,
-278, -289, -299, -309, -319, -330, -340, -350, -360, -370,
-380, -389, -399, -409, -418, -428, -437, -446, -455, -465,
-474, -482, -491, -500, -509, -517, -526, -534, -542, -550,
-558, -566, -574, -582, -589, -597, -604, -611, -618, -625,
-632, -639, -646, -652, -658, -665, -671, -677, -683, -688,
-694, -699, -705, -710, -715, -720, -724, -729, -733, -738,
-742, -746, -750, -754, -757, -761, -764, -767, -770, -773,
-776, -778, -781, -783, -785, -787, -789, -790, -792, -793,
-794, -795, -796, -797, -797, -798, -798, -798, -798, -798,
-797, -797, -796, -795, -794, -793, -792, -790, -789, -787,
-785, -783, -781, -778, -776, -773, -770, -767, -764, -761,
-757, -754, -750, -746, -742, -738, -733, -729, -724, -720,
-715, -710, -705, -699, -694, -688, -683, -677, -671, -665,
-658, -652, -646, -639, -632, -625, -618, -611, -604, -597,
-589, -582, -574, -566, -558, -550, -542, -534, -526, -517,
-509, -500, -491, -482, -474, -465, -455, -446, -437, -428,
-418, -409, -399, -389, -380, -370, -360, -350, -340, -330,
-319, -309, -299, -289, -278, -268, -257, -247, -236, -225,
-215, -204, -193, -182, -171, -160, -150, -139, -128, -117,
-106, -94, -83, -72, -61, -50, -39, -28, -17, -6};
int SPWM_TABLE_n1=0;
int SPWM_TABLE_n2=149;
int SPWM_TABLE_n3=299;
//int main()   //需要添加(stm32f10x_tim.c  misc.c)
//{ 
//  time3_init();

//	return 0;
//}
void time3_init();
extern void Key_Scan();

void time3_init()
{
  TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	//打开外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

	//*************************************************************************
	//定时器设置
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 1599;													//用于设置在下一个更新事件装入活动的自动装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 1;											//设置用来作为TIMx时钟频率除数的预分频值 频率 (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;									//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			//选择计数模式 TIM向上计数模式
	TIM_TimeBaseInit(TIM3 , &TIM_TimeBaseStructure);								//根据以上功能对定时器进行初始化
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                //开定时器中断
  TIM_Cmd(TIM3,ENABLE);                                  //使能定时器
 
  //使能TIM3中断
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                   //使能指定IRQ通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;         //设置中断先占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                //从优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   //使能NVIC IRQChannel中定义的IRQ通道
  NVIC_Init(&NVIC_InitStructure);
} 
float m1=0.82,m2=0.71;//逆变器1和逆变器2的调制比
int t1,t2,t3;
void TIM3_IRQHandler()
{   
   if(TIM_GetITStatus(TIM3,TIM_IT_Update) !=RESET)
   {
     TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		 
		 Key_Scan();
		 
		 //逆变器1的SPWM
		  t1 =m1* SPWM_TABLE[SPWM_TABLE_n1]+800;
			t2 =m1* SPWM_TABLE[SPWM_TABLE_n2]+800;
			t3 =m1* SPWM_TABLE[SPWM_TABLE_n3]+800;
		 TIM_SetCompare2(TIM2,t1);
		 TIM_SetCompare3(TIM2,t2);
		 TIM_SetCompare4(TIM2,t3);
			//逆变器2的SPWM
			t1 =m2* SPWM_TABLE[SPWM_TABLE_n1]+800;
			t2 =m2* SPWM_TABLE[SPWM_TABLE_n2]+800;
			t3 =m2* SPWM_TABLE[SPWM_TABLE_n3]+800;
		 TIM_SetCompare2(TIM8,t1);
		 TIM_SetCompare3(TIM4,t2);
		 TIM_SetCompare4(TIM4,t3);
			SPWM_TABLE_n1++;
		  SPWM_TABLE_n2++;
		  SPWM_TABLE_n3++;
		 if(SPWM_TABLE_n1 ==450)
		 {
			SPWM_TABLE_n1 = 0;
		 }
		 if(SPWM_TABLE_n2 ==450)
		 {
			SPWM_TABLE_n2 = 0;
		 }
		 if(SPWM_TABLE_n3 ==450)
		 {
			SPWM_TABLE_n3 = 0;
		 }
   }
}
