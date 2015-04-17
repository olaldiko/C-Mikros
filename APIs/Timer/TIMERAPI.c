#ifndef TIMERAPI_C
#define TIMERAPI_C

#include "TIMERAPI.h"
#include "stm32f4xx.h"

funtzio_helbidea_t funcIrq;

void aktTimer(void){
	RCC->APB1ENR |= (1<<4);
}
void setTime(uint16_t prescaler, uint16_t counter){
	TIM6->PSC = prescaler;
	TIM6->ARR = counter;
}
uint16_t getCounter(void){
	return TIM6->CNT;
}
void setLimitea(uint16_t counter){
	TIM6->ARR = counter;
}
uint16_t isUpdate(void){
	uint16_t update;
	update = TIM6->SR;
	update &= 1;
	if(update == 1){
		TIM6->SR = 0x00;
	}
	return update;
}
void startCounter(void){
	TIM6->CR1 |= 0x01;
}
void stopCounter(void){
	TIM6->CR1 &= ~(0x01);
}
void setUpdateMode(int mode){
	switch(mode){
		case 0:
			TIM6->EGR = 0x00;
		break;
		case 1:
			TIM6->EGR = 0x01;
		break;
	}
}
void setDebugMode(int piztua){
	if(piztua == 1){
		DBGMCU->APB1FZ |= (1<<4);
	}else{
		DBGMCU->APB1FZ &= ~(1<<4);
	}
	
}
void setOnePulse(int mode){
	if(mode == 1){
		TIM6->CR1 |= (1<<2);
	}else{
		TIM6->CR1 &= ~(1<<2);
	}	
}
void setUpdateIRQ(int mode){
	if(mode == 1){
		TIM6->DIER |=0x01;
	}else{
		TIM6->DIER &= ~(0x01);
	}
}
void setInterruptSource(int mode){
	if(mode == 1){
		TIM6->CR1 |= (1<<2);
	}else{
		TIM6->CR1 &= ~(1<<2);
	}
}
void clearInterrupt(void){
	TIM6->SR = 0x0;
}
void TIM6_DAC_IRQHandler(void){
	funcIrq();
	TIM6->SR = 0x0;
	NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
}
void ezarriIRQFunc(funtzio_helbidea_t func){
	funcIrq = func;
}
void initIRQ_TIM6(void){
	setInterruptSource(1);
	setUpdateIRQ(1);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
}
#endif

