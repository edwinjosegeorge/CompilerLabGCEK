/*
Author : Edwin Jose George
Input stream should be CRLF formated for line number to work
*/
%{
#include <stdlib.h>
#include "stack.h"
#include "definition.h"
char type[30];
int lineNo = 1;
FILE *fp;

void update_line(char pattern[]){
  for(int i=0;pattern[i]!='\0';i++){
    if(pattern[i]=='\n')lineNo++;
  }
}
void exit_error(char pattern[]){
  printf("ERROR at line %d : cannot detect lexeme | %s\n",lineNo,pattern);
  fclose(fp);
  exit(1);
}
%}

%%
("\"")(("\\"(.|" "|\n|\r\t))|[^\\\n\r\t])*("\"") {
  printf("%4d | %20s | %s\n",lineNo,"STRING CONST",yytext);
  update_line(yytext);
}

("\'")(("\\"(.|" "|\n|\r\t))|[^\\\n\r\t])*("\'") {
  printf("%4d | %20s | %s\n",lineNo,"CHAR CONST",yytext);
  update_line(yytext);
}

"//".* {
  printf("%4d | %20s | %s\n",lineNo,"SINGLE_LINE_COMMENT",yytext);
  update_line(yytext);
}

"/*"([^*]|\*+[^*/])*\*+"/" {
  printf("%4d | %20s | %s\n",lineNo,"MULTI_LINE_COMMENT",yytext);
  update_line(yytext);
}

[#_a-zA-Z][_a-zA-Z0-9]* {
  if(is_keyword(yytext,type));
  else if(is_identifier(yytext,type));
  else exit_error(yytext);
  printf("%4d | %20s | %s\n",lineNo,type,yytext);
}

[+-]?[0][Bb][01]+ {
  printf("%4d | %20s | %s\n",lineNo,"BINARY CONST",yytext);
}
[+-]?[0][Xx][0-9A-Fa-f]+ {
  printf("%4d | %20s | %s\n",lineNo,"HEXADECIMAL CONST",yytext);
}
[+-]?[0][0-7]+ {
  printf("%4d | %20s | %s\n",lineNo,"OCTAL CONST",yytext);
}
[+-]?[0]+ {
  printf("%4d | %20s | %s\n",lineNo,"DECIMAL CONST",yytext);
}
[+-]?[1-9][0-9]*[LlUu]? {
  printf("%4d | %20s | %s\n",lineNo,"DECIMAL CONST",yytext);
}
[+-]?(("."[0-9])|([0-9]+"."))[0-9]* {
  printf("%4d | %20s | %s\n",lineNo,"FLOAT CONST",yytext);
}
[+-]?[0-9]+[Ee][+-]?[0-9]+ {
  printf("%4d | %20s | %s\n",lineNo,"EXPONENT CONST",yytext);
}
[+-]?(("."[0-9])|([0-9]+"."))[0-9]*[Ee][+-]?[0-9]+ {
  printf("%4d | %20s | %s\n",lineNo,"EXPONENT CONST",yytext);
}

[+-]?[0-9][0-9A-Za-z\.]* {exit_error(yytext);}

