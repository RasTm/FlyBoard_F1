#include "stm32f10x.h"
#include "GPIO.hpp"
#include <vector>

enum adc_num : uint8_t {ADC_1,ADC_2,ADC_3};

class ADC_Base{
	public:
	ADC_TypeDef	*ADCx;
	ADC_Base(adc_num adc, GPIO_TypeDef *GPIO_port, uint8_t Pin){

		if(adc==ADC_1){
			ADCx = ((ADC_TypeDef*) ADC1_BASE);
			RCC-> APB2ENR |= 0x00000200;			//ADC 1 Clock Enable
		}
		else if(adc==ADC_2){
			ADCx = ((ADC_TypeDef*) ADC2_BASE);
			RCC-> APB2ENR |= 0x00000400;			//ADC 2 Clock Enable
		}
		else if(adc==ADC_3){
			if(((GPIO_port == GPIOA) || (GPIO_port == GPIOC)) && ((Pin == 0) || (Pin == 1) || (Pin == 2) || (Pin == 3))){
				ADCx = ((ADC_TypeDef*) ADC3_BASE);
				RCC-> APB2ENR |= 0x00008000;		//ADC 3 Clock Enable
			}
		}
		else if(!((GPIO_port == GPIOA) || (GPIO_port == GPIOB) || (GPIO_port == GPIOC)) && !((Pin == 0) || (Pin == 1) || (Pin == 2) || (Pin == 3) || (Pin == 4) || (Pin == 5) || (Pin == 6) || (Pin == 7))){
			while(1);
		}
		Set_Gpio(GPIO_port,Pin,INPUT,ANALOG,MED,NOT);
		ADCx-> CR2 |= 0x00000001;					//ADC X Enable
	}

	 uint16_t ADC_ScanConv();
	 uint16_t ADC_ScanConv(std::vector<uint16_t> &data);
	 uint16_t ADC_ContinuousConv();
};
