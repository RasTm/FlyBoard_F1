#include "stm32f10x.h"

#include "../Libs/RCC.hpp"
#include "../Libs/GPIO.hpp"
#include "../Libs/Nvic.hpp"
#include "../Libs/Timers.hpp"

#define PRE_SC 180-1			//PRE_Scaler / 72 = x uS tick
#define AUTO_R 2000-1

void Gpio_init(){
	Set_Gpio(GPIOA,8,ALTER,PUSH,MED,NOT);	//PWM ��k��� konfigurasyonu

	Set_Gpio(GPIOA,0,INPUT_R,PUSH,LOW,UP);	//PA0 pini giri� pull up konfigurasyonu
	Set_Gpio(GPIOB,1,INPUT_R,PUSH,LOW,UP);	//PB1 pini giri� pull up konfigurasyonu
}

void Interrupt_init(){
	Set_Interrupt(EXTI0_IRQn,1);			//EXTI 0 Hatt� konfigurasyonu
	Set_Interrupt(EXTI1_IRQn,2);			//EXTI 1 Hatt� konfigurasyonu
	Set_Ext_Interrupt(0,GPIO_A,FALLING);	//EXTI 0 Hatt� Dusen kenaer konfigurasyonu
	Set_Ext_Interrupt(1,GPIO_B,FALLING);	//EXTI 1 Hatt� Dusen kenaer konfigurasyonu
}

uint8_t pwm_val=0;							//Global de�i�ken

int main(void){

	Clock_init();
	Gpio_init();
	Interrupt_init();

	Timer_Base output(TIM_1,PRE_SC,AUTO_R);	//Timer 1 konfigurasyonu ve output isimli objesi
	output.Timerx->CCR1 = 0;				//Capture Compare yazmac� ba�lang�� de�er atams�
	output.PWM(1,PWM_1);					//output objesi i�in PWM ��k�� ayarlamas�

	while (1){
		output.Timerx->CCR1 = pwm_val*200;	//Sonsuz d�ng� i�inde capture compare yazmac� g�ncellemesi
	}
}

extern "C" {void EXTI0_IRQHandler(void){	//EXTI 0 hatt� i�in interrupt fonksiyonu
	if(pwm_val < 10){
		pwm_val += 1;
	}
	Clr_Ext_Interrupt_PD(0);
	Clr_Interrupt_PD(EXTI0_IRQn);
}}

extern "C" {void EXTI1_IRQHandler(void){	//EXTI 1 hatt� i�in interrupt fonksiyonu
	if(pwm_val > 0){
		pwm_val -= 1;
	}
	Clr_Ext_Interrupt_PD(1);
	Clr_Interrupt_PD(EXTI1_IRQn);
}}
