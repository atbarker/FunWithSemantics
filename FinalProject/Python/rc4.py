import sys

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

def key_to_ord(s):
    return [ord(c) for c in s]


def main():

    key = 'key'
    plain = 'yippee ki yay motherf*ckers'
    ciphertext = [len(plain)]

    key = key_to_ord(key)
    
    S = ksa(key)
    keystream = prga(S)

    print("Plaintext:")
    print(plain)
    
    print("Ciphertext:")
    for c in plain:
        sys.stdout.write("%02X" % (ord(c) ^ keystream.next()))
    
    print
    

if __name__ == "__main__":
    main()
