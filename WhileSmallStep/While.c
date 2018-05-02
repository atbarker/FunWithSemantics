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

// Assessment of Right hand side of variable assignment
ast * variableExp(char *name){
    ast *a = malloc(sizeof(ast));
    a->typeExp = var_exp;
    a->operation.variableExp = name;
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
	}else if(operator == '-'){
		a->typeExp = arith_exp;
		a->operation.arithExp.operator = operator;
		a->operation.arithExp.left = c1;
		a->operation.arithExp.right = c2;
	}else if(operator == '/'){
		a->typeExp = arith_exp;
		a->operation.arithExp.operator = operator;
		a->operation.arithExp.left = c1;
		a->operation.arithExp.right = c2;
	}
	else{
		printf("AHHHH Not Good\n");
		return NULL;
	}
	c1->operation.arithExp.parent = a;
	c2->operation.arithExp.parent = a;
	return a;
}

ast * booleanExpression(char operator, ast *c1, ast *c2){
	ast *a = malloc(sizeof(ast));
	if(operator == '='){
		a->typeExp = bool_exp;
		a->operation.boolean.operator = operator;
		a->operation.boolean.left = c1;
		a->operation.boolean.right = c2;
	}
	else if(operator == '<'){
		a->typeExp = bool_exp;
		a->operation.boolean.operator = operator;
		a->operation.boolean.left = c1;
		a->operation.boolean.right = c2;
	}
	else if(operator == '&'){
		a->typeExp = bool_exp;
		a->operation.boolean.operator = operator;
		a->operation.boolean.left = c1;
		a->operation.boolean.right = c2;
	}
	else if(operator == '|'){
		a->typeExp = bool_exp;
		a->operation.boolean.operator = operator;
		a->operation.boolean.left = c1;
		a->operation.boolean.right = c2;
	}
	else{
		printf("Something is horribly wrong at boolean\n");
	}
	c1->operation.boolean.parent = a;
	c2->operation.boolean.parent = a;
	return a;
}

//Asssesment of a negation. Has one child.
ast * negExpression(char operator, ast* c1){
	ast *a = malloc(sizeof(ast));
	a->typeExp = neg_exp; 
	a->operation.negExp.operator = '~';
	a->operation.negExp.child = c1;
	c1->operation.negExp.parent = a;
	return a;
}

//Assesment of seq/ ";" operator. 
ast * compExpression(char operator, ast *c1, ast *c2){
    ast *a = malloc(sizeof(ast));
    a->typeExp = comp_exp;
    a->operation.compCommand.left = c1;
    a->operation.compCommand.right = c2;
    c1->operation.compCommand.parent = a;
    c2->operation.compCommand.parent = a;
    return a;
}

//Assessment of if-then statement.
ast * ifExpression(char operator, ast* condition, ast* c1, ast* c2){
    ast *a = malloc(sizeof(ast));
    a->typeExp = if_exp;
    a->operation.ifCommand.condition = condition;
    a->operation.ifCommand.body1 = c1;
    a->operation.ifCommand.body2 = c2;
    condition->operation.ifCommand.parent = a;
    c1->operation.ifCommand.parent = a;
    c2->operation.ifCommand.parent = a;
    return a;
}

//Assesment of While operation node.
ast * whileExpression(char operator, ast* condition, ast* body){
    ast *a = malloc(sizeof(ast));
    a->typeExp = while_exp;
    a->operation.whileCommand.condition = condition;
    a->operation.whileCommand.body = body;
    condition->operation.whileCommand.parent = a;
    body->operation.whileCommand.parent = a;
    return a;
}

//Assesment of skip node.
ast * skipExpression(char operator, ast* c1){
    ast *a = malloc(sizeof(ast));
    a->typeExp = skip_exp;
    a->operation.skipCommand.child = c1;
    c1->operation.skipCommand.parent = a;
    return a;
}

// Handles variable assignment. Combine L/R sides
ast * assignExpression(char operator, char *variable, ast* expression){
    ast *a = malloc(sizeof(ast));
    a->typeExp = assign_exp;
    a->operation.assignCommand.variable = variable;
    a->operation.assignCommand.expression = expression;
    expression->operation.assignCommand.parent = a;
    return a;
}	
     


