#include "arith.h"

ast * intExpression(int number){
	ast *a = malloc(sizeof(ast));
	a->typeExp = integer_exp;
	a->operation.integerExp = number;
	return a;
}

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
	}
	else{
		printf("AHHHH Not Good\n");
		return NULL;
	}
	return a;
}


