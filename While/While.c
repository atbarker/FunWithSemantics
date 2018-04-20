#include "While.h"
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

ast * variableExp(char name[20]){
    ast *a = malloc(sizeof(ast));
    a->typeExp = var_exp;
    //a->operation.variableExp = name;
    return a;
}

// Accepts parent and child nodes in an AST. Evaluates type of operation for the parent node. 
// The function then assigns children a position inside the AST parent node
ast * arithExpression(char operator, ast* c1, ast* c2){
	ast *a = malloc(sizeof(ast));
	if(operator == '+'){
		a->typeExp = arith_exp;
		a->operation.arithExp.operator = operator;
		a->operation.arithExp.left = c1;
		a->operation.arithExp.right = c2;
	}
	else if(operator == '*'){
		a->typeExp = arith_exp;
		a->operation.arithExp.operator = operator;
		a->operation.arithExp.left = c1;
		a->operation.arithExp.right = c2;
	}else if(operator == '^'){
		a->typeExp = arith_exp;
		a->operation.arithExp.operator = operator;
		a->operation.arithExp.left = c1;
		a->operation.arithExp.right = c2;
	}
	else{
		printf("AHHHH Not Good\n");
		return NULL;
	}
	return a;
}

ast * negExpression(char operator, ast* c1){
	ast *a = malloc(sizeof(ast));
	a->operation.negExp.operator = '~';
	a->operation.negExp.child = c1;
	return a;
}

ast * compExpression(char operator, ast *c1, ast *c2){
    ast *a = malloc(sizeof(ast));
    a->typeExp = comp_exp;
    a->operation.compCommand.left = c1;
    a->operation.compCommand.right = c2;
    return a;
}

ast * ifExpression(char operator, ast* condition, ast* c1, ast* c2){
    ast *a = malloc(sizeof(ast));
    a->typeExp = if_exp;
    a->operation.ifCommand.condition = condition;
    a->operation.ifCommand.body1 = c1;
    a->operation.ifCommand.body2 = c2;
    return a;
}

ast * whileExpression(char operator, ast* condition, ast* body){
    ast *a = malloc(sizeof(ast));
    a->typeExp = while_exp;
    a->operation.whileCommand.condition = condition;
    a->operation.whileCommand.body = body;
    return a;
}

ast * skipExpression(char operator, ast* c1){
    ast *a = malloc(sizeof(ast));
    a->typeExp = skip_exp;
    a->operation.skipCommand.child = c1;
    return a;
}

//handles variable assignment
ast * assignExpression(char operator, ast* variable, ast* expression){
    ast *a = malloc(sizeof(ast));
    a->typeExp = assign_exp;
    a->operation.assignCommand.variable = variable;
    a->operation.assignCommand.expression = expression;
    return a;
}	
     


// This function runs through the AST and evaluates each level of expression parent, child nodes recursively
int eval(ast *a){
    int left;
    int right;
    int cond;
    int result = 0;
    if(a->typeExp == integer_exp){
    	result = a->operation.integerExp;
    }
    else if(a->typeExp == arith_exp){
        left = eval(a->operation.arithExp.left);
		right = eval(a->operation.arithExp.right);
		char op = a->operation.arithExp.operator;
		if(op == '+'){
            result = left + right;
		}
		else if(op == '*'){
            result = left * right;
		}
		else if(op == '-'){
            result = left - right;
		}	
		else{
            printf("Eval failed at Arith\n");
		}
    }
    else if(a->typeExp == bool_exp){
    	left = eval(a->operation.boolean.left);
		right = eval(a->operation.boolean.right);
        char op = a->operation.boolean.operator;
		if(op == '='){
            result = left == right;
		}
		else if(op == '<'){
            result = left < right;
		}
		else if(op == '&'){
            result = left && right;
		}
		else if(op == '|'){
            result = left || right;
		}
		else{
			printf("Eval failed at Bool\n");
		}
	
    }
    else if(a->typeExp == skip_exp){
        //executes a skip
        eval(a->operation.skipCommand.child);

    }
    else if(a->typeExp == neg_exp){
        //negates a boolean
		left = eval(a->operation.negExp.child);
        if(left == 0){
            result = 1;
		}
		else{
	    result = 0;
		}	    
    }else if(a->typeExp == assign_exp){
        //enters into the state
		left = eval(a->operation.assignCommand.expression);
    }else if(a->typeExp == comp_exp){
        //evaluates a composition
		left = eval(a->operation.compCommand.left);
		right = eval(a->operation.compCommand.right);
    }else if(a->typeExp == if_exp){
        //evaluates an if
		cond = eval(a->operation.ifCommand.condition);
		if(cond == 1){
            result = eval(a->operation.ifCommand.body1);
		}
		else{
            result = eval(a->operation.ifCommand.body2);
		}
    }else if(a->typeExp == while_exp){
        //evaluates a loop
       if(a->operation.whileCommand.condition){
    		result = eval(a->operation.whileCommand.body);
		}
    }else if(a->typeExp == var_exp){
    	// int variableKey = insert(a->operation.assignCommand.variable, a->operation.assignCommand.expression);
    	//  
       
    }else{
        //error state, something went wrong
    }
    return result;
}

hashObject hashArray[500];

//hashing function
int hashKey(char *key){
	return 0;
}

// insert the hash object(variable key and value) into the array

void insert(char *key, char *value) {

	int hashIndex = hashKey(key);
	hashObject *store;
    if(&hashArray[hashIndex] == NULL){
    	store = malloc(sizeof(hashObject)); 
    	store->value = *value;
    	hashArray[hashIndex] = *store;
	}
	else{
		store = &hashArray[hashIndex]; 
		store->value = *value;
	}
}


