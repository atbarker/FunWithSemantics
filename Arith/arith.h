#ifndef ARITH_H
#define ARITH_H
//creates a marking system for which operation we are using in eval.
enum type{
    integer_exp = 0,
    add_exp = 1,
    mult_exp = 2,
    expon_exp = 3
};
// Using a union, this creates a struct , for the assessment of mult, add, and exponentiation. Called AST
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
	    struct {
            char operator;
	        struct exp* left;
	        struct exp* right;
	    } expon;
    }operation;    
}ast;

//create an AST node that holds an integer expression
ast * intExpression(int number);
//create an AST node that performs an operation with two child ASTs
ast * arithExpression(char operator, ast* c1, ast* c2);

//evaluation, recursive, will evaluate an AST and return an integer
int eval(ast *a);

#endif
