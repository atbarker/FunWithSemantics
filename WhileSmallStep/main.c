//Austen Barker and Staunton Sample

#include "While.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

    //hash table for use as the state
    hashObject **hashArray = (hashObject**)calloc(500, sizeof(hashObject *));

    //create basic ast's for integer expressions.
    ast *left = intExpression(5);
    ast *right = intExpression(4);
    ast *divtest = intExpression(20);
    ast *boolTest = intExpression(1); 
    
        
    /*//if true
    ast *twelve1 = ifExpression(' ', eight, twelve, ten);
    int twelve1Test = eval(twelve1, hashArray);
    //printf("if true successful\n");

    //if false
    ast *twelve2 = ifExpression(' ', six, twelve, ten);
    int twelve2Test = eval(twelve2, hashArray);
    //printf("if false successful\n");

    ast *thirteen1 = variableExp("a");
    ast *thirteen2 = intExpression(7);
    ast *thirteen3 = booleanExpression('<', thirteen1, thirteen2);
    ast *thirteen4 = intExpression(1);
    ast *thirteen5 = arithExpression('+', thirteen1, thirteen4);
    ast *thirteen6 = assignExpression('=', "a", thirteen5);
    ast *thirteen = whileExpression(' ', thirteen3, thirteen6);
    int woop = eval(thirteen, hashArray);
    //printf("While loop working\n");
    */
    
    
    //testing the hash table for storing variables	
    //char *key = "a";
    //int h = 6;
    //insert(key, h, hashArray);
    //insert(key, h, hashArray);
    //int result = fetch(key, hashArray);
    //printf("Fetch result expected: 6, got:%d \n", result);
}
