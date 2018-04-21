//Austen Barker and Staunton Sample

#include "While.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    //create basic ast's for integer expressions.
    ast *left = intExpression(5);
    ast *right = intExpression(4);
    ast *divtest = intExpression(20);
    ast *boolTest = intExpression(1); 

    // Tests '+' 
    ast * one = arithExpression('+', left, right);
    int test =eval(one); 
    printf("The result of test for + should be 9, actual:%d\n", test);

    //Tests '*'
    ast * two = arithExpression('*', left, right);
    test = eval(two);
    printf("The result of test for * should be 20, actual:%d\n", test);

    //Tests '/'
    ast * three = arithExpression('/', divtest, right);
    test = eval(three);
    printf("The result of test for / should be 5, actual:%d\n", test);


    //Tests '~'
    ast * four = negExpression('~', boolTest);
    int threeTest = eval(four);
    printf("The result of test for ~ should be 0, actual:%d\n", threeTest); 

    ast *five = booleanExpression('=', left, right);
    int fourTest = eval(five);
    printf("The result of test for = should be 0, actual:%d\n", fourTest);

    ast *six = booleanExpression('<', left, right);
    int sixTest = eval(six);
    printf("The result of test for < should be 0, actual:%d\n", sixTest);

    ast *seven = booleanExpression('|', left, right);
    int sevenTest = eval(seven);
    printf("The result of test for | should be 1, actual:%d\n", sevenTest);

    ast *eight = booleanExpression('&', left, right);
    int eightTest = eval(eight);
    printf("The result of test for & should be 1, actual:%d\n", eightTest);

    //variable storage/assignment/update
    ast *nine = assignExpression('=', "a", right);
    int nineTest = eval(nine);
    printf("Variable a assigned to value 4\n");

    //variable retrieval
    ast *ten = variableExp("a");
    int tenTest = eval(ten);
    printf("Retrieved value should be 4, actual:%d\n", tenTest);

    //skip command
    ast *eleven = skipExpression('@', right);
    int elevenTest = eval(eleven);
    printf("Skip successful\n");

    //composition expression
    ast *nine1 = assignExpression('=', "r", right);
    ast *ten1 = variableExp("r");
    ast *twelve = compExpression(';', nine1, ten1);
    int twelveTest = eval(twelve);
    printf("Composition successful\n");

    //if true
    ast *twelve1 = ifExpression(' ', eight, twelve, ten);
    int twelve1Test = eval(twelve1);
    printf("if true successful\n");

    //if false
    ast *twelve2 = ifExpression(' ', six, twelve, ten);
    int twelve2Test = eval(twelve2);
    printf("if false successful\n");

    ast *thirteen1 = variableExp("a");
    ast *thirteen2 = intExpression(7);
    ast *thirteen3 = booleanExpression('<', thirteen1, thirteen2);
    ast *thirteen4 = intExpression(1);
    ast *thirteen5 = arithExpression('+', thirteen1, thirteen4);
    ast *thirteen6 = assignExpression('=', "a", thirteen5);
    ast *thirteen = whileExpression(' ', thirteen3, thirteen6);
    int woop = eval(thirteen);
    printf("While loop working\n");

    
    
    //testing the hash table for storing variables	
    //char *key = "a";
    //int h = 6;
    //insert(key, h);
    //insert(key, h);
    //int result = fetch(key);
    //printf("Fetch result expected: 6, got:%d \n", result);
}
