#ifndef TIMERAPI_C
#define TIMERAPI_C
#include "TIMERAPI.h"

void aktTimer(){
	RCC_TypeDef *rcc = RCC;
	RCC->APB1ENR |= (1<<4);
}
void setTime(uint16_t prescaler, uint16_t counter){
	TIM_TypeDef *timer = TIM6;
	timer->PSC = prescaler;
	timer->ARR = counter;
}
uint16_t getCounter(){
	TIM_TypeDef *timer = TIM6;
	return timer->CNT;
}
void setLimitea(uint16_t counter){
	TIM_TypeDef *timer = TIM6;
	timer->ARR = counter;
}
uint16_t isUpdate(){
	uint16_t update;
	TIM_TypeDef *timer = TIM6;
	update = timer->SR;
	update &= 1;
	if(update == 1){
		timer->SR = 0x00;
	}
	return update;
}
void startCounter(){
	TIM_TypeDef *timer = TIM6;
	timer->CR1 |= 0x01;
}
void stopCounter(){
	TIM_TypeDef *timer = TIM6;
	timer->CR1 &= ~(0x01);
}
void setUpdateMode(int mode){
	TIM_TypeDef *timer = TIM6;
	switch(mode){
		case 0:
			timer->EGR = 0x00;
		break;
		case 1:
			timer->EGR = 0x01;
		break;
	}
}
void setDebugMode(int piztua){
	DBGMCU_TypeDef *debugreg = DBGMCU;
	if(piztua == 1){
		debugreg->APB1FZ |= (1<<4);
	}else{
		debugreg->APB1FZ &= ~(1<<4);
	}
	
}
void setOnePulse(int mode){
	TIM_TypeDef *timer = TIM6;
	if(mode == 1){
		timer->CR1 |= (1<<2);
	}else{
		timer->CR1 &= ~(1<<2);
	}	
}
void setUpdateIRQ(int mode){
	TIM_TypeDef *timer = TIM6;
	if(mode == 1){
		timer->DIER |=0x01;
	}else{
		timer->DIER &= ~(0x01);
	}
}
void setInterruptSource(int mode){
	TIM_TypeDef *timer = TIM6;
	if(mode == 1){
		timer->CR1 |= (1<<2);
	}else{
		timer->CR1 &= ~(1<<2);
	}
}

#endif

