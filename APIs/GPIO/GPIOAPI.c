#ifndef GPIOAPI_C
#define GPIOAPI_C
#include <stm32f407xx.h>
#include "GPIOAPI.h"


void aktdesgpio(int portua, int egoera){
	if((portua >= 0)&&(portua <=10)){
			if(egoera == 0){
				RCC->AHB1ENR &= ~(1<<portua);
			}else{
				RCC->AHB1ENR |= (1<<portua);
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
			gpio->BSRRL |= (1 <<pina); 
		}
	}
}
void piztupinout(int portua, int pina){
		GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <=15)){
			gpio->BSRRH |= (1 <<(pina)); 
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
uint32_t irakurripin(int portua, int pina){
			GPIO_TypeDef *gpio = (GPIO_TypeDef *)((GPIOA_BASE+(portua*0x400)));
			uint32_t erregistroa = gpio->IDR;
	if((portua >= 0)&&(portua <= 10)){
		if((pina >= 0)&&(pina <=	15)){
				erregistroa &= (1<<pina);
				if(erregistroa > 0 ){
						return 1;
				}else{
						return 0;
				}
		}
	}
	return 0;
}


#endif
