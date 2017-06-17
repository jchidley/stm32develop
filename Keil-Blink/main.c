#include "stm32f072xb.h"
#define LED_PIN (7)		// from the data sheet 7C 5A
#define LED_PORT (GPIOC)	// Also need to enable the correct port with RCC
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
	LED_PORT->BSRR = (1UL << LED_PIN);
}

/**
* ledOff() - Turn off the led
*
* Return: none.
*/
void ledOff()
{
	LED_PORT->BSRR = ((1UL << LED_PIN) << 16);
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
	RCC->AHBENR = RCC_AHBENR_GPIOCEN;		// Port C enable
	LED_PORT->MODER |= (1UL << 2 * LED_PIN);	// Output
	LED_PORT->OTYPER &= ~(1UL << 1 * LED_PIN);	// Output push-pull
	LED_PORT->OSPEEDR |= (3UL << 0 * LED_PIN);	// Low speed
	LED_PORT->PUPDR &= ~(3UL << 2 * LED_PIN);	// No pull-up, pull-down

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
}
