%{
#include<stdio.h>
#include<stdlib.h>
%}

%token IDENTIFIER NUMBER OPERATOR OTHER END OPEN_BKT CLOSE_BKT

%%
EXPR: EXPR END {printf("VALID expression \n");return;}
    | IDENTIFIER
    | NUMBER
    | OPEN_BKT EXPR CLOSE_BKT
    | EXPR OPERATOR EXPR ;
%%

void main(){
	printf("Enter the expression\n");
	yyparse();
}

void yyerror(){
	printf("INVALID expression\n");
}
