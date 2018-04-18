#ifndef WHILE_H
#define WHILE_H
//creates a marking system for which operation we are using in eval.
enum type{
    integer_exp = 0,
    add_exp = 1,
    mult_exp = 2,
    expon_exp = 3,
    bool_exp = 4,
    command_exp = 5,
    neg_exp = 6
};
// Using a union, this creates a struct , for the assessment of mult, add, and exponentiation. Called AST
typedef struct exp{
    enum type typeExp; 
    union {
	    int integerExp;
	    int negExp;
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
	    struct {
	    	char operator;
	    	struct exp* left;
	    	struct exp* right;
	    } boolean;
	    struct {
	    	char operator;
	    	struct exp* left;
	    	struct exp* right;
	    } command;
    }operation;    
}ast;

//create an AST node that holds an integer expression
ast * intExpression(int number);
//create an AST node that performs an operation with two child ASTs
ast * arithExpression(char operator, ast* c1, ast* c2);
// create an AST node that performs a boolean evaluation
ast * boolExpression(char operator, ast* c1, ast* c2);
// create an AST node that performs a command evalutaion
ast * commandExpression(char operator, ast* c1, ast* c2);
// evaluates the negation of a node
ast * negExpression(char operator, ast* c1)

//evaluation, recursive, will evaluate an AST and return an integer
int eval(ast *a);

#endif
