/*
Author : Edwin Jose George
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include <unistd.h>

struct{char ch;int hold;}INPUT_BUFFER={' ',0};
int lineNumber = 1;

const char KEYWORD[][10]  = {"char","int","float","long","short","double","void","if","for","else","while","switch","struct","const"};
const char OPERATOR[][3]  = {"+" ,"-" ,"/" ,"*" ,"%" ,"<" ,">" ,"=" ,"|" ,"&", "!","++","--","||","&&", ",", ".","?",":"
														 "+=","-=","/=","*=","%=","<=",">=","==","|=","&=","!="};
const char PUNCTUATION[]  = ";{}[]()";

const int KEYWORD_SIZE = 14;
const int OPERATOR_SIZE = 30;
const int PUNCTUATION_SIZE = 7;

struct symbol_table{
	char symName[32];
	char type[20];
	struct symbol_table *next;
}*SYMTAB;

int is_keyword(char buffer[]){
	for(int i=0;i<KEYWORD_SIZE;i++){
		if(strcmp(KEYWORD[i],buffer)==1)
			return 1;
	}
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


int read_token(char buffer[32]){
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
		if((buffer[j] == ' ' || buffer[j]=='\t' || buffer[j]=='\n')){
			if(buffer[j]=='\n')lineNumber += 1;

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
					if(ch == '\n'){
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
				char ch2 = getchar();
				while(1){
					if(ch2 == EOF)return 0;
					if(ch2 == '\n')lineNumber+=1;
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

		//scaning keyword, identifiers, numbers, special symbols
		j++;
	}
	buffer[j+1] = '\0';
	return 1;
}

void main(){
	char buffer[32];
	while(read_token(buffer)){
		printf("%04d | \t %s\n",lineNumber,buffer);
		//sleep(1);
	}
}
