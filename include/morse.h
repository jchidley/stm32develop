#ifndef __MORSE_H__
#define __MORSE_H__

void signalCode( char *morseCode, void (*ledOn)(void), void (*ledOff)(void), void (*delay)(uint32_t), uint32_t d );
void messageSend ( char *msg, void (*ledOn)(void), void (*ledOff)(void), void (*delay)(uint32_t), uint32_t d );

#endif // __MORSE_H__
