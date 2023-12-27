#include "RCC.hpp"

void Clock_init(){
	 RCC-> CR = 0x00000000; 			//CR Reset
	 RCC-> CR |= 0x00010000;			//HSE enable
	 while(!(RCC-> CR & 0x00020000));	//HSE FLAG control
	 RCC-> CR |= 0x00080000;			//CSS enable
	 RCC-> CR |= 0x01000000;			//PLL On
	 RCC-> CFGR |= 0x00010000;			//HSE Select PLL input
	 RCC-> CFGR |= 0x001C0000;			//PLL Multi With 9 = 72 Mhz
	 RCC-> CFGR |= 0x00000002;			//PLL Select as SYSCLK
	 RCC-> CFGR |= 0x00000400;			//APB1 Clock divided by 2

	 RCC-> APB1ENR |= 0x18000000;		//APB1 BKP Clock Enable
	 PWR-> CR |= 0x0100;				//PWR BKP Access Enable

	 RCC-> APB2ENR |= 0x000001FC;		//All GPIO Port Clocks Enable

	 RCC-> APB2ENR |= 0x00000001;		//APB2 AFIO Clock Enable

	 RCC-> APB1ENR |= 0x00000001;		//APB1 TIM2 Clock Enable

	SysTick-> LOAD = 0;
	SysTick-> LOAD = 71999;				//Systick Load is 167,999 (168 Million Pulse each second/ 167,999 pulse = 1 milisecond)

	SysTick-> CTRL|= 0x00000007;		//Systick Clock Source AHB(Processor Clock), SysTick Interrupt Enable, Systick Enable
}
/*
uint32_t Systick_counter =0;

void delay(int count){
	Systick_counter = count;
	while(Systick_counter != 0);
}

extern "C" {void SysTick_Handler(void){
	if(Systick_counter > 0){Systick_counter--;}
}}*/