">>="   {printf("%4d | %20s | %s\n",lineNo,"SHIFT_RIGHT_EQUAL",yytext);}
"<<="   {printf("%4d | %20s | %s\n",lineNo,"SHIFT_LEFT_EQUAL",yytext);}
"++"  {printf("%4d | %20s | %s\n",lineNo,"INC",yytext);}
"--"  {printf("%4d | %20s | %s\n",lineNo,"DEC",yytext);}
">="  {printf("%4d | %20s | %s\n",lineNo,"GREATER_THAN_EQUAL",yytext);}
"<="  {printf("%4d | %20s | %s\n",lineNo,"LESS_THAN_EQUAL",yytext);}
"=="  {printf("%4d | %20s | %s\n",lineNo,"DOUBLE_EQUAL",yytext);}
"!="  {printf("%4d | %20s | %s\n",lineNo,"NOT_EQUAL",yytext);}
"&&"  {printf("%4d | %20s | %s\n",lineNo,"DOUBLE_AMP",yytext);}
"||"  {printf("%4d | %20s | %s\n",lineNo,"DOUBLE_PIPE",yytext);}
">>"  {printf("%4d | %20s | %s\n",lineNo,"SHIFT_RIGHT",yytext);}
"<<"  {printf("%4d | %20s | %s\n",lineNo,"SHIFT_LEFT",yytext);}
"+="  {printf("%4d | %20s | %s\n",lineNo,"PLUS_EQUAL",yytext);}
"-="  {printf("%4d | %20s | %s\n",lineNo,"MINUS_EQUAL",yytext);}
"*="  {printf("%4d | %20s | %s\n",lineNo,"ASTERISK_EQUAL",yytext);}
"/="  {printf("%4d | %20s | %s\n",lineNo,"SLASH_EQUAL",yytext);}
"%="  {printf("%4d | %20s | %s\n",lineNo,"MODULO_EQUAL",yytext);}
"|="  {printf("%4d | %20s | %s\n",lineNo,"PIPE_EQUAL",yytext);}
"&="  {printf("%4d | %20s | %s\n",lineNo,"AMP_EQUAL",yytext);}
"~="  {printf("%4d | %20s | %s\n",lineNo,"TILDE_EQUAL",yytext);}
"^="  {printf("%4d | %20s | %s\n",lineNo,"CAP_EQUAL",yytext);}
"+" {printf("%4d | %20s | %s\n",lineNo,"PLUS",yytext);}
"-" {printf("%4d | %20s | %s\n",lineNo,"MINUS",yytext);}
"*" {printf("%4d | %20s | %s\n",lineNo,"ASTERISK",yytext);}
"%" {printf("%4d | %20s | %s\n",lineNo,"MODULO",yytext);}
"/" {printf("%4d | %20s | %s\n",lineNo,"SLASH",yytext);}
">" {printf("%4d | %20s | %s\n",lineNo,"GREATER_THAN",yytext);}
"<" {printf("%4d | %20s | %s\n",lineNo,"LESS_THAN",yytext);}
"!" {printf("%4d | %20s | %s\n",lineNo,"EXCLAMATION",yytext);}
"|" {printf("%4d | %20s | %s\n",lineNo,"SINGLE_PIPE",yytext);}
"&" {printf("%4d | %20s | %s\n",lineNo,"SINGLE_AMP",yytext);}
"~" {printf("%4d | %20s | %s\n",lineNo,"TILDE",yytext);}
"^" {printf("%4d | %20s | %s\n",lineNo,"CAP",yytext);}
"," {printf("%4d | %20s | %s\n",lineNo,"COMMA",yytext);}
"." {printf("%4d | %20s | %s\n",lineNo,"DOT",yytext);}
"?" {printf("%4d | %20s | %s\n",lineNo,"QUES_MARK",yytext);}
":" {printf("%4d | %20s | %s\n",lineNo,"COLON",yytext);}
"{" {printf("%4d | %20s | %s\n",lineNo,"CURLY_BKT_OPEN",yytext);}
"}" {printf("%4d | %20s | %s\n",lineNo,"CURLY_BKT_CLOSE",yytext);}
"(" {printf("%4d | %20s | %s\n",lineNo,"PARANTHESIS_OPEN",yytext);}
")" {printf("%4d | %20s | %s\n",lineNo,"PARANTHESIS_CLOSE",yytext);}
"[" {printf("%4d | %20s | %s\n",lineNo,"SQUARE_BKT_OPEN",yytext);}
"]" {printf("%4d | %20s | %s\n",lineNo,"SQUARE_BKT_CLOSE",yytext);}
";" {printf("%4d | %20s | %s\n",lineNo,"SEMICOLON",yytext);}
"=" {printf("%4d | %20s | %s\n",lineNo,"EQUAL",yytext);}
(" "|\t|\n|\r|"\\"(.|\n))* {update_line(yytext);}
.	 {printf("unidentified %s at line %d\n",yytext,lineNo);}
%%

int yywrap(){}
void main(int argc, char** argv){
	if(argc > 1){
		if((fp=fopen(argv[1], "r"))==NULL) {
	    printf("Cannot open file %s.\n",argv[1]);
	    exit(1);
	  }
		printf("Reading the file %s\n\n",argv[1]);
	}
  else{
    puts("No filename was given.\n");
		exit(1);
	}

	initialize_resv_token();
	yyin = fp;
  yylex();
	fclose(fp);
	distroy_resv_token();
}
