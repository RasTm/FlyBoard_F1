#include "ADC.hpp"

uint16_t ADC_Base::ADC_ScanConv(){
//	ADCx-> CR1 |= 0x00000100;		//Scan Mode Enable
	ADCx-> SQR2|= 0x00000000;
	ADCx-> SQR1|= 0x00100000;
	ADCx-> SQR3|= 0x00000001;
	ADCx-> CR2 |= 0x000E0000;
	ADCx-> CR2 |= 0x40000000;		//Regular conv start
	return ADCx-> DR;
}

uint16_t ADC_Base::ADC_ScanConv(std::vector<uint16_t> &data){
	ADCx-> CR1 |= 0x40000002;		//Regular conv start, Continuous mode enable

	return ADCx-> DR;
}
/*
uint16_t ADC_Base::ADC_ContinuousConv(){

}*/
