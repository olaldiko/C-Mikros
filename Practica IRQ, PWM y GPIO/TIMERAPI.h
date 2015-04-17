#ifndef TIMERAPI_H
#define TIMERAPI_H
#include <stdint.h>
#include <stm32f4xx.h>


// Sortu funtzioen helbideak gordetzeko datu mota
typedef void (*funtzio_helbidea_t)(void);


//Aktibatu Timer6a RCCan
void aktTimer(void);
//Ezarri kontadore eta prescalerra
void setTime(uint16_t prescaler, uint16_t counter);
//Lortu kontadorearen balioa
uint16_t getCounter(void);
//Aldatu limitea
void setLimitea(uint16_t counter);
//Lortu update ebentua
uint16_t isUpdate(void);
//Hasi kontatzen
void startCounter(void);
//Gelditu kontadorea
void stopCounter(void);
//Aktibatu edo desaktibatu update-a
void setUpdateMode(int mode);
//Gelditu timerrak breakpointetan
void setDebugMode(int piztua);
//Gelditu timerra counterrera iristean(1) edo jarraitu kontatzen(0) 
void setOnePulse(int mode);
//Sortu interrupzio bat update ebentu bat sortzean
void setUpdateIRQ(int mode);
//Ezarri interrupzioak kasu guztietan edo bakarrik overflowetan sortuko diren
void setInterruptSource(int mode);
//Garbitu interrupzioa
void clearInterrupt(void);
//Hasieratu interrupzio sistema
void initIRQ_TIM6(void);
//Ezarri interrupzioan exekutatuko den funtzioa	
void ezarriIRQFunc(funtzio_helbidea_t func);
//Inizializatu timerraren interrupzioak
void initIRQ_TIM6(void);
#endif


