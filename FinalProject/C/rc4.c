#include <stdio.h>
#include "rc4.h"


/*
 * Swaps the values at the given indexes indexA and indexB
 * in the arrayS using a temp value
 * 
*/
void swapIndexes(unsigned char arrayS[], size_t indexA, size_t indexB) {
    unsigned char temp = arrayS[indexA];
    arrayS[indexA] = arrayS[indexB];
    arrayS[indexB] = temp;
}


/* KEY SCHEDULING ALGORITHM
 * Initializes S to the values 0-255, then does an initial permutation
 * according to the rc4 algorithm
 * arrayS is assumed to have a size of 256
 *
*/
void initializeS(unsigned char key[], size_t keySize, unsigned char arrayS[]) {
    unsigned char arrayT[256];
    int j = 0;    
    int i = 0;
    for(i = 0; i < 256; i++) {
        arrayS[i] = i;
        arrayT[i] = key[i % keySize];
    }

    i = 0;
    for(i = 0; i < 256; i++) {
        j = (j + arrayS[i] + arrayT[i]) % 256;
        swapIndexes(arrayS, i, j);
    }
}
/* Combination of the PRGA and XOR at the end of the loop
 * Implements the rc4 stream cipher
 * does an initial permutation of the key,
 * then uses it to encrypt one byte at a time from the input file and write it
 * to the output file
 *
*/
void rc4(unsigned char key[], size_t keySize, unsigned char *inputBuffer, unsigned char *outputBuffer, int bufferLength) {
    unsigned char arrayS[256];
    initializeS(key, keySize, arrayS);
    int a = 0;
    unsigned char currentByte = 0;
    unsigned char encryptedByte = 0;
    unsigned char k = 0;
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char t = 0;
    for(a = 0; a < bufferLength; a++){
        currentByte = inputBuffer[a];
        i = (i + 1) % 256;
        j = (j + arrayS[i]) % 256;
        swapIndexes(arrayS, i, j);
        t = (arrayS[i] + arrayS[j]) % 256;
        k = arrayS[t];
        encryptedByte = currentByte ^ k;
        outputBuffer[a] = encryptedByte;
    }
}
