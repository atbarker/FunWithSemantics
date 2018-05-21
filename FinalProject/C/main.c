#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "rc4.h"

/*
 * Generates a sequence of keySize pseudorandom bytes
 * and writes them to outfile
 * 
*/
void generateKeyFile(size_t keySize, FILE* outfile) {
    unsigned char nextByte;
    srand(time(NULL));
    size_t i;
    for(i = 0; i < keySize; i++) {
        nextByte = rand () % 256;
        fputc(nextByte, outfile);
    }
}

/*
 * Returns the size of a file in bytes
 * 
*/
size_t getFileSize(FILE* infile) {
    size_t size = 0;
    fseek(infile, 0L, SEEK_END);
    size = ftell(infile);
    fseek(infile, 0L, SEEK_SET);
    return size;
}

/*
 * Reads keyArray bytes from infile into the keyArray
 * or until EOF is reached
 * returns the number of bytes read
*/
size_t readKeyFile(unsigned char keyArray[], size_t keySize, FILE* infile) {
    char inputByte;
    unsigned char currentByte;
    size_t index = 0;
    while ((inputByte = fgetc(infile)) != EOF && index < keySize) {
        currentByte = (unsigned char) inputByte;
        keyArray[index] = currentByte;
        index++;
    }
    return index;
}

int main( int argc, char* argv[] ) {
    int bufferLength = 2048;
    int itemsRead = 0;
    int keygen = 0;
    int keySize = 0;
    int keySizeGiven = 0;
    int keyName = 0;
    int c;
    FILE* infile = NULL;
    FILE* outfile = NULL;
    FILE* keyfile = NULL;
    char *inputfilename = NULL;
    char *outputfilename = "rc4.txt.out";
    char *keyfilename = NULL;
    unsigned char inputBuffer[bufferLength];
    unsigned char outputBuffer[bufferLength];

    while ((c = getopt (argc, argv, "i:o:k:g:s")) != -1) {
        switch (c) {
            case 'i':
                inputfilename = optarg;
                break;
            case 'o':
                outputfilename = optarg;
                break;
            case 'k':
                keyfilename = optarg;
                if (keygen) {
                    printf("can't specify a key file and a keygenfile\n");
                    exit(1);
                }
                keyName = 1;
                break;
            case 'g':
                keyfilename = optarg;
                if (keyName) {
                    printf("can't specify a key file and a keygenfile\n");
                    exit(1);
                }
                keygen = 1;
                break;
            case 's':
                keySize = atoi(optarg);
                keySizeGiven = 1;
                break;
            default:
                printf("Invalid argument\n");
                exit(1);

        }
    }

    if (inputfilename == NULL) {
        printf("must specify input file name\n");
        exit(1);
    }
    
    if (keyfilename == NULL) {
        printf("must specify or generate a key file\n");
        exit(1);
    }
	

    if ((infile = fopen(inputfilename, "r")) ==NULL){
        printf("Error opening infile\n");
        exit(1);
    }

    if ((outfile = fopen(outputfilename, "w")) ==NULL){
        printf("Error opening outfile\n");
        exit(1);
    }


    if (keygen) {
        if (!keySizeGiven) {
            keySize  = 256;
        }
        if ((keyfile = fopen(keyfilename, "w")) ==NULL){
            printf("Error opening keyfile for key generation\n");
            exit(1);
        }
        generateKeyFile(keySize, keyfile);
        fclose(keyfile);
    }

    if ((keyfile = fopen(keyfilename, "r")) ==NULL){
        printf("Error opening keyfile\n");
        exit(1);
    }

    keySize = getFileSize(keyfile);
    unsigned char keyArray[keySize];
    readKeyFile(keyArray, keySize, keyfile);
    fclose(keyfile);

    while(1) {
        itemsRead = fread(inputBuffer, sizeof(unsigned char), bufferLength, infile);
        itemsRead = itemsRead;
        rc4(keyArray, keySize, inputBuffer, outputBuffer, itemsRead);
        fwrite(outputBuffer, sizeof(unsigned char), itemsRead, outfile);

        if (itemsRead != bufferLength) {
            break;
        }
    }

    fclose(infile);
    fclose(outfile);
    return 0;

}
