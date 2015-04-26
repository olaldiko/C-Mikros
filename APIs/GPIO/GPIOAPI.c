#ifndef GPIOAPI_C
#define GPIOAPI_C
#include <stm32f407xx.h>
#include "GPIOAPI.h"

/**
*Enables or disables the corresponding GPIO port.
* @param portua The corresponding gpio port. 0-9
* @param egoera 0 Disabled, 1 Enabled
*/
void aktdesgpio(int portua, int egoera) {
	if((portua >= 0)&&(portua <=10)) {
			if(egoera == 0) { 
				RCC->AHB1ENR &= ~(1<<portua);
			} else {
				RCC->AHB1ENR |= (1<<portua);
			}				
	}
}
/**
*Puts the corresponding output pin in High or low states.
* @param portua The corresponding GPIO port. 0-9
* @param pina The corresponding pin. 0-15
* @param egoera 0 Low output, 1 High output.
*/
void aktdesgpioout(int portua, int pina, int egoera) {
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400))); /**<The base address + the corresponding port * the offset*/
	if((portua >= 0)&&(portua <= 10)) {
		if((pina >= 0)&&(pina <=15)) {
			if(egoera == 0) {
				gpio->ODR &= ~(1<<pina);
			} else {
				gpio->ODR |= (1<<pina);
			}
		}
	}
}
/**
*Puts the corresponding output pin in LOW state.
* @param portua The corresponding GPIO port. 0-9
* @param pina The corresponding pin. 0-15
*/
void itzalipinout(int portua, int pina) {
		GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)) {
		if((pina >= 0)&&(pina <=15)) {
			gpio->BSRRL |= (1 <<pina); 
		}
	}
}
/**
*Puts the corresponding output pin in HIGH state.
* @param portua The corresponding GPIO port. 0-9
* @param pina The corresponding pin. 0-15
*/
void piztupinout(int portua, int pina) {
		GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)) {
		if((pina >= 0)&&(pina <=15)) {
			gpio->BSRRH |= (1 <<(pina)); 
		}
	}
}
/**
*Changes the output state of the output pin. From LOW to HIGH and from HIGH to LOW.
* @param portua The corresponding GPIO port. 0-9
* @param pina The corresponding pin. 0-15
*/
void aldatupinout(int portua, int pina) {
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)) {
		if((pina >= 0)&&(pina <=15)) {
			gpio->ODR ^=(1<<pina);
		}
	}
}
/**
*Changes the pin mode of the GPIO.
* @param portua The corresponding GPIO port. 0-9
* @param pina The corresponding pin. 0-15
* @param modua The mode of the pin. 1-4
* 1->Pin in Digital input mode.
* 2->Pin in Digital output mode.
* 3->Pin in Alternate function mode.
* 4->Pin in Analog input mode.
*/
void setpinmode(int portua, int pina, int modua) {
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)) {
		if((pina >= 0)&&(pina <=	15)) {
		switch(modua) {
			case 1:
				//Sarrera
				gpio->MODER &=~(3<<(pina*2));
				break;
			case 2:
				//Irteera digitala
				gpio->MODER |= (1<<(pina*2));
				gpio->MODER &=~(2<<(pina*2));
				break;
			case 3:
				//Alternate
				gpio->MODER &=~(1<<(pina*2));	
				gpio->MODER |= (2<<(pina*2));
				break;
			case 4:
				//Analogikoa
				gpio->MODER |= (3<<(pina*2));
				break;
			}
		}
	}
}
/**
*Changes the mode for the pull-up and pull-down resistors of the input pin.
* @param portua The corresponding GPIO port. 0-9
* @param pina The corresponding pin. 0-15
* @param modua The mode of the pin. 1-3
* Mode 1-> No pull-up or pull-down resistors enabled.
* Mode 2-> Pull-up resistor enabled.
* Mode 3-> Pull-down resistor enabled.
*/
void setResistorMode(int portua, int pina, int modua) {
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)) {
		if((pina >= 0)&&(pina <= 15)) {
		switch(modua) {
			case 1: //00
				gpio->PUPDR &=~(3<<(pina*2));
				break;
			case 2: //01
				gpio->PUPDR |= (1<<(pina*2));
				gpio->PUPDR &= ~(2<<(pina*2));
				break;
			case 3: //10
				gpio->PUPDR |= (2<<(pina*2));
				gpio->PUPDR &= ~(1<<(pina*2));
				break;
			}
		}
	}
}
/**
* Reads the state of the input pin.
* @param portua The corresponding GPIO port. 0-9
* @param pina The corresponding pin. 0-15
* @return The state of the pin. 0-Low, 1-High.
*/
uint32_t irakurripin(int portua, int pina) {
			GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
			uint32_t erregistroa = gpio->IDR;
	if((portua >= 0)&&(portua <= 10)) {
		if((pina >= 0)&&(pina <=	15)) {
				erregistroa &= (1<<pina);
				if(erregistroa > 0 ) {
						return 1;
				} else {
						return 0;
				}
		}
	}
	return 0;
}


#endif
