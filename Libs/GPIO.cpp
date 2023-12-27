#include "GPIO.hpp"

void Set_Gpio(GPIO_TypeDef *Gpio_Port, uint8_t Pin, uint8_t Mode=OUTPUT, uint8_t Config=PUSH, uint8_t Speed=MED, uint8_t Pupdr=NOT){

	uint8_t gpio_field=0;

		 if(Mode == OUTPUT) {gpio_field = (((Mode-1)<<2)+(Config<<2)+Speed);}
	else if(Mode == ALTER ) {gpio_field = ((Mode<<2)+(Config<<2)+Speed);}
	else if(Mode == INPUT ) {gpio_field = ((Mode<<2)+(Config<<2));}

	else if(Mode == INPUT_R && Pupdr == UP)	{gpio_field = ((Mode-1)<<2); Gpio_Port-> ODR |= (1<<Pin);}
	else if(Mode == INPUT_R)					{gpio_field = (((Mode-1)<<2));}

	if(Pin<8){
		Gpio_Port-> CRL |= (0xF<<(Pin*4));
		Gpio_Port-> CRL ^= (0xF<<(Pin*4));
		Gpio_Port-> CRL |= (gpio_field<<(Pin*4));
	}
	else{
		Gpio_Port-> CRH |= (0xF<<((Pin-8)*4));
		Gpio_Port-> CRH ^= (0xF<<((Pin-8)*4));
		Gpio_Port-> CRH |= (gpio_field<<((Pin-8)*4));
	}
}

void Set_Gpio_Pin(GPIO_TypeDef *Gpio_Port, uint8_t Pin, uint8_t set_reset){

	if(set_reset == 1){
		Gpio_Port-> ODR |= (1<<Pin);
	}
	else if(set_reset == 0){
		Gpio_Port-> ODR &= (0<<Pin);
	}
}

void Set_Ext_Interrupt(uint8_t Exti, uint8_t Gpio_Port, uint8_t r_f){

	AFIO-> EXTICR[Exti/4] |= (Gpio_Port<<(Exti*4));

	EXTI-> IMR |= (1<<Exti);

	if(r_f == RISING){
		EXTI-> RTSR |= (1<<Exti);
	}
	else if(r_f == FALLING){
		EXTI-> FTSR |= (1<<Exti);
	}
	else if(r_f == BOTH){
		EXTI-> RTSR |= (1<<Exti);
		EXTI-> FTSR |= (1<<Exti);
	}
}

void Clr_Ext_Interrupt_PD(uint8_t Exti){

	EXTI-> PR |= (1<<Exti);
}
