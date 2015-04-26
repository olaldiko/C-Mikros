#include <stdint.h>
#include "stm32f4xx.h"
#include "TIMERAPI.h"
#include "GPIOAPI.h"
#define PORTLED 5
#define PORTBUZ 1
#define BUZ 1
#define LED4 9
#define LED3 8
#define LED2 7
#define LED1 6
#define PORTJOY 6
#define JOYGORA 8
#define JOYBEHERA 7
#define PERIOD 100
#define PRESC 0
#define SYSCFG_RCC 14


uint16_t cnton = 1000;
uint16_t cntoff = 29000;
uint16_t pot = 10;
volatile uint16_t ledstat = 0;

void initGPIO(void);
void initTimer(void);
void initIRQ(void);
void EXTI9_5_IRQHandler(void);
void timerInterrupzioa(void);
int main(void){
	int i = 0;
	initGPIO();
	initTimer();
	initIRQ();
	
	while(1){
		if(irakurripin(PORTJOY, JOYGORA) && (pot < 95) && (i==0)){
			i=1;
			pot += 5;
			cnton = pot * PERIOD;
			cntoff = PERIOD*(100-pot);
		}else{
			if(irakurripin(PORTJOY, JOYBEHERA)&& (pot > 5) && (i==0)){
				i=1;	
				pot -= 5;
				cnton = pot * PERIOD;
				cntoff = PERIOD*(100-pot);
			}
		}
		if((irakurripin(PORTJOY, JOYGORA) == 0)&&(irakurripin(PORTJOY, JOYBEHERA) == 0)){
			i=0;
		}
	}
}
/** 
*GPIO init function. Initializes all the needed gpio ports and configures the pins.
*
*/
void initGPIO(void){
	aktdesgpio(PORTLED, 1);
	aktdesgpio(PORTBUZ, 1);
	aktdesgpio(PORTJOY, 1);
	setpinmode(PORTLED,LED1, 2); 
	setpinmode(PORTLED,LED2, 2);
	setpinmode(PORTLED,LED3, 2);
 	setpinmode(PORTLED,LED4, 2); 
	setpinmode(PORTJOY, JOYGORA, 1);
	setpinmode(PORTJOY, JOYBEHERA, 1);
	setpinmode(PORTBUZ, BUZ, 2);
}

/** 
*Timer init function. Activates the timer and sets all the needed configuration bits.
*/
void initTimer(void){
	aktTimer();
	setDebugMode(1);
	setTime(PRESC, cnton);
	setUpdateMode(1);
	setOnePulse(1);
	setInterruptSource(1);
	
}
/**
*IRQ Initialization function. Initializes the EXTIand configures it, configures the SYSCFG
*for choosing the ports that generate an event or interrupt 
*and sets the function to call when an interrupt occurs.
*For now the GPIO interrupt setup is disabled.
*/
void initIRQ(void){
	RCC_TypeDef *rcc = RCC;
	EXTI_TypeDef *exti = EXTI;
	SYSCFG_TypeDef *syscfg = SYSCFG;
	//rcc->APB2ENR |= (1<<SYSCFG_RCC);
	//Aukeratu G portua exti-an
	//syscfg->EXTICR[2] |= (6<<12);
	//syscfg->EXTICR[3] |= 0x06;
	//Aktibatu honen interrupzioak
	//exti->IMR |= (1<<JOYGORA);
	//exti->IMR |= (1<<JOYBEHERA);
	//Falling edgean aktibatzeko ezarri
	//exti->FTSR |= (1<<JOYGORA);
	//exti->FTSR |= (1<<JOYBEHERA);
	//exti->RTSR |= (1<<JOYGORA);
	//exti->RTSR |= (1<<JOYBEHERA);
	//NVICean aktibatu interrupzioak
	//NVIC_EnableIRQ(EXTI9_5_IRQn);
	ezarriIRQFunc(timerInterrupzioa);
	initIRQ_TIM6();
}
/**
*The GPIO interrumpt function. This function is called when an interruption occurs in the EXTI 5 to 9 ports.
*/
void EXTI9_5_IRQHandler(void){
	EXTI_TypeDef *exti = EXTI;
	if(irakurripin(PORTJOY, JOYGORA) == 1){
		if(pot<1.0){
			pot += 0.05;
			cnton = pot * PERIOD;
			cntoff = PERIOD - cnton;
			exti->PR |= (1<<JOYGORA);
		}
	}else{
		if(irakurripin(PORTJOY, JOYBEHERA) == 1){
			if(pot > 0.0){
				pot -= 0.05;
				cnton = pot * PERIOD;
				cntoff = PERIOD - cnton;
				exti->PR |= (1<<JOYBEHERA);
			}
		}
	}
	
	NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
}
/**
*The function that will be called when a timer interrumpt occurs.
*It will set the on or off time for the led and will also start the counter again.
*/
void timerInterrupzioa(void){
	if(ledstat == 0){
			ledstat = 1;
			setTime(PRESC, cnton);
			aktdesgpioout(PORTLED, LED1, 1);
			aktdesgpioout(PORTLED, LED2, 1);
			aktdesgpioout(PORTLED, LED3, 1);
			aktdesgpioout(PORTLED, LED4, 1);
		//	aktdesgpioout(PORTBUZ, BUZ, 1);
	}else{
			ledstat = 0;
			setTime(PRESC, cntoff);
			aktdesgpioout(PORTLED, LED1, 0);
			aktdesgpioout(PORTLED, LED2, 0);
			aktdesgpioout(PORTLED, LED3, 0);
			aktdesgpioout(PORTLED, LED4, 0);
			//aktdesgpioout(PORTBUZ, BUZ, 0);
	}
	startCounter();
}
