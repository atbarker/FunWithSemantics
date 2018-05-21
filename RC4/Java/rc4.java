
public class rc4{

    public byte[] state = new byte[256];
    public byte[] t = new byte[256];

    //key scheduling algorithm 
    public void ksa(byte[] key){
        int keylen = key.length;
	int j;
	byte t;
	for (int i = 0; i < 256; i++){
            state[i] = (byte) i;
        }
	j = 0;
	for (int i = 0; i < 256; i++){
            j = (j + state[i] + key[i % keylen]) % 256;
	    t = state[i];
	    state[i] = state[j];
	    state[j] = t;
        }
    }

    //pseudo-random number generator
    public byte[] encrypt(byte[] key, byte[] input){
        int i = 0;
	int j = 0;
	byte t, k;
	byte[] output = new byte[input.len];
	for(int m = 0; m < input.len; m++){
            i = (i+1) % 256;
	    j = (j+state[i]) % 256;
            t = state[i];
	    state[i] = state[j];
	    state[j] = t;
	    k = state[(state[i] + state[j]) % 256];
	    output[m] = input[m] ^ k;
	}
	return output;
    }

    //main method
    public static void main(String[] args){


    }

}
