#ifndef GPIOAPI_C
#define GPIOAPI_C
#include <stm32f407xx.h>
#include "GPIOAPI.h"


void aktdesgpio(int portua, int egoera){
		RCC_TypeDef *rcc = RCC;
	if((portua >= 0)&&(portua <=10)){
			if(egoera == 0){
				rcc->AHB1ENR &= ~(1<<portua);
			}else{
				rcc->AHB1ENR |= (1<<portua);
			}				
	}
}
void aktdesgpioout(int portua, int pina, int egoera){
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <=15)){
			if(egoera == 0){
				gpio->ODR &= ~(1<<pina);
			}else{
				gpio->ODR |= (1<<pina);
			}
		}
	}
}
void itzalipinout(int portua, int pina){
		GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <=15)){
			gpio->BSRRH |= (1 <<pina); 
		}
	}
}
void piztupinout(int portua, int pina){
		GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <=15)){
			gpio->BSRRL |= (1 <<(pina)); 
		}
	}
}
void aldatupinout(int portua, int pina){
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <=15)){
			gpio->ODR ^=(1<<pina);
		}
	}
}

void setpinmode(int portua, int pina, int modua){
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <=	15)){
		switch(modua){
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
void setResistorMode(int portua, int pina, int modua){
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <= 15)){
		switch(modua){
			case 1: //00 Ezer
				gpio->PUPDR &=~(3<<(pina*2));
				break;
			case 2: //01 pull-up
				gpio->PUPDR |= (1<<(pina*2));
				gpio->PUPDR &= ~(2<<(pina*2));
				break;
			case 3: //10 pull-down
				gpio->PUPDR |= (2<<(pina*2));
				gpio->PUPDR &= ~(1<<(pina*2));
				break;
			}
		}
	}
}
uint32_t irakurripin(int portua, int pina){
			GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
			//uint32_t erregistroa = gpio->IDR;
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <= 15)){
				if((gpio->IDR & (1<<pina)) > 0 ){
						return 1;
				}else{
						return 0;
				}
		}
	}
	return 0;
}
void setOutputMode(uint8_t port, uint8_t pin, uint8_t mode){
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(port*0x400)));
	if((port >= 0)&&(port <= 10)){
		if((pin >= 0)&&(pin <= 15)){
			switch(mode){
				case 0: gpio->OTYPER &= ~(1<<pin); break;
				case 1: gpio->OTYPER |= (1<<pin); break;
			}
		}
	}
}

#endif
