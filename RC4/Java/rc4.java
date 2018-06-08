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
        String plaintext = "Friends, Romans, countrymen, lend me your ears; I come to bury Caesar, not to praise him. The evil that men do lives after them; The good is oft interred with their bones; So let it be with Caesar. The noble BrutusHath told you Caesar was ambitious:If it were so, it was a grievous fault,And grievously hath Caesar answer'd it.Here, under leave of Brutus and the restFor Brutus is an honourable man;So are they all, all honourable menCome I to speak in Caesar's funeral.He was my friend, faithful and just to me:But Brutus says he was ambitious;And Brutus is an honourable man.He hath brought many captives home to RomeWhose ransoms did the general coffers fillDid this in Caesar seem ambitious?When that the poor have cried, Caesar hath wept:Ambition should be made of sterner stuff:Yet Brutus says he was ambitious;And Brutus is an honourable man.You all did see that on the LupercalI thrice presented him a kingly crown,Which he did thrice refuse, was this ambition?Yet Brutus says he was ambitious;And, sure, he is an honourable man.I speak not to disprove what Brutus spoke,But here I am to speak what I do know.You all did love him once, not without cause:What cause withholds you then, to mourn for him?O judgment! thou art fled to brutish beasts,And men have lost their reason. Bear with me;My heart is in the coffin there with Caesar, And I must pause till it come back to me.";
        byte[] keybytes = key.getBytes();
        byte[] plainbytes = plaintext.getBytes();
        
        System.out.println(plaintext);
        
        long startTime = System.nanoTime();
        ksa(keybytes);
        output = encrypt(keybytes, plainbytes);
        long endTime = System.nanoTime();
        long duration = (endTime - startTime);
        System.out.println("Runtime: " + duration + "ns");

        StringBuilder sb = new StringBuilder();
        for (byte b : output) {
            sb.append(String.format("%02X ", b));
        }
        System.out.println(sb.toString());
    }
}
