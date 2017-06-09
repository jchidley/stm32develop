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
".-",        // a
"-...",      // b
"-.-.",      // c
"-..",       // d
".",         // e ITU accented e, ".._.."
"..-.",      // f
"--.",       // g
"....",      // h
"..",        // i
".---",      // j
"-.-",       // k also ITU invitation to transmit
".-..",      // l
"--",        // m
"-.",        // n
"---",       // o
".--.",      // p
"--.-",      // q
".-.",       // r
"...",       // s
"-",         // t
"..-",       // u
"...-",      // v
".--",       // w
"-..-",      // x also ITU multiply
"-.--",      // y
"--..",      // z
};

char *morseNumbers[10] = {
"-----",     // 0
".----",     // 1
"..---",     // 2
"...--",     // 3
"....-",     // 4
".....",     // 5
"-....",     // 6
"--...",     // 7
"---..",     // 8
"----.",     // 9
};

void signalCode( char *morseCode, void (*ledOn)(void), void (*ledOff)(void), void (*delay)(uint32_t), uint32_t d )
{
	for(char i = 0; i < strlen(morseCode);i++)
  {
		char c = morseCode[i];
		if (c == '.') { // 1 on: at bottom. 1 off: at bottom
			ledOn();
		}
		else if (c == '-') // 3 on: 2 extra for a dash, 1 at bottom. 1 off: at bottom.
		{
			ledOn();
			delay(d);
			delay(d);
		}
		else if (c == ' ') 					
		{
			ledOff();
			for (int i = 0; i < 2; i++) // 7 total: 2 for a space, 1 extra per symbol, 1 off for intra symbol and 3 for intra char
			{
				delay(d);
			}
		}
		else signalCode("........",ledOn,ledOff,delay,d)	; // Do error
		//bottom
		delay(d); // 1 for current symbol: on for . and -.  Off for ' ' (as above)
		ledOff();
		delay(d); // intra symbol off
  }
	for (int i = 0; i < 3; i++) // extra 2 off between symbols
	{
		delay(d);
	}
}

void messageSend ( char *msg, void (*ledOn)(void), void (*ledOff)(void), void (*delay)(uint32_t), uint32_t d )
{
	for(char i = 0; i < strlen(msg); i++)
  {
		char c = msg[i];
		if ( isalpha(c) )
		{
			char pos = tolower(c) - 'a';
			signalCode(morseLetters[pos], ledOn, ledOff, delay,d);
		}
		else if ( isdigit(c) )
		{
			char pos = c - '0';
			signalCode(morseNumbers[pos], ledOn, ledOff, delay,d);
		}
		else if (c == ' ') signalCode(" ", ledOn, ledOff, delay,d);				// At top because this will be the most used
		else if (c == '.') signalCode(".-.-.-", ledOn, ledOff, delay,d);
		else if (c == ',') signalCode("--..--", ledOn, ledOff, delay,d);
		else if (c == ':') signalCode("---...", ledOn, ledOff, delay,d);
		else if (c == '?') signalCode("..--..", ledOn, ledOff, delay,d);
		else if (c == '-') signalCode("-....-", ledOn, ledOff, delay,d);
		else if (c == '/') signalCode("-..-.", ledOn, ledOff, delay,d);
		else if (c == '(') signalCode("-.--.", ledOn, ledOff, delay,d);
		else if (c == ')') signalCode("-.--.-", ledOn, ledOff, delay,d);
		else if (c == '"') signalCode(".-..-.", ledOn, ledOff, delay,d);
		else if (c == '=') signalCode("-...-", ledOn, ledOff, delay,d);
		else if (c == '%') signalCode("...-.", ledOn, ledOff, delay,d);		// My char for ITU undertood
		else if (c == '+') signalCode(".-.-.", ledOn, ledOff, delay,d);
		else if (c == '}') signalCode(".-...", ledOn, ledOff, delay,d);		// My char for ITU wait
		else if (c == '>') signalCode("...-.-", ledOn, ledOff, delay,d);	// My char for ITU end of work
		else if (c == '<') signalCode("-.-.-", ledOn, ledOff, delay,d);		// My char for ITU starting signal 
		else if (c == '@') signalCode(".--.-.", ledOn, ledOff, delay,d);
		else signalCode("........", ledOn, ledOff, delay,d); // ITU error
		}
}

/*
void morseSend(char msg[],uint16_t msgLen,uint32_t ledOn,uint32_t ledOff)
{
  // need: 
  // port name in
  // delay function in
  // 
  #include "morse.c"
  const int morseInterval = 600000;
  int len = msgLen / sizeof(msg[0]);

  for (int i = 0; i < len; i++ ) {

      for(int j = 0; j < sizeof (MorseCodeDictionary) / sizeof (MorseCodeDictionary[0]); ++j ) {

        if( msg[i] == MorseCodeDictionary[j].writtenCharacter ) { // need tolower function
          int lenM = sizeof(MorseCodeDictionary[j].code) / sizeof (MorseCodeDictionary[j].code[0]);

          for (int k = 0; k < lenM ; k++) {

            switch (MorseCodeDictionary[j].code[k]) {
              case '.':
                GPIOC->BSRR = ledOn; // on
                break;
              case '-':
                GPIOC->BSRR = ledOn;
                delay(morseInterval * 2);
                break;
              case ' ':
                GPIOC->BSRR = ledOff;
                delay(morseInterval * 6);
                break;
			  default :
				// recursive call to display error, then continue with rest of message
            }

            delay(morseInterval);
            GPIOC->BSRR = ledOff; // off
            delay(morseInterval);

          }
          break;

        }

      }
      delay(morseInterval * 2);

    }

}
*/
