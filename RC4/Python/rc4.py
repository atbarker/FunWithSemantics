import sys
import time

#key scheduling algorithm, initializes the state
def ksa(key):
    keylength = len(key)
    state = range(256)
    for i in range(0,255):
        state[i] = i
    j = 0
    for i in range(0,255):
        j = (j + state[i] + key[i % keylength]) % 256
        #swappy
        state[i], state[j] = state[j], state[i] 
    return state

#psueudo-random number generator
def prga(state):
    i = 0
    j = 0
    while True:
        i = (i+1) % 256
        j = (j + state[i]) % 256
        state[i], state[j] = state[j], state[i]
        k = state[(state[i] + state[j]) % 256]
        yield k

#more convenient encoding for the key
def key_to_ord(s):
    return [ord(c) for c in s]

def enc(plain, key, length):
    S = ksa(key)
    keystream = prga(S)
    ciphertext = [0]*length
    for c in range(0, length-1):
        ciphertext[c] = (plain[c] ^ keystream.next())
    return ciphertext

#main
def main():
    key = 'key'
    plain = "Friends, Romans, countrymen, lend me your ears; I come to bury Caesar, not to praise him. The evil that men do lives after them; The good is oft interred with their bones; So let it be with Caesar. The noble Brutus Hath told you Caesar was ambitious: If it were so, it was a grievous fault, And grievously hath Caesar answer'd it. Here, under leave of Brutus and the rest For Brutus is an honourable man; So are they all, all honourable men Come I to speak in Caesar's funeral. He was my friend, faithful and just to me: But Brutus says he was ambitious; And Brutus is an honourable man. He hath brought many captives home to Rome Whose ransoms did the general coffers fill Did this in Caesar seem ambitious? When that the poor have cried, Caesar hath wept: Ambition should be made of sterner stuff: Yet Brutus says he was ambitious; And Brutus is an honourable man. You all did see that on the Lupercal I thrice presented him a kingly crown, Which he did thrice refuse, was this ambitioYet Brutus says he was ambitious;And, sure, he is an honourable man. I speak not to disprove what Brutus spoke, But here I am to speak what I do know. You all did love him once, not without cause: What cause withholds you then, to mourn for him? O judgment! thou art fled to brutish beasts, And men have lost their reason. Bear with me; My heart is in the coffin there with Caesar, And I must pause till it come back to me."
    length = len(plain)

    key = key_to_ord(key)
    plain_ord = key_to_ord(plain)

    print("Plaintext:")
    print(plain)
    t0 = time.clock()
    cipher = enc(plain_ord, key, length) 
    t1 = time.clock()
    print("Time in seconds %f" % (t1-t0))
    print("Ciphertext:")
       
    for c in cipher:    
        sys.stdout.write("%02X" % c)
    print
    
if __name__ == "__main__":
    main()
