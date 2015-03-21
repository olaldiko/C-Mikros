
#include "GPIOAPI.h"
#define LED 6
int main(){
		int i = 0;
		aktdesgpio(5, 1);
		setpinmode(5, LED, 2);
		itzalipinout(5, LED);
		while( 0 == 0){
			for(i = 0; i < 10000; i++);
			aldatupinout(5, LED);
		}
}
