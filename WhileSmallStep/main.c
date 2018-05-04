//Austen Barker and Staunton Sample

#include "While.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

    //hash table for use as the state
    hashObject **hashArray = (hashObject**)calloc(500, sizeof(hashObject *));

    //If statement example from the assignment description
    //tests boolean, arithmetic, if statements, composition, and assignment
    //we added an additional assignment 'y:=5' in order to test more than two chained commands
    //and multiple variables in the state hash table
    printf("If statment, composition, assignment, arithmetic, and boolean test.\n");
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
    int result1 = eval(c1c2, hashArray);
    printf("Evaluation done, values for x and y should be 4 and 5.\n\n");


    //new hash table for second test
    hashObject **hashArray2 = (hashObject**)calloc(500, sizeof(hashObject *));
    
    printf("While statement, boolean, and arithmetic check\n");
    ast *three2 = intExpression(2);
    ast *one2 = intExpression(1);
    ast *five2 = intExpression(5);
    ast *x2 = variableExp("x");
    ast *y2 = variableExp("y");
    ast *initialx2 = assignExpression('=', "x", three2);
    ast *initialy2 = assignExpression('=', "y", five2);
    ast *test2 = booleanExpression('<', x, five2);
    ast *add2 = arithExpression('+', x, one2);
    ast *inc2 = assignExpression('=', "x", add2);
    ast *whileExp = whileExpression(' ', test2, inc2);
    ast *whilecomp = compExpression(';', initialx2, whileExp);
    int result2 = eval(whilecomp, hashArray2);
    printf("Evaluation Done, final value for x should be 5.\n\n");

    //Chaining while and if statements
    hashObject **hashArray3 = (hashObject**)calloc(500, sizeof(hashObject*));
    
    printf("While statement, if statement, and assignment test.\n");
    ast *whileandif = compExpression(';', whileExp, ifstatement);
    ast *test3 = compExpression(';', initialx2, whileandif);
    int result3 = eval(test3, hashArray3);
    printf("Evaluation done, final value for x should be 4.\n");
}
