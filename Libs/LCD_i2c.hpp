#include "Timers.hpp"
#include "I2C.hpp"

#define LCD_ADDR 0x4E

class lcd : public I2C_Base{
	public:
	lcd(I2C_TypeDef* I2Cxn):I2C_Base(I2Cxn, STANDART){}

	void lcd_init();
	void lcd_send_cmd(char cmd);
	void lcd_send_data(char data);
	void lcd_clear();
	void lcd_put_cur(uint8_t row, uint8_t col);
	void lcd_send_string(char *str);
};
