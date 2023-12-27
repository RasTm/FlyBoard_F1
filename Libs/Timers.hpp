#include "stm32f10x.h"
#include <bitset>

#define TIM_1  1
#define TIM_2  2
#define TIM_3  3
#define TIM_4  4
#define TIM_5  5
#define TIM_6  6
#define TIM_7  7
#define TIM_8  8
#define TIM_9  9
#define TIM_10 10
#define TIM_11 11
#define TIM_12 12
#define TIM_13 13
#define TIM_14 14

#define FROZEN 	   0
#define SET_HIGH   1
#define SET_LOW    2
#define TOGGLE     3
#define FORCE_LOW  4
#define FORCE_HIGH 5
#define PWM_1 	   6
#define PWM_2 	   7

class Timer_Base{
	private:
	uint8_t MOE_Status;
	uint8_t Timer;
	public:
	TIM_TypeDef *Timerx;

	Timer_Base(uint8_t const TimerXn, uint32_t Prescaler_Value, uint32_t ARR_Value){
		Timer = TimerXn;
		switch (TimerXn){
		 case TIM_1:
			 Timerx = ((TIM_TypeDef *) TIM1_BASE);
			 RCC-> APB2ENR |= 0x00000800;
			 break;
		 case TIM_2:
			 Timerx = ((TIM_TypeDef *) TIM2_BASE);
			 RCC-> APB1ENR |= 0x00000001;
		 	 break;
		 case TIM_3:
			 Timerx = ((TIM_TypeDef *) TIM3_BASE);
			 RCC-> APB1ENR |= 0x00000002;
			 break;
		 case TIM_4:
			 Timerx = ((TIM_TypeDef *) TIM4_BASE);
			 RCC-> APB1ENR |= 0x00000004;
			 break;
		 case TIM_5:
			 Timerx = ((TIM_TypeDef *) TIM5_BASE);
			 RCC-> APB1ENR |= 0x00000008;
			 break;
		 case TIM_6:
			 Timerx = ((TIM_TypeDef *) TIM6_BASE);
			 RCC-> APB1ENR |= 0x00000010;
			 break;
		 case TIM_7:
			 Timerx = ((TIM_TypeDef *) TIM7_BASE);
			 RCC-> APB1ENR |= 0x00000020;
			 break;
		 case TIM_8:
			 Timerx = ((TIM_TypeDef *) TIM8_BASE);
			 RCC-> APB2ENR |= 0x00002000;
			 break;
		 case TIM_9:
			 Timerx = ((TIM_TypeDef *) TIM9_BASE);
			 RCC-> APB2ENR |= 0x00080000;
			 break;
		 case TIM_10:
			 Timerx = ((TIM_TypeDef *) TIM10_BASE);
			 RCC-> APB2ENR |= 0x00100000;
			 break;
		 case TIM_11:
			 Timerx = ((TIM_TypeDef *) TIM11_BASE);
			 RCC-> APB2ENR |= 0x00200000;
			 break;
		 case TIM_12:
			 Timerx = ((TIM_TypeDef *) TIM12_BASE);
			 RCC-> APB1ENR |= 0x00000040;
			 break;
		 case TIM_13:
			 Timerx = ((TIM_TypeDef *) TIM13_BASE);
			 RCC-> APB1ENR |= 0x00000080;
			 break;
		 case TIM_14:
			 Timerx = ((TIM_TypeDef *) TIM14_BASE);
			 RCC-> APB1ENR |= 0x00000100;
			 break;
		 default:
			 while(1);
		}

		Timerx-> ARR = ARR_Value;
		Timerx-> PSC = Prescaler_Value;
	}
	void Counter_Start();
	void PWM(uint8_t CH, uint8_t Pwm_mode);
	void Pulse_Generator(uint32_t ARR_Val);
};

void delay(int count);
