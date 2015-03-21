#ifndef TIMERAPI_H
#define TIMERAPI_H
#include <stdint.h>
#include <stm32f4xx.h>
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


#endif


