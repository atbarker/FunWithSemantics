
#key scheduling algorithm
def ksa(State, key, keylength):
    for i from 0 to 255:
        State[i] = i
    j = 0
    for i from 0 to 255:
        j = (j + S[i] + key[i % keylength]) % 256
        #swap s[i] and s[j]


#psueudo-random number generator
def prga():
    i = 0
    j = 0
    while():
        i = (i+1) % 256
        j = (j + S[i] % 256
        #swap s[i] s[j]
        k = S[(S[i] + S[j]) % 256]
        return k


def main():


if __name__ == "__main__":
    main()
