
public class rc4{

    public static byte[] state = new byte[256];
    public static byte[] t = new byte[256];

    //key scheduling algorithm 
    public static void ksa(byte[] key){
        int keylen = key.length;
	int j;
	byte t;
	for (int i = 0; i < 256; i++){
            state[i] =  (byte)i;
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
    public static byte[] encrypt(byte[] key, byte[] input){
        int i = 0;
	int j = 0;
	byte t, k;
	byte[] output = new byte[input.length];
	for(int m = 0; m < input.length; m++){
            i = (int)((i+1) % 256);
	    j = (int)(((j+state[i]) % 256) & 0xFF);
            t = state[i];
	    state[i] = state[j];
	    state[j] = t;
	    k = state[(int)(((state[i] + state[j]) % 256) & 0xFF)];
	    output[m] = (byte)(input[m] ^ k);
	}
	return output;
    }

    //main method
    public static void main(String[] args){
        byte[] output;
        String key = "thisisakey";
        String plaintext = "yippee ki yay motherf*cker";
        byte[] keybytes = key.getBytes();
        byte[] plainbytes = plaintext.getBytes();
        
        System.out.println(plaintext);

        ksa(keybytes);

        output = encrypt(keybytes, plainbytes);

        StringBuilder sb = new StringBuilder();
        for (byte b : output) {
            sb.append(String.format("%02X ", b));
        }
        System.out.println(sb.toString());
    }
}
