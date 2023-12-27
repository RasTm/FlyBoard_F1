#include "USART.hpp"

template <typename T> void USART_Base::USART_Transmit(std::vector<T> &data){

	uint8_t data_size = sizeof(data[0]);

	USARTx-> CR1  = 0;							//Reset USART CR1 Register
	USARTx-> CR1 |= 0x00002008;					//USART Enable TX Mode Set

	if(data_size == 1){
		for(T Usart_data : data){
			while(!(USARTx-> SR & 0x0000080));	//Check TXE bit
			USARTx-> DR = Usart_data;
		}
	}
	else if(data_size == 2){
		for(T Usart_data : data){
			while(!(USARTx-> SR & 0x00000080)); //Check TXE bit
			USARTx-> DR = (Usart_data & 0x00FF);
			while(!(USARTx-> SR & 0x00000080)); //Check TXE bit
			USARTx-> DR = (Usart_data & 0xFF00);
		}
	}
	else if(data_size == 4){
		for(T Usart_data : data){
			while(!(USARTx-> SR & 0x00000080)); //Check TXE bit
			USARTx-> DR = (Usart_data & 0x000000FF);
			while(!(USARTx-> SR & 0x00000080)); //Check TXE bit
			USARTx-> DR = (Usart_data & 0x0000FF00);
			while(!(USARTx-> SR & 0x00000080)); //Check TXE bit
			USARTx-> DR = (Usart_data & 0x00FF0000);
			while(!(USARTx-> SR & 0x00000080)); //Check TXE bit
			USARTx-> DR = (Usart_data & 0xFF000000);
		}
	}

	while(!(USARTx-> SR & 0x000000040));	//Wait Until Transmission Complete Bit Set
	USARTx-> CR1 &= 0xFFFFFFF7; 			//USART Disable TX Mode Clear
}

void USART_Base::USART_Transmit(uint8_t *data, uint8_t size){
	USARTx-> CR1  = 0;						//Reset USART CR1 Register
	USARTx-> CR1 |= 0x00002008;				//USART Enable TX Mode Set

	for(uint8_t i=0; i<size; i++){
		while(!(USARTx-> SR & 0x0000080));	//Check TXE bit
		USARTx-> DR = (uint8_t)data[i];
	}

	while(!(USARTx-> SR & 0x000000040));	//Wait Until Transmission Complete Bit Set
	USARTx-> CR1 &= 0xFFFFFFF7; 			//USART Disable TX Mode Clear

}

void USART_Base::USART_Receive(std::vector<uint8_t> data){
	USARTx-> CR1  = 0;						//Reset USART CR1 Register
	USARTx-> CR1 |= 0x00002004;				//USART Enable RX Mode Set

	while(!(USARTx-> SR & 0x00000020)){		//Check RXNE bit
		if(USARTx->DR == '\0' && USARTx-> DR & 0x00000020){
			break;
		}
		data.push_back(USARTx-> DR);
	}

	USARTx-> CR1 &= 0xFFFFFFFB;				//USART Disable RX Mode Clear
}

void USART_Base::USART_Receive(uint8_t *data, uint8_t size){
	USARTx-> CR1  = 0;						//Reset USART CR1 Register
	USARTx-> CR1 |= 0x00002004;				//USART Enable RX Mode Set

	for(uint8_t i=0; i<size; i++){
		while(!(USARTx-> SR & 0x00000020));	//Check RXNE bit
		data[i] = USARTx->DR;
	}

	USARTx-> CR1 &= 0xFFFFFFFB;				//USART Disable RX Mode Clear
}
