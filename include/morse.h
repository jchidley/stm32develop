#ifndef __MORSE_H__
#define __MORSE_H__

void signalCode(char *morseCode, void (*ledOn)(void), void (*ledOff)(void), void (*delay)(void));
void messageSend(char *msg, void (*ledOn)(void), void (*ledOff)(void), void (*delay)(void));

#endif // __MORSE_H__
