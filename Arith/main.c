#include "arith.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	ast *left = intExpression(5);
	ast *right = intExpression(4);
    ast *first = arithExpression('+',left,right);

    int result = eval(first);
    printf("Result 1: %d\n", result);
    return 0;
}
