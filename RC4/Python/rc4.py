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
        #swappy boi
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
    plain = 'yippee ki yay motherf*ckers'
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
