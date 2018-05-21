#!/bin/bash

FILE=${1}
./rc4 -i $FILE -o $FILE.encrypted.out -g key.rc4
./rc4 -i $FILE.encrypted.out -o $FILE.decrypted.out -k key.rc4

diff $FILE $FILE.decrypted.out
