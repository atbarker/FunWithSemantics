#ifndef RC4_H_
#define RC4_H_

#include <stdlib.h>

void rc4(unsigned char key[], size_t keySize, unsigned char *inputBuffer, unsigned char *outputBuffer, int bufferLength);

#endif
