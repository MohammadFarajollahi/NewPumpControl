/***********************************************************************************************
*	  			  EEPROM I2C
* File name		: I2C_EEPROM 
* Programmer 	: 
* Web presence  :  
* Note			:  
* Language		: 
* Hardware		: 
* Date			:  
************************************************************************************************/ 
//##################################################################################
//##################################################################################
#define I2C_SCL_RCC_ENABLE       __HAL_RCC_GPIOA_CLK_ENABLE()
#define I2C_SCL_PORT GPIOB
#define I2C_SCL_BIT  GPIO_PIN_6

#define I2C_SDA_RCC_ENABLE       __HAL_RCC_GPIOA_CLK_ENABLE()
#define I2C_SDA_PORT GPIOB
#define I2C_SDA_BIT  GPIO_PIN_7

#define SET_SCL      I2C_SCL_PORT->ODR |= I2C_SCL_BIT
#define RESET_SCL      I2C_SCL_PORT->ODR &=~I2C_SCL_BIT

#define SET_SDA      I2C_SDA_PORT->ODR |= I2C_SDA_BIT
#define RESET_SDA      I2C_SDA_PORT->ODR &=~I2C_SDA_BIT

//####################################################################################
