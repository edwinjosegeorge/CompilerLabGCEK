%{
#include<stdio.h>
#include<stdlib.h>
%}

%token letter digit NEWLINE OTHER

%%
F_VAR: letter VAR NEWLINE {printf("Valid variable\n");return;};
VAR: VAR letter | VAR digit | {};
%%

void main(){
	printf("Enter the variable \n");
	yyparse();
}

void yyerror(){
	printf("INVALID variable\n");
}
