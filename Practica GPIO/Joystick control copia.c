	#include "GPIOAPI.H"
	#include <stm32f4xx.h>
	#define PORTLED 5
	#define PORTJOY 6
	#define LED1 5
	#define LED2 6
	#define LED3 7
	#define LED4 8
	#define JOYGORA 6
	#define JOYBEHERA 7
	#define JOYESKUIN 5
	#define JOYEZKER 10
	#define JOYCENT 14
int main(void){
	aktdesgpio(PORTLED, 1);
	aktdesgpio(PORTJOY, 1);
	setpinmode(PORTLED, LED1, 2);
	setpinmode(PORTLED, LED2, 2);
	setpinmode(PORTLED, LED3, 2);
	setpinmode(PORTLED, LED4, 2);
	setpinmode(PORTJOY, JOYGORA, 1);
	setpinmode(PORTJOY, JOYBEHERA, 1);
	setpinmode(PORTJOY, JOYESKUIN, 1);
	setpinmode(PORTJOY, JOYEZKER, 1);
	setpinmode(PORTJOY, JOYCENT, 1);
	while(0 == 0){
		if(irakurripin(PORTJOY, JOYGORA) > 0){
			piztupinout(PORTLED, LED1);
			piztupinout(PORTLED, LED3);
			itzalipinout(PORTLED, LED2);
			itzalipinout(PORTLED, LED4);
		}else{
			if(irakurripin(PORTJOY, JOYEZKER) > 0){
				piztupinout(PORTLED, LED2);
				piztupinout(PORTLED, LED4);
				itzalipinout(PORTLED, LED1);
				itzalipinout(PORTLED, LED3);
			}else{
				if(irakurripin(PORTJOY, JOYBEHERA) > 0){
				piztupinout(PORTLED, LED1);
				piztupinout(PORTLED, LED4);
				itzalipinout(PORTLED, LED2);
				itzalipinout(PORTLED, LED3);
				}else{
					if((irakurripin(PORTJOY, JOYGORA) == 0)&&(irakurripin(PORTJOY, JOYEZKER) == 0)&&(irakurripin(PORTJOY, JOYBEHERA) == 0)){
						itzalipinout(PORTLED, LED1);
						itzalipinout(PORTLED, LED2);
						itzalipinout(PORTLED, LED3);
						itzalipinout(PORTLED, LED4);
					}else{
						piztupinout(PORTLED, LED1);
						piztupinout(PORTLED, LED2);
						piztupinout(PORTLED, LED3);
						piztupinout(PORTLED, LED4);
					}
				}
			}
		}
	}
}
