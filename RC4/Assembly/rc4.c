#include <stdio.h>


int rc4_x86(const void *inbuf, void *outbuf, size_t buflen, const char *key, size_t keylen){
    char s[256];
    char *state = s;
    char k[256];
    char *key = k;

    //initialize the state
    __asm {
        mov eax, state
        mov ecx, 256
        fill_s:
            xor ebx, ebx
            sub bl, cl
            mov [eax + ebx], bl
        loop fill_s
    }



    //generate our k
    __asm {



    }
    
    //KSA
    __asm{


    }


    __asm{


    }

    return bufferLength;
}
