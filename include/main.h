#include "STM32F030x8.h" // "stm32f072xb.h" or "STM32F030x8.h"
#define LED_PIN (7)		// from the data sheet 7C 5A 7A
#define LED_PORT (GPIOA)	
#define ABH_GPIO_PORT_ENABLE (RCC_AHBENR_GPIOAEN)

#include "morse.h"
#define TIMING_DELAY (240UL) 
/** 
* 50 - 60ms, 20 words a minute - highest level of amateur license
* 200 - 240ms, 5 wpm - last defined minimum
* PARIS is the 'standard' word, it's 50 units.
* CODEX is another word, it's 60 units.
*/