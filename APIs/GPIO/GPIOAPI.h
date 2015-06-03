#ifndef GPIOAPI_H
#define GPIOAPI_H
#include <stdint.h>

#define GPIO_OUT_PP 0
#define GPIO_OUT_OD 1
//Aktibatu edo desaktibatu gpio portua
void aktdesgpio(int portua, int egoera);
//Aktibatu edo desaktibatu pin baten irteera(Lehenengo out bezala konfiguratu)
void aktdesgpioout(int portua, int pina, int egoera);
//Itzali irteera pin bat
void itzalipinout(int portua, int pina);
//Piztu irteera pin bat
void piztupinout(int portua, int pina);
//Aldatu(piztu/itzali) irteera pin bat
void aldatupinout(int portua, int pina);
//Konfiguratu pin bat irteera sarrera edo analogiko bezala
void setpinmode(int portua, int pina, int modua);
//Konfiguratu pull up eta pull down erresistentziak.
void setResistorMode(int portua, int pina, int modua);
//Irakurri pin baten balioa
uint32_t irakurripin(int portua, int pina);
//Set the output mode to push-pull(0) or open-drain(1)
void setOutputMode(uint8_t port, uint8_t pin, uint8_t mode);

#endif
