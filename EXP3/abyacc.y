%{
#include<stdio.h>
#include<stdlib.h>
int flag=0;
%}

%token A B NEWLINE OTHER

%%
stmt: A B NEWLINE {printf("Valid string\n");flag=1;return;};
%%

void main(){
	printf("Enter the string \n");
	yyparse();
	if(!flag){
		printf("INVALID string\n");
	}
}

void yyerror(){}
