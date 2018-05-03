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
    
    ast *three = intExpression(3);
    ast *one = intExpression(1);
    ast *five = intExpression(5);
    ast *x = variableExp("x");
    ast *y = variableExp("y");
    ast *initial = assignExpression('=', "x", three);
    ast *initialy = assignExpression('=', "y", five);
    ast *test = booleanExpression('<', x, five);
    ast *add = arithExpression('+', x, one);
    ast *sub = arithExpression('-', x, one);
    ast *inc = assignExpression('=', "x", add);
    ast *dec = assignExpression('=', "x", sub);
    ast *ifstatement = ifExpression(' ', test, inc, dec);
    ast *c2c3 = compExpression(';', ifstatement, initialy);
    ast *c1c2 = compExpression(';', initial, c2c3);
    int fun = eval(c1c2, hashArray); 
    
    //testing the hash table for storing variables	
    //char *key = "a";
    //int h = 6;
    //insert(key, h, hashArray);
    //insert(key, h, hashArray);
    //int result = fetch(key, hashArray);
    //printf("Fetch result expected: 6, got:%d \n", result);
}
