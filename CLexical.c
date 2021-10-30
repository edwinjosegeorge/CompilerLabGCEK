/*
Author : Edwin Jose George
Input stream should be LF formated for line number to work
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>

struct{char ch;int hold;}INPUT_BUFFER={' ',0};
int lineNumber = 1;

const char PREPROCESSOR[][10] = {"#include","#define","#undef", "#ifdef" ,"#ifndef", "#if", "#else", "#elif", "#endif", "#error","#pragma"};
const char KEYWORD[][10]  = {"char","int","float","long","short","double","void","if","for","else","while","switch","struct","const"};
const char OPERATOR[][3]  = {"+" ,"-" ,"/" ,"*" ,"%" ,"<" ,">" ,"=" ,"|" ,"&", "!","++","--","||","&&", ",", ".","?",":","+=","-=","/=","*=","%=","<=",">=","==","|=","&=","!=","->"};
const char PUNCTUATION[]  = ";{}[]()";

const int PREPROCESSOR_SIZE = 11;
const int KEYWORD_SIZE = 14;
const int OPERATOR_SIZE = 31;
const int PUNCTUATION_SIZE = 7;

struct symbol_table{
	char symName[32];
	char type[20];
	struct symbol_table *next;
}*SYMTAB;


int is_preprocessor(char buffer[32]){
	for(int op = 0; op<PREPROCESSOR_SIZE; op++)
			if(strcmp(buffer,PREPROCESSOR[op])==0)return 1;
	return 0;
}

int is_keyword(char buffer[32]){
	for(int i=0;i<KEYWORD_SIZE;i++)
		if(strcmp(KEYWORD[i],buffer)==0)return 1;
	return 0;
}

int is_operator(char c1, char c2){
	for(int op = 0; op<OPERATOR_SIZE; op++){
		if(c1 == OPERATOR[op][0]){
			if(c2 == '\0')return 1;
			if(c2 == OPERATOR[op][1])return 1;
		}
	}
	return 0;
}

int is_punctuation(char c1){
	for(int op = 0; op<PUNCTUATION_SIZE; op++){
		if(c1 == PUNCTUATION[op])return 1;
	}
	return 0;
}

int is_numeral(char lexeme[]){

	//decimal
	if(lexeme[0] != '0'){
		for(int i=0;lexeme[i]!='\0';i++){
			if(!isdigit(lexeme[i]))return 0;
		}
		return 1;
	}

	//hexal
	if(lexeme[1]=='x' || lexeme[1]=='X'){
		for(int i=2;lexeme[i]!='\0';i++){
			if(!(isdigit(lexeme[i]) || ('A'<=lexeme[i] && lexeme[i]<='F') || ('a'<=lexeme[i] && lexeme[i]<='f'))){
				return 0;
			}
		}
		return 1;
	}

	//binary
	if(lexeme[1]=='b' || lexeme[1]=='B'){
		for(int i=2;lexeme[i]!='\0';i++){
			if('0'!=lexeme[i] && '1'!=lexeme[i]){
				return 0;
			}
		}
		return 1;
	}

	//octal
	for(int i=1;lexeme[i]!='\0';i++){
		if(lexeme[i] >'7' || lexeme[i] < '0'){
			return 0;
		}
	}
	return 1;

}

int is_identifier(char lexeme[]){
	if(!( isalpha(lexeme[0]) || lexeme[0] == '_')){
		return 0;
	}
	for(int i=1;lexeme[i]!='\0';i++){
		if(!( isalnum(lexeme[i]) || lexeme[i] == '_')){
			return 0;
		}
	}
	return 1;
}

int add_SYMTAB(struct symbol_table entry){
	//Add a symbol table entry, success = 1

	struct symbol_table *ptr=SYMTAB;
	while(ptr != NULL){  //search for duplicate entery!
		if(strcmp(ptr->symName,entry.symName)==1){
			printf("Duplicate entery for %s at line %d",entry.symName,lineNumber);
			return 0;
		}
		ptr = ptr->next;
	}
	if(SYMTAB == NULL){
		SYMTAB == malloc(sizeof(struct symbol_table));
		SYMTAB->next = NULL;
	}else{
		SYMTAB->next = malloc(sizeof(struct symbol_table));
		SYMTAB->next->next = SYMTAB;
		SYMTAB = SYMTAB->next;
	}
	strcpy(SYMTAB->symName,entry.symName);
	strcpy(SYMTAB->type,entry.type);
	return 1;
}

void print_symbol_table(){
	printf("+");for(int i=0;i<34;i++)printf("-");printf("+");
	printf("+");for(int i=0;i<34;i++)printf("-");printf("+\n");
	printf("| %32s | %32s |\n","symName","type");
	printf("+");for(int i=0;i<34;i++)printf("-");printf("+");
	printf("+");for(int i=0;i<34;i++)printf("-");printf("+\n");

	struct symbol_table *ptr=SYMTAB;
	while(ptr!=NULL){
		printf("| %32s | %32s |\n",ptr->symName,ptr->type);
	}
	printf("+");for(int i=0;i<34;i++)printf("-");printf("+");
	printf("+");for(int i=0;i<34;i++)printf("-");printf("+\n");
}

void delete_symbol_table(){
	struct symbol_table *ptr;
	while(SYMTAB!=NULL){
		ptr = SYMTAB->next;
		free(SYMTAB);
		SYMTAB = ptr;
	}
}

int read_lexeme(char buffer[32]){
	//read a valid single token (max size is 32, won't go beyond that!)
	int j = 0;
	buffer[0] = '\0';
	buffer[1] = '\0';
	buffer[2] = '\0';

	while(1){
		if(INPUT_BUFFER.hold){
			buffer[j] = INPUT_BUFFER.ch;
			INPUT_BUFFER.hold = 0;
		}
		else buffer[j] = getchar();
		buffer[j+1] = '\0';
		if(buffer[j]==EOF){buffer[j]='\0';return 0;}

		//handle the white spaces
		if((buffer[j] == ' ' || buffer[j]=='\t' || buffer[j]=='\n' || buffer[j]=='\r')){
			if(buffer[j]=='\n' || buffer[j]=='\r')lineNumber += 1;

			if(j == 0)continue; //ignore inital white spaces
			else{ //found end of a token
				buffer[j] = '\0';
				return 1;
			}
		}

		//handle the punctuation symbols
		if(is_punctuation(buffer[j])){
			if(j!=0){//it marks end of previous token
				INPUT_BUFFER.ch = buffer[j];
				INPUT_BUFFER.hold = 1;
				buffer[j] = '\0';
				return 1;
			}
			buffer[j+1] = '\0';
			return 1;
		}

		if(buffer[j] == '"' || buffer[j] == '\'' ){ //reading string/charactor stream
			if(j!=0){//it marks end of previous token
				INPUT_BUFFER.ch = buffer[j];
				INPUT_BUFFER.hold = 1;
				buffer[j] = '\0';
				return 1;
			}
			int end = j;
			do{
				buffer[++j] = getchar();
				buffer[j+1] = '\0';
				if(buffer[j]==EOF){buffer[j]='\0';return 0;}

				if(buffer[j] == '\\'){ //escape charactor
					buffer[++j] = getchar();
					buffer[j+1] = '\0';
					if(buffer[j]==EOF){buffer[j]='\0';return 0;}
					buffer[++j] = getchar();
					buffer[j+1] = '\0';
					if(buffer[j]==EOF){buffer[j]='\0';return 0;}
				}
			}while(buffer[j]!=buffer[end]);
			return 1;
		}

		if(is_operator(buffer[j],'\0')){
			if(j!=0){//it marks end of previous token
				INPUT_BUFFER.ch = buffer[j];
				INPUT_BUFFER.hold = 1;
				buffer[j] = '\0';
				return 1;
			}

			buffer[++j] = getchar();
			buffer[j+1] = '\0';
			if(buffer[j]==EOF){buffer[j]='\0';return 0;}

			if(is_operator(buffer[j-1],buffer[j])){
				buffer[j+1]='\0';
			}
			else if(buffer[j-1]=='/' && buffer[j]=='/'){//skip single-line comments
				j -= 1;
				buffer[j] = '\0';
				char ch = getchar();
				while(1){
					if(ch == EOF)return 0;
					if(ch == '\n'|| ch =='\r'){
						lineNumber += 1;
						break;
					}
					ch = getchar();
				}
				continue;
			}
			else if(buffer[j-1]=='/' && buffer[j]=='*'){//skip multi-line comments
				j -= 1;
				buffer[j] = '\0';
				char ch1 = getchar();
				if(ch1 == EOF)return 0;
				if(ch1 == '\n'|| ch1=='\r')lineNumber+=1;
				char ch2 = getchar();
				while(1){
					if(ch2 == EOF)return 0;
					if(ch2 == '\n'|| ch2=='\r')lineNumber+=1;
					if(ch1 == '*' && ch2 == '/')break;
					ch1 = ch2;
					ch2 = getchar();
				}
				continue;
			}
			else{//it marks end of previous token
				INPUT_BUFFER.ch = buffer[j];
				INPUT_BUFFER.hold = 1;
				buffer[j] = '\0';
			}
			return 1;
		}

		//scaning keyword, identifiers, numbers, constants, special symbols
		j++;
	}
	buffer[j+1] = '\0';
	return 1;
}

char* tag_lexeme(char lexeme[32]){
	if(is_preprocessor(lexeme))return "PREPROCESSOR";
	if(is_keyword(lexeme))return "KEYWORD";
	if(is_operator(lexeme[0],lexeme[1]))return "OPERATOR SYM";
	if(is_punctuation(lexeme[0]))return "PUNCTUATION SYM";
	if(is_numeral(lexeme))return "NUMBER CONST";
	if(is_identifier(lexeme))return "IDENTIFIER";

	int size = strlen(lexeme);
	if((lexeme[0] == '\'' && lexeme[size-1]=='\'')||(lexeme[0] == '\"' && lexeme[size-1]=='\"'))
		return "STRING CONST";
	return "UN-IDENTIFIED";
}

void main(){
	char lexeme[32];
	int float_check = 0;
	char float_buff[32];
	char line_buff;
	while(read_lexeme(lexeme)){
		if(float_check!=0 && line_buff!=lineNumber){
			if(float_check == 1)printf("%4d | %20s | %s\n",line_buff,tag_lexeme(float_buff),float_buff);
			else printf("%4d | %20s | %s\n",line_buff,"FLOAT CONST",float_buff);

			float_check = 0;
		}

		if(is_numeral(lexeme)){
			if(float_check==0){//start float buffer
				float_check=1;
				strcpy(float_buff,lexeme);
				line_buff = lineNumber;
			}
			else if(float_check == 1){
				printf("%4d | %20s | %s\n",line_buff,tag_lexeme(float_buff),float_buff);

				strcpy(float_buff,lexeme);
				line_buff = lineNumber;
			}
			else if(float_check == 2){ //caught the float
				float_check = 0;
				strcat(float_buff,lexeme);
				printf("%4d | %20s | %s\n",lineNumber,"FLOAT CONST",float_buff);
			}
			continue;
		}
		else if(lexeme[0]=='.'){
			if(float_check==0){
				float_check == 2;
				strcpy(float_buff,lexeme);
				line_buff = lineNumber;
			}
			else if(float_check == 1){
				float_check = 2;
				strcat(float_buff,".");
			}
			else if(float_check == 2){
				printf("%4d | %20s | %s\n",line_buff,"FLOAT CONST",float_buff);

				float_check == 2;
				strcpy(float_buff,lexeme);
				line_buff = lineNumber;
			}
			continue;
		}
		else if(float_check !=0){
			if(float_check == 1)printf("%4d | %20s | %s\n",line_buff,tag_lexeme(float_buff),float_buff);
			else printf("%4d | %20s | %s\n",line_buff,"FLOAT CONST",float_buff);

			float_check = 0;
		}
		printf("%4d | %20s | %s\n",lineNumber,tag_lexeme(lexeme),lexeme);
	}
	if(float_check == 1)printf("%4d | %20s | %s\n",line_buff,tag_lexeme(float_buff),float_buff);
	else if (float_check == 2) printf("%4d | %20s | %s\n",line_buff,"FLOAT CONST",float_buff);

	if(lexeme[0]!='\0')
		printf("%4d | %20s | %s\n",lineNumber,tag_lexeme(lexeme),lexeme);
}
