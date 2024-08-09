#include "Timers.hpp"

uint32_t Systick_counter=0;

void Timer_Base::Counter_Start(){
	Timerx-> CR1 |= 0x0001;
}

void Timer_Base::PWM(uint8_t CH, uint8_t Pwm_mode){

	if(Timer < 6 || Timer == 8){
		if(CH > 15){ while(1);}
	}
	else if(Timer == 6 || Timer == 7) while(1);
	else if(Timer == 9 || Timer == 12){
		if(CH > 2){  while(1);}
	}
	else if(Timer == 10 || Timer == 11 || Timer == 13 || Timer == 14){
		if(CH > 1){  while(1);}
	}

	std::bitset<4> channel (CH);

    for(uint8_t i=0;i<4;i++){
        if(channel[i] == 1 && i<2){
            Timerx-> CCMR1 |= ((((Pwm_mode)<<4)+(0x8))<<(8*i));
            Timerx-> CCER  |= (1<<(i*4));
        }
        else if(channel[i] == 1 && i>1){
        	Timerx-> CCMR2 |= ((((Pwm_mode)<<4)+(0x8))<<(8*(i-2)));
            Timerx-> CCER  |= (1<<(i*4));
        }
    }

    if(Timer == 8 || Timer == 1){
    	Timerx-> BDTR |= 0xA000;		//Main Output Enable (MOE) and Break Polarity Active High
    }

	Timerx -> CR1   |= 0x0080;			//Auto Reload Preload (ARPE) Enable

	Counter_Start();
}

void Timer_Base::Pulse_Generator(uint32_t ARR_Val){

}

void delay(int count){
	Systick_counter = count;
	while(Systick_counter != 0);
}

extern "C" {void SysTick_Handler(void){
	if(Systick_counter > 0){Systick_counter--;}
}}
