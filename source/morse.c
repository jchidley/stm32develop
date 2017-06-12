#include "allHeaders.h"
// https://www.itu.int/rec/R-REC-M.1677-1-200910-I/en for the formal definition
// Build a struct with the morse code mapping
// Everything is based on time units:
// 1 for dot 
// 3 dots for a dash
// 1 between dot or dash 
// 3 between letters
// 7 between words (i.e. 3 between  letters, 4 for the space)
char *morseLetters[26] = {
	".-",		// a
	"-...",		// b
	"-.-.",		// c
	"-..",		// d
	".",		// e // ITU accented e ".._.."
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

char *morseNumbers[10] = {
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

void signalCode( char *morseCode, void (*ledOn)(void), void (*ledOff)(void), 
	void (*delay)(uint32_t), uint32_t d )
{
// Everything is based on time units:
// 1 for dot 
// 3 dots for a dash
// 1 off between dot or dash 
// 3 off between letters
// Space is 7 off total
	for(char i = 0; i < strlen(morseCode);i++) {
		char c = morseCode[i];
		if (c == '.') { 
			ledOn();
		}
		else if (c == '-') {
			ledOn();
			delay(d);
			delay(d);
		}
		else if (c == ' ') {
			ledOff();
			delay(d);
			delay(d);
			delay(d);
		}
		else signalCode("........",ledOn,ledOff,delay,d); // error
		delay(d); 
		ledOff();
		delay(d);
	}
	delay(d);
	delay(d);
}

void messageSend ( char *msg, void (*ledOn)(void), void (*ledOff)(void), void (*delay)(uint32_t), uint32_t d )
{
	for(char i = 0; i < strlen(msg); i++) {
		char c = msg[i];
		if (isalpha(c)) {
			char pos = tolower(c) - 'a';
			signalCode(morseLetters[pos], ledOn, ledOff, delay,d);
		}
		else if (isdigit(c)) {
			char pos = c - '0';
			signalCode(morseNumbers[pos], ledOn, ledOff, delay,d);
		}
		else if (c == ' ') // At top because this will be the most used
			signalCode(" ", ledOn, ledOff, delay,d);
		else if (c == '.') 
			signalCode(".-.-.-", ledOn, ledOff, delay,d);
		else if (c == ',') 
			signalCode("--..--", ledOn, ledOff, delay,d);
		else if (c == ':') 
			signalCode("---...", ledOn, ledOff, delay,d);
		else if (c == '?') 
			signalCode("..--..", ledOn, ledOff, delay,d);
		else if (c == '-') 
			signalCode("-....-", ledOn, ledOff, delay,d);
		else if (c == '/') 
			signalCode("-..-.", ledOn, ledOff, delay,d);
		else if (c == '(') 
			signalCode("-.--.", ledOn, ledOff, delay,d);
		else if (c == ')') 
			signalCode("-.--.-", ledOn, ledOff, delay,d);
		else if (c == '"') 
			signalCode(".-..-.", ledOn, ledOff, delay,d);
		else if (c == '=') 
			signalCode("-...-", ledOn, ledOff, delay,d);
		else if (c == '%') // my char for ITU understood
			signalCode("...-.", ledOn, ledOff, delay,d);
		else if (c == '+') 
			signalCode(".-.-.", ledOn, ledOff, delay,d);
		else if (c == '}') // my char for ITU wait
			signalCode(".-...", ledOn, ledOff, delay,d);
		else if (c == '>') // my char for ITU end of work
			signalCode("...-.-", ledOn, ledOff, delay,d);
		else if (c == '<') // my char for ITU starting signal
			signalCode("-.-.-", ledOn, ledOff, delay,d);
		else if (c == '@') 
			signalCode(".--.-.", ledOn, ledOff, delay,d);
		else // Error, any currently unsed char, say � ~ � $ #
			signalCode("........", ledOn, ledOff, delay,d);
		}
}
