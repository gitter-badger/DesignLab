#ifndef __ZPUINO_H__
#define __ZPUINO_H__

#include "register.h"
#include "interrupt.h"

#define __ZPUINO__ 1

static inline __attribute__((always_inline)) register_t outputRegisterForPin(unsigned int pin)
{
	return &GPIODATA(pin/32);
}

static inline __attribute__((always_inline)) register_t inputRegisterForPin(unsigned int pin)
{
	return &GPIODATA(pin/32);
}

static inline __attribute__((always_inline)) register_t modeRegisterForPin(unsigned int pin)
{
	return &GPIOTRIS(pin/32);
}

static inline __attribute__((always_inline)) unsigned int bitMaskForPin(unsigned int pin)
{
    return (1<<(pin%32));
}

static inline __attribute__((always_inline)) void digitalWrite(unsigned int pin, int value)
{
	if (value) {
		*outputRegisterForPin(pin) |= bitMaskForPin(pin);
	} else {
		*outputRegisterForPin(pin) &= ~bitMaskForPin(pin);
	}
}

static inline __attribute__((always_inline)) int digitalRead(unsigned int pin)
{
	return !!(*inputRegisterForPin(pin) & bitMaskForPin(pin));
}

static inline __attribute__((always_inline)) void pinMode(unsigned int pin, int mode)
{
	if (mode) {
		*modeRegisterForPin(pin) |= bitMaskForPin(pin);
	} else {
		*modeRegisterForPin(pin) &= ~bitMaskForPin(pin);
	}
}

#endif