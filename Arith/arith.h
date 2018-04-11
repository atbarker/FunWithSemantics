#ifndef ARITH_H
#define ARITH_H

enum type{
    integer_exp = 0,
    add_exp = 1,
    mult_exp = 2
};

typedef struct exp{
    enum type typeExp; 
    union {
	int integerExp;
	struct { 
	    char operator;
	    struct exp* left;
	    struct exp* right;
	} addExp;
	struct {
	    char operator;
	    struct exp* left;
	    struct exp* right;
	} multExp;
    }operation;    
}ast;

//create an AST node that holds an integer expression
ast * intExpresstion(int number);
//create an AST node that performs an operation with two child ASTs
ast * arithExpression(char operator, ast* c1, ast* c2);

//evaluation, recursive, will evaluate an AST and return an integer
int eval(ast *a);

#endif
