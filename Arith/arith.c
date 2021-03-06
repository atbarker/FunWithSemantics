#include "arith.h"
#include <stdio.h>
#include <stdlib.h>

//This assignment was created by Austen Barker (1.5 hours) and Staunton Sample (1.5 hours)

//Assessment of an integer. Accepts an integer as an argument and assigns it as a leaf node in an AST
ast * intExpression(int number){
	ast *a = malloc(sizeof(ast));
	a->typeExp = integer_exp;
	a->operation.integerExp = number;
	return a;
}

// Accepts parent and child nodes in an AST. Evaluates type of operation for the parent node. 
// The function then assigns children a position inside the AST parent node
ast * arithExpression(char operator, ast* c1, ast* c2){
	ast *a = malloc(sizeof(ast));
	if(operator == '+'){
		a->typeExp = add_exp;
		a->operation.addExp.operator = operator;
		a->operation.addExp.left = c1;
		a->operation.addExp.right = c2;
	}
	else if(operator == '*'){
		a->typeExp = mult_exp;
		a->operation.multExp.operator = operator;
		a->operation.multExp.left = c1;
		a->operation.multExp.right = c2;
	}else if(operator == '^'){
		a->typeExp = expon_exp;
		a->operation.expon.operator = operator;
		a->operation.expon.left = c1;
		a->operation.expon.right = c2;
	}
	else{
		printf("AHHHH Not Good\n");
		return NULL;
	}
	return a;
}

// This function runs through the AST and evaluates each level of expression parent, child nodes recursively
int eval(ast *a){
    int left;
    int right;
    int result = 0;
    if(a->typeExp == integer_exp){
    	result = a->operation.integerExp;
    }
    else if(a->typeExp == add_exp){
        left = eval(a->operation.addExp.left);
		right = eval(a->operation.addExp.right);
		result = left + right;
    }
    else if(a->typeExp == mult_exp){
    	left = eval(a->operation.multExp.left);
		right = eval(a->operation.multExp.right);
		result = left * right;
    }
    else if(a->typeExp == expon_exp){
    	int b = eval(a->operation.expon.left);
    	//printf("This is B %d\n", b);
    	int c = eval(a->operation.expon.right);
    	//printf("This is C %d\n", c);
    	int d = b;
    	for(int i = 0; i < c-1; i++){
    		//printf("current result %d\n", d);
    		d = d * b;
    	}
    	result = d;
    }
    return result;
}


