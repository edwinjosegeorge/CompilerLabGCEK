%{
#include<stdio.h>
#include<stdlib.h>
int flag=0;
%}

%token IDENTIFIER NUMBER OPERATOR OTHER END OPEN_BKT CLOSE_BKT

%%
EXPR: EXPR END {printf("VALID expression\n");flag=1;return;}
    | IDENTIFIER                {}
    | NUMBER                    {}
    | OPEN_BKT EXPR CLOSE_BKT   {}
    | EXPR OPERATOR EXPR        {};
%%

void main(){
	printf("Enter the expression\n");
	yyparse();
	if(!flag){
		printf("INVALID expression\n");
	}
}

void yyerror(){}
