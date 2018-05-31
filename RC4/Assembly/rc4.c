#include <stdbool.h>
#include <stddef.h>
//#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Rc4State {
    unsigned char i;
    unsigned char j;
    unsigned char s[256];
};

void rc4_init(struct Rc4State state[static 1], const unsigned char key[static 1], size_t len) {
    for (int i = 0; i < 256; i++)
        state->s[i] = (unsigned char)i;
    state->i = 0;
    state->j = 0;
    
    unsigned char j = 0;
    for (int i = 0; i < 256; i++) {
        j += state->s[i] + key[i % len];
        
        // Swap
        unsigned char temp = state->s[i];
        state->s[i] = state->s[j];
        state->s[j] = temp;
    }
}



int main(void) {
    // Self-check
    printf("Self-check passed\n");
    
    // Benchmark speed
    const long TRIALS = 300000;
    #define MSG_LEN 1024
    
    unsigned char key[3] = {'a', 'b', 'c'};
    unsigned char msg[MSG_LEN] = {0};
    char* input = "Friends, Romans, countrymen, lend me your ears; I come to bury Caesar, not to praise him. The evil that men do lives after them; The good is oft interred with their bones; So let it be with Caesar. The noble BrutusHath told you Caesar was ambitious:If it were so, it was a grievous fault,And grievously hath Caesar answer'd it.Here, under leave of Brutus and the restFor Brutus is an honourable man;So are they all, all honourable menCome I to speak in Caesar's funeral.He was my friend, faithful and just to me:But Brutus says he was ambitious;And Brutus is an honourable man.He hath brought many captives home to RomeWhose ransoms did the general coffers fillDid this in Caesar seem ambitious?When that the poor have cried, Caesar hath wept:Ambition should be made of sterner stuff:Yet Brutus says he was ambitious;And Brutus is an honourable man.You all did see that on the LupercalI thrice presented him a kingly crown,Which he did thrice refuse, was this ambition?Yet Brutus says he was ambitious;And, sure, he is an honourable man.I speak not to disprove what Brutus spoke,But here I am to speak what I do know.You all did love him once, not without cause:What cause withholds you then, to mourn for him?O judgment! thou art fled to brutish beasts,And men have lost their reason. Bear with me;My heart is in the coffin there with Caesar, And I must pause till it come back to me.";
    struct Rc4State state;
    rc4_init(&state, key, sizeof(key));
    
    time_t start;
    
    start = clock();
    rc4_encrypt_x86(&state, input, 1414);
    printf("Speed (x86): %.1f MB/s\n", (clock() - start) * CLOCKS_PER_SEC / 1000000);
    
    return EXIT_SUCCESS;
    #undef MSG_LEN
}
