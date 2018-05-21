# To Compile

    make

# To run

## Options summary
- i: file to be encrypted/decrypted *required*
- o: file to write the output to *optional - default is rc4.txt.out*
- k: file to read key from *either this or -g is required*
- g: file to generate a key into and read from *either this or -k is required*
- s: size in bytes of the key to generate *optional - default is 256*

example:

    ./rc4 -i input.txt -o output.txt -g key.rc4 -s 128

## Test Script

included is a bash test script to generate a key, encrypt an input file, decrypt it, and diff the original with the decrypted

example:

    ./test.sh input.txt
