#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

//obtained from http://www.charmysoft.com/app/rc4-cipher
int rc4(const void *input, void *output, size_t buflen, const char *key, size_t keylen){
    char s[256];
    char *state = s;
    char k[256];
    char *k_ptr = k;

    //initialize the state
    //move the address for state into eax
    //move 256 into ecx, this is our loop counter
    //xor ebx and ebx to set contents to zero
    //subtract bl 8 bit register by the cl register this
    //move the contents of the new register into our offset
    __asm {
        mov eax, state
        mov ecx, 256
        fill_s:
            xor ebx, ebx
            sub bl, cl
            mov [eax + ebx], bl
        loop fill_s
    }

    //ksa part 1, populate the array S with values
    __asm {
        mov edx, key ;// set the original key
	mov edi, keylen ;//set edi to be our key length
	mov esi, k_ptr ;//set our pointer to be in register esi
	mov ecx, 256 ;//set our counter to 256
	xor ebx, ebx ;//zero ebx
loop_j:
	cmp ebx, edi ;// compare our j and our keylen
	    jl continue_loop ;//if not equal then continue the loop
	    xor ebx, ebx ;// clear ebx, move to the start of the key, repeat until full
continue_loop:
	mov ah, [edx + ebx] ;//move the j'th value from our key into the AH register
	mov [esi], ah ;//store the AH register into the memory address at esi
	inc esi ;//increment esi
	inc ebx ;//increment ebx to the next value
	loop loop_j
    }
    
    //KSA part 2
    __asm{
        mov edi, s_ptr
	xor ebx, ebx ;//again our counter
	sub esi, 256 ;//go back to the begining of esi (our k pointer)
	xor eax, eax ;//clear eax
loop_s:
	mov dl, [esi + eax]
	add bl, dl ;//add our value k[i] into bl
	mov dl, [edi + eax] //our value S[i] into dl
	add bl, dl ;//add the S[i] value
	mov dl, [edi + eax] ;//perform our swap
	mov dh, [edi + ebx]
	mov [edi+eax], dh
	mov [edi+ebx], dl
	inc eax ;//our counter
	loop loop_s
    }


    __asm{
        mov esi, input ;// our input buffer start address
	mov edi, s_ptr  ;//our state
	mov edx, output ;//our output buffer start address

	xor eax, eax ;//clear some registers
	xor ebx, ebx 
	
	mov exc, buflen  ;//store buffer length
cd:
	push ecx ;//put ecx on the stack
	movzx ecx, al
	inc cl
	push edx
	mov dh,[edi,ecx]
	add bl,dh
	mov dl,[edi+ebx]
	mov [edi+ecx],dl
	mov [edi+ebx],dh
	add dl,dh
	movzx edx,dl
	mov dl,[edi+edx]
	mov cl,[esi+eax]
	xor cl,dl ;//our actual xor step for encryption
	pop edx ;//retrieve edx off the stack
	mov [edx+eax], cl ;//write our xor'd value to the buffer edx
	inc eax ;//increment our counter
	pop ecx ;//retrieve ecx off the stack
	loop cd
    }

    return buflen;
}

int main(){
    void *output;
    const char *key = "thisisakey";
    size_t keylen = 10;
    size_t buflen = 1400;
    char* input = "Friends, Romans, countrymen, lend me your ears; I come to bury Caesar, not to praise him. The evil that men do lives after them; The good is oft interred with their bones; So let it be with Caesar. The noble BrutusHath told you Caesar was ambitious:If it were so, it was a grievous fault,And grievously hath Caesar answer'd it.Here, under leave of Brutus and the restFor Brutus is an honourable man;So are they all, all honourable menCome I to speak in Caesar's funeral.He was my friend, faithful and just to me:But Brutus says he was ambitious;And Brutus is an honourable man.He hath brought many captives home to RomeWhose ransoms did the general coffers fillDid this in Caesar seem ambitious?When that the poor have cried, Caesar hath wept:Ambition should be made of sterner stuff:Yet Brutus says he was ambitious;And Brutus is an honourable man.You all did see that on the LupercalI thrice presented him a kingly crown,Which he did thrice refuse, was this ambition?Yet Brutus says he was ambitious;And, sure, he is an honourable man.I speak not to disprove what Brutus spoke,But here I am to speak what I do know.You all did love him once, not without cause:What cause withholds you then, to mourn for him?O judgment! thou art fled to brutish beasts,And men have lost their reason. Bear with me;My heart is in the coffin there with Caesar, And I must pause till it come back to me.";
    
    clock_t begin = clock();
    rc4((const void*)input, output, buflen, key, keylen);
    clock_t end = clock();
    double timespent = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("Time for execution:  %f\n", timespent);
    return 0;
}
