//Austen Barker and Staunton Sample

#include "While.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    //create basic ast's for integer expressions.
    ast *left = intExpression(5);
    ast *right = intExpression(4);

    //testing the hash table for storing variables	
    char *key = "h";
    int h = 6;
    insert(key, h);
    insert(key, h);
    int result = fetch(key);
    printf("Fetch result expected: 6, got:%d \n", result);
}