// This function runs through the AST and evaluates each level of expression parent, child nodes recursively
int eval(ast *a, hashObject **hashArray){
    int left;
    int right;
    int cond;
    int result = 0;
    //printf("<");
    //printAST(a);
    //printf("> ->\n");
    if(a->typeExp == integer_exp){
    	result = a->operation.integerExp;
    }
    else if(a->typeExp == arith_exp){
	printASTTop(a);
        left = eval(a->operation.arithExp.left, hashArray);
		right = eval(a->operation.arithExp.right, hashArray);
		char op = a->operation.arithExp.operator;
		if(op == '+'){
            result = left + right;
		}
		else if(op == '*'){
            result = left * right;
		}
		else if(op == '-'){
            result = left - right;
		}else if(op == '/'){
	            if(right <= 0){
			    printf("No divide by zero\n");
			    return 0;
		    }
                    result = left / right;
		}	
		else{
            printf("Eval failed at Arith\n");
		}
    }
    else if(a->typeExp == bool_exp){
	printASTTop(a);
    	left = eval(a->operation.boolean.left, hashArray);
	right = eval(a->operation.boolean.right, hashArray);
        char op = a->operation.boolean.operator;
	if(op == '='){
            if(left == right){
	        result = 1;
	    }else{
                result = 0;
	    }
	}
	else if(op == '<'){
            if(left < right){
	        result = 1;
	    }else{
                result = 0;
	    }
	}
	else if(op == '&'){
            if(left & right){
	        result = 1;
	    }else{
                result = 0;
	    }
	}
	else if(op == '|'){
            if(left || right){
	        result = 1;
	    }else{
                result = 0;
	    }
	}
	else{
	    printf("Eval failed at Bool\n");
	}
	
    }
    else if(a->typeExp == skip_exp){
        //executes a skip
        //eval(a->operation.skipCommand.child);
        //print out the remaining AST
	printASTTop(a);
    }
    else if(a->typeExp == neg_exp){
        //negates a boolean
	printASTTop(a);
	left = eval(a->operation.negExp.child, hashArray);
        if(left == 0){
            result = 1;
	}
	else{
	    result = 0;
	}	    
    }else if(a->typeExp == assign_exp){
	printASTTop(a);
        //enters into the state
	left = eval(a->operation.assignCommand.expression, hashArray);
	insert(a->operation.assignCommand.variable, left, hashArray);
    }else if(a->typeExp == comp_exp){
        //evaluates a composition
	//traverse the AST
	printASTTop(a);
	left = eval(a->operation.compCommand.left, hashArray);
	right = eval(a->operation.compCommand.right, hashArray);
    }else if(a->typeExp == if_exp){
	printASTTop(a);
        //evaluates an if
	cond = eval(a->operation.ifCommand.condition, hashArray);
	if(cond == 1){
            result = eval(a->operation.ifCommand.body1, hashArray);
	}else{
            result = eval(a->operation.ifCommand.body2, hashArray);
	}
    }else if(a->typeExp == while_exp){
	printASTTop(a);
        //evaluates a loop
       int cond = eval(a->operation.whileCommand.condition, hashArray);
       //printf("condition %d\n", cond);
       if(cond == 1){
	     //printf("Executing loop\n");
    	     while(1){
		 eval(a->operation.whileCommand.body, hashArray);
		 cond = eval(a->operation.whileCommand.condition, hashArray);
		 if(cond != 1){break;}
		 //printf("continuing\n");
             }
       }
    }else if(a->typeExp == var_exp){
	result = fetch(a->operation.variableExp, hashArray);   
    }else{
        //error state, something went wrong
    }
    return result;
}

//Array to store hashtable for variables


//Hashing function for variable assignment.
//Hash function is modified djb2 found http://www.cs.dartmouth.edu/~campbell/cs50/hash.c
int hashKey(char *key){
	int hash = 5381;
	int c;
	while((c = *key++) != 0){
		hash = ((hash << 5) + hash) + c; 
	}
	return hash %= 500; 
}

//Inserts the hash object(variable expression) into the array

void insert(char *key, int value, hashObject **hashArray) {

	int hashIndex = hashKey(key);
	hashObject *store;
        if(hashArray[hashIndex] == NULL){
    	    store = calloc(1, sizeof(hashObject)); 
    	    store->value = value;
    	    hashArray[hashIndex] = store;
    	    //printf("New object stored at index: %d\n",hashIndex);
	}
	else{ 
		hashArray[hashIndex]->value = value;
		//printf("New value stored at: %d\n", hashIndex);
	}
}

int fetch(char *key, hashObject **hashArray){
	 int hashIndex = hashKey(key);
	 hashObject *store;
	 if(hashArray[hashIndex] != NULL){
		//printf("Object retrieved at index %d\n", hashIndex);
	 	return hashArray[hashIndex] -> value;
	 }
	 else{
	 	printf("Object not found\n");
	 }
	 return 0;
}

int dumpHash(hashObject **hashArray){
    return 0;
}

int printAST(ast *a){
    //if a composition print the left and then right
    if(a->typeExp == comp_exp){
        printAST(a->operation.compCommand.left);
	printf(";");
        printAST(a->operation.compCommand.right);
    }
    //if a variable assignment
    else if(a->typeExp == assign_exp){
        printf(a->operation.assignCommand.variable);
	printf(":=");
	printAST(a->operation.assignCommand.expression);
    }
    //if a variable statement
    else if(a->typeExp == var_exp){
        printf(a->operation.variableExp);
    }
    //if a skip
    else if(a->typeExp == skip_exp){
        printf("skip");
    }
    //if an if
    else if(a->typeExp == if_exp){
        printf("if(");
        printAST(a->operation.ifCommand.condition);
        printf(") ");
        printAST(a->operation.ifCommand.body1);
        printf(" else ");
        printAST(a->operation.ifCommand.body2);	
    }
    //if a while
    else if(a->typeExp == while_exp){
        printf("while(");
	printAST(a->operation.whileCommand.condition);
	printf(") ");
	printAST(a->operation.whileCommand.body);
    }
    else if(a->typeExp == integer_exp){
        printf("%d", a->operation.integerExp);
    }
    else if(a->typeExp == arith_exp){
        printAST(a->operation.arithExp.left);
        printf("%c", a->operation.arithExp.operator);
        printAST(a->operation.arithExp.right);	
    }
    else if(a->typeExp == bool_exp){
	//if(a->operation.boolean.parent){
	//if(a->operation.boolean.parent->typeExp == if_exp){
            printAST(a->operation.boolean.left);
	    printf("%c", a->operation.boolean.operator);
	    printAST(a->operation.boolean.right);
	//}
	//}
    }
    else if(a->typeExp == neg_exp){
        printf("~");
	printAST(a->operation.negExp.child);
    }
    else{

    }
    return 0;
}

void printASTTop(ast *a){
    printf("< ");
    printAST(a);
    printf(" >  ->\n");
}



