#include <stdint.h>
#include "stm32f4xx.h"
#include "TIMERAPI.h"
#include "GPIOAPI.h"
#define PORTLED 5
#define LED 8
#define PORTJOY 6
#define JOYGORA 6
#define JOYBEHERA 7
#define PERIOD 10000

uint16_t cnton = 0x00F0;
uint16_t cntoff = 0xFDE8;
float pot = 0.2;
uint16_t ledstat = 0;

void initGPIO(void);
void initTimer(void);
void initIRQ(void);
void TIM6_DAC_IRQHandler(void);
__irq void treatIRQ(void);

int main(void){
	initGPIO();
	initTimer();
	initIRQ();
	while(1){
		
	}
}

void initGPIO(void){
	aktdesgpio(PORTLED, 1);
	aktdesgpio(PORTJOY, 1);
	setpinmode(PORTLED,LED, 2); 
	setpinmode(PORTJOY, JOYGORA, 1);
	setpinmode(PORTJOY, JOYBEHERA, 1);
}
void initTimer(void){
	aktTimer();
	setDebugMode(1);
	setTime(1000, cnton);
	setUpdateMode(1);
	setOnePulse(1);
	setInterruptSource(1);
	setUpdateIRQ(1);
	
}
void initIRQ(void){
	EXTI_TypeDef *exti = EXTI;
	
	exti->EMR |= (1<<JOYGORA);
	exti->EMR |= (1<<JOYBEHERA);
	
	exti->FTSR |= (1<<JOYGORA);
	exti->FTSR |= (1<<JOYBEHERA);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void EXTI9_5_IRQHandler(void){
	EXTI_TypeDef *exti = EXTI;
	if(irakurripin(PORTJOY, JOYGORA) == 1){
		if(pot<1.0){
			pot += 0.20;
			cnton = pot * PERIOD;
			cntoff = PERIOD - cnton;
		}
	}else{
		if(irakurripin(PORTJOY, JOYBEHERA) == 1){
			if(pot > 0.0){
				pot -= 0.05;
				cnton = pot * PERIOD;
				cntoff = PERIOD - cnton;
			}
		}
	}
	NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
}

void TIM6_DAC_IRQHandler(void){
	if(ledstat == 0){
			ledstat = 1;
			setTime(65000, cnton);
			aktdesgpioout(PORTLED, LED, 1);
			startCounter();
			NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
	}else{
			ledstat = 0;
			setTime(65000, cntoff);
			aktdesgpioout(PORTLED, LED, 0);
			startCounter();
			NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
	}
}
