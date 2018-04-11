#ifndef ARITH_H
#define ARITH_H

enum type{
    integer_exp = 1,
    add_exp = 1,
    mult_exp = 2
};

typedef struct exp{
    enum type; 
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

//some sort of constructor

//evaluation, recursive
int eval();

#endif
