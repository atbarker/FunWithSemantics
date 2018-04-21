#ifndef WHILE_H
#define WHILE_H
//creates a marking system for which operation we are using in eval.
enum type{
    integer_exp = 0,
    arith_exp = 1,
    bool_exp = 2,
    skip_exp = 3,
    neg_exp = 4,
    assign_exp = 5,
    comp_exp = 6,
    if_exp = 7,
    while_exp = 8,
    var_exp = 9
};

enum commandType{
    skip_cmd = 1, // 'skip'
    assign_cmd = 2, //'x := 5'
    comp_cmd = 3, // 'c1 ; c2'
    if_cmd = 4,
    while_cmd = 5
};

// Using a union, this creates a struct , for the assessment of mult, add, and exponentiation. Called AST
typedef struct exp{
    enum type typeExp; 
    union {
	    int integerExp;
	    char *variableExp;
	    struct{
		char operator;
		struct exp* child;
	    } negExp;
	    struct { 
	        char operator;
	        struct exp* left;
	        struct exp* right;
	    } arithExp;
	    //in the boolean expression if the right child is null and the operator is '~' then we can assume it is a logical NOT
	    struct {
	    	char operator;
	    	struct exp* left;
	    	struct exp* right;
	    } boolean;
	    struct {
	    	char operator;
		enum commandType cmd;
	    	struct exp* child;
	    } skipCommand;
	    struct {
                char operator;
		enum commandType cmd;
		char *variable;
		struct exp* expression;
            } assignCommand;
	    struct {
	        char operator;
		enum commandType cmd;
		struct exp* left;
		struct exp* right;
	    } compCommand;
	    struct {
		char operator;
                enum commandType cmd;
		struct exp* condition;
		struct exp* body1;
		struct exp* body2;
	    } ifCommand;
	    struct {
		char operator;
		enum commandType cmd;
		struct exp* condition;
		struct exp* body;
	    } whileCommand;
    }operation;    
}ast;

typedef struct hashObj{
	int value;
}hashObject;

hashObject *hashArray[500];

//create an AST node that holds an integer expression
ast * intExpression(int number);
//variable name
ast * variableExp(char *name);
//create an AST node that performs an operation with two child ASTs
ast * arithExpression(char operator, ast* c1, ast* c2);
// create an AST node that performs a boolean evaluation
ast * booleanExpression(char operator, ast* c1, ast* c2);
// create an AST node that creates a "skip" node
ast * skipExpression(char operator, ast* c1);
// AST for an assignment operation
ast * assignExpression(char operator, char *variable, ast* expression);
// AST for a composition expression
ast * compExpression(char operator, ast* c1, ast* c2);
// AST for an if statement
ast * ifExpression(char operator, ast* condition, ast* c1, ast* c2);
// AST for a loop
ast * whileExpression(char operator, ast* condition, ast* body);
// evaluates the negation of a node
ast * negExpression(char operator, ast* c1);

//evaluation, recursive, will evaluate an AST and return an integer
int eval(ast *a);

int hashKey(char *key);

void insert(char *key, int value);

int fetch(char *key);
#endif
