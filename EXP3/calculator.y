%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
%}

%left '+' '-'
%left '*' '/' '%'
%right '^'
%token '(' ')'
%token NUMBER OTHER END

%%
TOTEXP: EXPR END        { printf("Result is : %d\n",$1); return;};
EXPR: NUMBER            { $$ = $1; }
    | '(' EXPR ')'      { $$ = $2; }
	  | EXPR '+' EXPR     { $$ = $1 + $3; }
	  | EXPR '-' EXPR     { $$ = $1 - $3; }
	  | EXPR '*' EXPR     { $$ = $1 * $3; }
	  | EXPR '/' EXPR     { if($3 == 0){
                            printf("Division by zero error\n");
          									return 0;
								          }
                          $$ = $1 / $3;
                        }
	  | EXPR '%' EXPR     { if($3 == 0){
									          printf("Division by zero error\n");
                            return 0;
                          }
                          $$ = $1 % $3;
                        }
	  | EXPR '^' EXPR     { $$ = pow($1,$3); };	
%%

void main(){
	printf("YACC calculator\n");
	printf("Supported symbols: + - * / ^ %\n");
	printf("Warning: result reduced to integer type!\n\n");
	printf("Enter the integer expression: ");
	yyparse();
}

void yyerror(){
	printf("INVALID expression\n");
}
