#include "Nvic.hpp"

void Set_Interrupt(IRQn Int_Num, uint8_t Prior){

	NVIC-> ISER[Int_Num/32] |= (1<<(Int_Num%32));

	NVIC-> IP[Int_Num] = Prior;
}

void Clr_Interrupt(IRQn Int_Num){

	NVIC-> ICER[Int_Num/32] |= (1<<(Int_Num%32));
}

void Clr_Interrupt_PD(IRQn Int_Num){

	NVIC-> ICPR[Int_Num/32] |= (1<<(Int_Num%32));
}
