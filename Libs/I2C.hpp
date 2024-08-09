#include "stm32f10x.h"
#include "GPIO.hpp"
#include <vector>

#define STANDART 0
#define FAST 1

class I2C_Base{
	private:
	uint8_t own_i2c_addr = 0;
	uint16_t trash;

	public:
	I2C_TypeDef *I2Cx;
	I2C_Base(I2C_TypeDef *I2Cxn, uint8_t i2c_mode = STANDART){
		if(I2Cxn == I2C1){
			RCC-> APB1ENR |= 0x00200000;
			I2Cx = ((I2C_TypeDef *) I2C1_BASE);
			Set_Gpio(GPIOB, 6, ALTER, DRAIN, MED, UP);
			Set_Gpio(GPIOB, 7, ALTER, DRAIN, MED, UP);
		}
		else if(I2Cxn == I2C2){
			RCC-> APB1ENR |= 0x00400000;
			I2Cx = ((I2C_TypeDef *) I2C2_BASE);
			Set_Gpio(GPIOB, 10, ALTER, DRAIN, MED, UP);
			Set_Gpio(GPIOB, 11, ALTER, DRAIN, MED, UP);
		}
		else while(1);

		I2Cx-> CR2 |= 36;			//Sonra düzeltilecek APB1_CLK yazılacak
		I2Cx-> OAR1|= own_i2c_addr;

		switch(i2c_mode){
			case STANDART:
				I2Cx-> CCR   |= 0x001E;
				I2Cx-> TRISE |= 0x0022;
				break;
			case FAST:
				I2Cx-> CCR   |= 0x8000;
				break;
			default:
				while(1);
		}

	}
	void write_byte(uint8_t dev_addr, uint8_t dev_reg_addr, uint8_t data);
	void multi_byte_write(uint8_t dev_addr, uint8_t dev_reg_addr, std::vector<uint8_t> &data);

	void read_byte(uint8_t dev_addr, uint8_t dev_reg_addr, uint8_t *data);
	void multi_byte_read(uint8_t dev_addr, uint8_t dev_reg_addr, std::vector<uint8_t> &data, uint8_t byte_count);

	void write_byte_small(uint8_t dev_addr, uint8_t data);
	void multi_byte_write_small(uint8_t dev_addr, uint8_t *data, uint8_t byte_count);

	void read_byte_small(uint8_t dev_addr, uint8_t *data);
	void multi_byte_read_small(uint8_t dev_addr, uint8_t *data, uint8_t byte_count);

	void multi_byte_read_extend(uint8_t dev_addr, uint16_t dev_reg_addr, uint8_t *data, uint8_t byte_count);
};
