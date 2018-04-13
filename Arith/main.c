//Austen Barker and Staunton Sample

#include "arith.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	ast *left = intExpression(5);
	ast *right = intExpression(4);
	//4 + 5
    ast *first = arithExpression('+',left,right);
    int result = eval(first);
    printf("Result 1: %d\n", result);
    
    //4 * 5
    ast *second = arithExpression('*', left, right);
    result = eval(second);
    printf("Result 2: %d\n", result);

    // 3
    ast *third = intExpression(3);
    result = eval(third);
    printf("Result 3: %d\n", result);

    //5^4
    ast *fourth = arithExpression('^', left,right );
    result = eval(fourth);
    printf("Result 4: %d\n", result);

    //5 + (5 + 4)
    ast *fifth = arithExpression('+',left, first);
    result = eval(fifth);
    printf("Result 5: %d\n", result);
    
    //5 * (5^4)
    ast *sixth = arithExpression('*', fourth, right);
    result = eval(sixth);
    printf("Result 6: %d\n", result);
    return 0;
}
