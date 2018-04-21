//Austen Barker and Staunton Sample

#include "While.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    //create basic ast's for integer expressions.
    ast *left = intExpression(5);
    ast *right = intExpression(4);
    ast *boolTest = intExpression(1); 
    // Tests '+' 
    ast * one = arithExpression('+', left, right);
    int test =eval(one); 
    printf("The result of test for + should be 9, actual:%d\n", test);
    //Tests '*'
    ast * two = arithExpression('*', left, right);
    test = eval(two);
    printf("The result of test for * should be 20, actual:%d\n", test);
    //Tests '^'
    // ast * three = arithExpression('^', left, right);
    // test = eval(three);
    // printf("The result of test for ^ should be 625, actual:%d\n", test);


    //Tests '~'
    ast * three = negExpression('~', boolTest);
    test = eval(three);
    printf("The result of test for ~ should be 0, actual:%d\n", test); 

    ast *four =  
    //testing the hash table for storing variables	
    char *key = "h";
    int h = 6;
    insert(key, h);
    insert(key, h);
    int result = fetch(key);
    printf("Fetch result expected: 6, got:%d \n", result);
}
