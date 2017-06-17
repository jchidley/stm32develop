#include "stm32f072xb.h"
#define PIN (5)
#include "morse.h"
#define TIMING_DELAY (240UL) 
/** 
* 50 - 60ms, 20 words a minute - highest level of amateur license
* 200 - 240ms, 5 wpm - last defined minimum
* PARIS is the 'standard' word, it's 50 units.
* CODEX is another word, it's 60 units.
*/

// I don't like globals.  There must be a better way
uint32_t volatile TimingDelay = 0UL;

/**
* Systick_Init() - Set up SysTick_Handler to fire every 1ms 
*
* Return: none.
*/
void Systick_Init(void)
{
	while (SysTick_Config(SystemCoreClock / 1000UL)) 
		;
}

/**
* morseTimingDelay() - Do nothing while waiting for a period
*
* Return: none.
*/
void morseTimingDelay()
{
	// wait for a bunch of ops to be complete, timing inexact
	// for (uint32_t volatile n = 0; n < 200000UL; n++)
	//	;
	
	// Execute a nop until a certain amount of time has passed
	TimingDelay = TIMING_DELAY;
	while(TimingDelay > 0)
		;  
}

/**
* ledOn() - Turn on the led
*
* Return: none.
*/
void ledOn()
{
	GPIOA->BSRR = (1UL << PIN);
}

/**
* ledOff() - Turn off the led
*
* Return: none.
*/
void ledOff()
{
	GPIOA->BSRR = ((1UL << PIN) << 16);
}

/**
* SysTick_Handler() - Decrement global variable each SysTick
*
* Return: none.
*/
void SysTick_Handler(void)
{
	if (TimingDelay > 0)
		TimingDelay--;
}

int main()
{	
	RCC->AHBENR = RCC_AHBENR_GPIOAEN;   // Port A enable
	GPIOA->MODER |= (1UL << 2 * PIN);   // Output
	GPIOA->OTYPER &= ~(1UL << 1 * PIN); // Output push-pull
	GPIOA->OSPEEDR |= (3UL << 0 * PIN); // Low speed
	GPIOA->PUPDR &= ~(3UL << 2 * PIN);  // No pull-up, pull-down
	
	Systick_Init();

	// Signal startup to the human
	messageSend("<", ledOn, ledOff, morseTimingDelay);

	uint64_t tmpInt = (uint64_t)1;
	uint64_t *tmp = &tmpInt;
	memset(tmp, 0xf0, 5);

	while (1)
	{
		// "k" - ITT - give me work!
		messageSend("jack ", ledOn, ledOff, morseTimingDelay);
	}
	// we're not going to get here but...
	// messageSend(">", ledOn, ledOff, morseTimingDelay);
}
