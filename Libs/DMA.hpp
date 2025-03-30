#include "stm32f10x.h"
#include "Nvic.hpp"

//enum DMA_Select:			uint8_t {DMA_1,DMA_2};
enum DMA_Priority:			uint8_t {LOW_P,MED_P,HIGH_P,V_HIGH_P};
enum DMA_Transfer_Direction:uint8_t {P_M, 						//Peripheral to Memory
									 M_P,						//Memory to Peripheral
									 M_M};						//Memory to Memory

enum DMA_Periph_Datasize:	uint8_t {P8,						//8 Bit Peripheral Data Size
									 P16,						//16 Bit Peripheral Data Size
									 P32};						//32 Bit Peripheral Data Size

enum DMA_Mem_Datasize:		uint8_t {M8,						//8 Bit Memory Data Size
									 M16,						//16 Bit Memory Data Size
									 M32};						//32 Bit Memory Data Size

enum DMA_Circular:			uint8_t {Disable, Enable};

enum DMA_Interrupt_Types:	uint8_t {Not,
									 Transfer_Complete=2,		//Transfer Complete Interrupt Enable
									 Half_Trasnfer=4,			//Half Transfer Complete Interrupt Enable
									 Transfer_Error=8,			//Transfer Error Interrupt Enable
									 TC_HT=6,					//Transfer Complete and Half Transfer Interrupt Enable
									 TC_TE=10,					//Transfer Complete and Transfer Error Interrupt Enable
									 HT_TE=12,					//Half Transfer and Transfer Error Interrupt Enable
									 ALL=0xE};					//All DMA Interrupts Enable

enum DMA_Peripheral:		uint8_t {ADC_1,
									 SPI_1_RX,
									 SPI_1_TX,
									 SPI_2_RX,
									 SPI_2_TX,
									 USART_3_TX,
									 USART_3_RX,
									 USART_1_TX,
									 USART_1_RX,
									 USART_2_RX,
									 USART_2_TX,
									 I2C_2_TX,
									 I2C_2_RX,
									 I2C_1_TX,
									 I2C_1_RX};

class DMA_Config{
	public:

	DMA_TypeDef *DMAx;
	DMA_Channel_TypeDef *DMA_Channelx;
	IRQn Dma_Irq;

	DMA_Config(DMA_Peripheral dma_periph, uint32_t Periph_Adr, uint32_t Mem_Adr, uint16_t Tranfer_Count, DMA_Transfer_Direction Direction, DMA_Periph_Datasize P_Datasize, DMA_Mem_Datasize M_Datasize, DMA_Priority Priority, DMA_Circular Circular, DMA_Interrupt_Types Interrupt, uint8_t Interrupt_Priorty){

			if(dma_periph == ADC_1){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel1_BASE);
				Dma_Irq = DMA1_Channel1_IRQn;
			}
			else if(dma_periph == SPI_1_RX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel2_BASE);
				Dma_Irq = DMA1_Channel2_IRQn;
			}
			else if(dma_periph == SPI_1_TX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel3_BASE);
				Dma_Irq = DMA1_Channel3_IRQn;
			}
			else if(dma_periph == SPI_2_RX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE);
				Dma_Irq = DMA1_Channel4_IRQn;
			}
			else if(dma_periph == SPI_2_TX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE);
				Dma_Irq = DMA1_Channel5_IRQn;
			}
			else if(dma_periph == USART_3_TX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel2_BASE);
				Dma_Irq = DMA1_Channel2_IRQn;
			}
			else if(dma_periph == USART_3_RX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel3_BASE);
				Dma_Irq = DMA1_Channel3_IRQn;
			}
			else if(dma_periph == USART_1_TX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE);
				Dma_Irq = DMA1_Channel4_IRQn;
			}
			else if(dma_periph == USART_1_RX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE);
				Dma_Irq = DMA1_Channel5_IRQn;
			}
			else if(dma_periph == USART_2_RX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel6_BASE);
				Dma_Irq = DMA1_Channel6_IRQn;
			}
			else if(dma_periph == USART_2_TX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel7_BASE);
				Dma_Irq = DMA1_Channel7_IRQn;
			}
			else if(dma_periph == I2C_2_TX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE);
				Dma_Irq = DMA1_Channel4_IRQn;
			}
			else if(dma_periph == I2C_2_RX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE);
				Dma_Irq = DMA1_Channel5_IRQn;
			}
			else if(dma_periph == I2C_1_TX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel6_BASE);
				Dma_Irq = DMA1_Channel6_IRQn;
			}
			else if(dma_periph == I2C_1_RX){
				DMAx 		 = ((DMA_TypeDef *) DMA1_BASE);
				DMA_Channelx = ((DMA_Channel_TypeDef *) DMA1_Channel7_BASE);
				Dma_Irq = DMA1_Channel7_IRQn;
			}

			if	   (Direction == P_M){DMA_Channelx-> CCR |= 0x00000080;}
			else if(Direction == M_P){DMA_Channelx-> CCR |= 0x00000050;}
			else if(Direction == M_M){DMA_Channelx-> CCR |= 0x00004090;}

			if(Interrupt != 0){
				Set_Interrupt(Dma_Irq,Interrupt_Priorty);
			}

			DMA_Channelx-> CPAR  = Periph_Adr;
			DMA_Channelx-> CMAR  = Mem_Adr;
			DMA_Channelx-> CNDTR = Tranfer_Count;
			DMA_Channelx-> CCR  |= ((Priority<<13)+(M_Datasize<<11)+(P_Datasize<<9)+(Circular<<5)+Interrupt);
		}

	void DMA_ChannelDisabler();
	void DMA_ChannelEnabler();
};
