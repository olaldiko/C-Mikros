#include "TIMERAPI.h"
#include "GPIOAPI.h"
#define PORTLED 5
#define LED 7
int main(void){
	int egoera = 0;
	int i = 0;
	aktdesgpio(PORTLED, 1);
	setpinmode(PORTLED, LED, 2);
	itzalipinout(PORTLED, LED);
	aktTimer();
	setDebugMode(1);
	setTime(16000, 1000);
	setUpdateMode(1);
	startCounter();
	while(0 == 0){
		if(isUpdate() == 1){
			if(egoera == 0){
				aktdesgpioout(PORTLED, LED, 1);
				egoera = 1;
			}else{
				aktdesgpioout(PORTLED, LED, 0);
				egoera = 0;
			}
		}
	}
}

