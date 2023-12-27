#include "stm32f10x.h"

#define INPUT 0				//
#define OUTPUT 1			//Mode Byte
#define ALTER 2				//
#define INPUT_R 3			//

#define PUSH 0				//
#define DRAIN 1				//Config Byte
#define ANALOG 0			//
#define FLOATING 1			//

#define LOW 2				//
#define MED 1				//Speed Byte
#define HIGH 3				//

#define NOT 0				//
#define DOWN 0				//Pupdr Byte
#define UP 1				//

#define RISING 0			//
#define FALLING 1			//r_f Byte
#define BOTH 2				//

#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6

void Set_Gpio(GPIO_TypeDef *Gpio_Port, uint8_t Pin, uint8_t Mode, uint8_t Config, uint8_t Speed, uint8_t Pupdr);

void Set_Gpio_Pin(GPIO_TypeDef *Gpio_Port, uint8_t Pin, uint8_t set_reset);

void Set_Ext_Interrupt(uint8_t Exti, uint8_t Gpio_Port, uint8_t r_f);

void Clr_Ext_Interrupt_PD(uint8_t Exti);
