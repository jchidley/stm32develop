#include "allHeaders.h"
// C11 standard headers, and libraries, assumed.
// Documentation guide:
// https://www.kernel.org/doc/Documentation/doc-guide/kernel-doc.rst

/**
* DOC: morse.c
*
* A simple set of functions that output morse code messages for a 
* human to understand on a single LED.  From the outset, morse code
* was designed to use a single line/light/sound to send a receive messages
* in a simple to understand method.  Speed or 20 words a minue should be 
* possible to understand.
*
* Better than using multiple LEDs for seperate signals.  It keeps morse
* alive!
* 
* Should be possible to use with other things, say speaker, vibrate, etc.
* you need to provide a functions for 
* signalOn()
* signalOff()
* signalDelay()
*/

/**
* ITU codes for lower case letters
* https://www.itu.int/rec/R-REC-M.1677-1-200910-I/en
* ITU accented e ".._.." is excluded
*/
char *morseLetter[26] = {
	".-",		// a
	"-...",		// b
	"-.-.",		// c
	"-..",		// d
	".",		// e 
	"..-.",		// f
	"--.",		// g
	"....",		// h
	"..",		// i
	".---",		// j
	"-.-",		// k and ITU invitation to transmit
	".-..",		// l
	"--",		// m
	"-.",		// n
	"---",		// o
	".--.",		// p
	"--.-",		// q
	".-.",		// r
	"...",		// s
	"-",		// t
	"..-",		// u
	"...-",		// v
	".--",		// w
	"-..-",		// x and ITU multiply
	"-.--",		// y
	"--..",		// z
};

/**
* ITU codes for digits
* https://www.itu.int/rec/R-REC-M.1677-1-200910-I/en
*/
char *morseDigit[10] = {
	"-----",	// 0
	".----",	// 1
	"..---",	// 2
	"...--",	// 3
	"....-",	// 4
	".....",	// 5
	"-....",	// 6
	"--...",	// 7
	"---..",	// 8
	"----.",	// 9
};

/**
* signalSend() - Send a message in morse code using an LED.
* @morseCode: The dots and dashes to send to the connected human.
* This must either be a " " (space) or a string of '.' and '-' nothing else.
* @signalOn: A function to turn on an LED.
* @signalOn: A function to turn off an LED.
* @signalDelay: A busy wait function.
* @d: The number of C no op statements.
*
* As soon as an incorrect (not '.' or '-' or ' ' is detected, send the 
* morse error signal, then continue with the rest of the morse code.  
* It's up to the human to understand that this code is now junk.
* 
* Everything is based on the signalDelay(d) time units:
* 1 for dot 
* 3 dots for a dash
* 1 off between dot or dash 
* 3 off between letters
* Space is 7 off total
*
* Return: none.
*
*/
void signalSend(char *morseCode, void(*signalOn)(void), void (*signalOff)(void), 
	void (*signalDelay)(void))
{
	if (strcmp(morseCode, " ") == 0) {
		signalOff();
		for (char i = 0; i < 7; i++)
			signalDelay();
		return;
	}
	for(char i = 0; i < strlen(morseCode);i++) {
		char c = morseCode[i];
		if (c == '.') { 
			signalOn();
		}
		else if (c == '-') {
			signalOn();
			signalDelay();
			signalDelay();
		}
		else { // error
			signalSend("........",signalOn,signalOff,signalDelay); 
		}
		signalDelay(); 
		signalOff();
		signalDelay();
	}
	signalDelay();
	signalDelay();
	return;
}

/**
* messageSend() - Send a message in morse code using an LED.
* @msg: ASCII message to be sent, using specific characters.
* @signalOn: A function to turn on an LED.
* @signalOn: A function to turn off an LED.
* @signalDelay: A busy wait function.
* @d: The number of C no op statements.
*
* Use, ideally, and on-board LED to send messages to a human.  More versatile
* than several LEDs of different colours.
*
* ITU codes for ITU selected punctuation
* Extra characters chosen for ITU code words like "understood" to make
* use easier.  These shouldn't conflict with other morse code uses.
* https://www.itu.int/rec/R-REC-M.1677-1-200910-I/en
*
* Return: none.
*
*/
void messageSend(char *msg, void(*signalOn)(void), void(*signalOff)(void), 
	void(*signalDelay)(void))
{
	for(char i = 0; i < strlen(msg); i++) {
		char c = msg[i];
		if (isalpha(c)) {
			char pos = tolower(c) - 'a';
			signalSend(morseLetter[pos], signalOn, signalOff, signalDelay);
		}
		else if (isdigit(c)) {
			char pos = c - '0';
			signalSend(morseDigit[pos], signalOn, signalOff, signalDelay);
		}
		else if (c == ' ') // At top because this will be the most used
			signalSend(" ", signalOn, signalOff, signalDelay);
		else if (c == '.') 
			signalSend(".-.-.-", signalOn, signalOff, signalDelay);
		else if (c == ',') 
			signalSend("--..--", signalOn, signalOff, signalDelay);
		else if (c == ':') 
			signalSend("---...", signalOn, signalOff, signalDelay);
		else if (c == '?') 
			signalSend("..--..", signalOn, signalOff, signalDelay);
		else if (c == '-') 
			signalSend("-....-", signalOn, signalOff, signalDelay);
		else if (c == '/') 
			signalSend("-..-.", signalOn, signalOff, signalDelay);
		else if (c == '(') 
			signalSend("-.--.", signalOn, signalOff, signalDelay);
		else if (c == ')') 
			signalSend("-.--.-", signalOn, signalOff, signalDelay);
		else if (c == '"') 
			signalSend(".-..-.", signalOn, signalOff, signalDelay);
		else if (c == '=') 
			signalSend("-...-", signalOn, signalOff, signalDelay);
		else if (c == '%') // non standard char for *understood*
			signalSend("...-.", signalOn, signalOff, signalDelay);
		else if (c == '+') 
			signalSend(".-.-.", signalOn, signalOff, signalDelay);
		else if (c == '}') // non standard char for *wait*
			signalSend(".-...", signalOn, signalOff, signalDelay);
		else if (c == '>') // non standard char for *end of work*
			signalSend("...-.-", signalOn, signalOff, signalDelay);
		else if (c == '<') // non standard char for *starting signal*
			signalSend("-.-.-", signalOn, signalOff, signalDelay);
		else if (c == '@') 
			signalSend(".--.-.", signalOn, signalOff, signalDelay);
		else // Error.  Any unsed ITU char can be used e.g. £ ¬ ~ #
			signalSend("........", signalOn, signalOff, signalDelay);
		}
}
