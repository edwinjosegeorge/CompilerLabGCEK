//~~~~~~~~~~~~~~~~~~~~~~~~~defining token values of language~~~~~~~~~~~~~~~~~~~~

struct sys_token_info{
	char pattern[12];
	char type[20];
};

struct sys_token_info *new_resv_token(char pattern[],char type[]){
	struct sys_token_info *tmp = malloc(sizeof(struct sys_token_info));
	strcpy(tmp->pattern, pattern);
	strcpy(tmp->type,type);
	return tmp;
}

// stack that holds pre-defined tokens!
struct stack *RESV_WORDS = NULL;

void initialize_resv_token(){
	//setups the language specific tokens (except identifiers,numerials,strings)

	RESV_WORDS = push(RESV_WORDS,new_resv_token("#include","PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#define" ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#undef"  ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#ifdef"  ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#ifndef" ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#if"     ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#else"   ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#elif"   ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#endif"  ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#error"  ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#pragma" ,"PRE_PROCESSOR"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("#line"   ,"PRE_PROCESSOR"));

	RESV_WORDS = push(RESV_WORDS,new_resv_token("void"    ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("char"    ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("int"     ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("float"   ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("double"  ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("short"   ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("long"    ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("signed"  ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("unsigned","KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("if"      ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("else"    ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("switch"  ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("case"    ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("default" ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("for"     ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("while"   ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("do"      ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("break"   ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("continue","KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("return"  ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("auto"    ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("static"  ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("struct"  ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("union"   ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("typedef" ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("enum"    ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("extern"  ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("volatile","KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("sizeof"  ,"KEYWORD"));
	RESV_WORDS = push(RESV_WORDS,new_resv_token("const"  ,"KEYWORD"));

	//RESV_SYMBL = push(RESV_SYMBL,new_resv_token("//"  ,"CMT LINE"));
	//RESV_SYMBL = push(RESV_SYMBL,new_resv_token("/*"  ,"CMT M-LINE ST"));
	//RESV_SYMBL = push(RESV_SYMBL,new_resv_token("*/"  ,"CMT M-LINE END"));
	//RESV_SYMBL = push(RESV_SYMBL,new_resv_token("\'"  ,"CHAR CONST"));
	//RESV_SYMBL = push(RESV_SYMBL,new_resv_token("\""  ,"STRING CONST"));
	// The back-slash inside strings have overloaded meaning - escape sequence!
}

void distroy_resv_token(){
	struct stack *table = RESV_WORDS;
	while(table != NULL){
		free(table->info);
		table = pop(table);
	}
}

int is_keyword(char pattern[], char type[]){
	struct stack *resv_words = RESV_WORDS;
	struct sys_token_info *tkn = NULL;

	while(resv_words != NULL){
		tkn = resv_words->info;
		if(strcmp(tkn->pattern,pattern)==0){
			strcpy(type,tkn->type);
			return 1;
		}
		resv_words = resv_words->next;
	}
	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~handling identifiers~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int scan_identifier(char pattern, int *state){
	/*compare pattern on identifier rules.
	'state' denotes the DFA state matching identifer. auto update this variable
		if exact match   -> return  1
		if no match      -> return  0
	identifier = ( _ | alpha )( _ | alph-num )*
	identifier != RESV_SYMBL (needs to be check outside!)
	*/

	if((*state) == 0){
		if(pattern == '_'){(*state) = 1;return 1;}
		if(pattern >= 'A' && pattern <= 'Z'){(*state) = 1;return 1;}
		if(pattern >= 'a' && pattern <= 'z'){(*state) = 1;return 1;}

		(*state)=2;return 0;
	}
	if((*state) == 1){
		if(pattern == '_')return 1;
		if(pattern >= 'A' && pattern <= 'Z')return 1;
		if(pattern >= 'a' && pattern <= 'z')return 1;
		if(pattern >= '0' && pattern <= '9')return 1;

		(*state)=2;return 0;
	}
	if((*state) == 2)return 0;
}

int is_identifier(char pattern[],char type[]){
	/*Returns the acceptance info of identifier from the DFA.
		  returns  0 -> invalid
			returns  1 -> valid identifer
	*/

	int state = 0;
	for(int i=0;pattern[i]!='\0';i++){
		if(scan_identifier(pattern[i],&state) == 0)return 0;
	}

	if(is_keyword(pattern,type))return 0;

	strcpy(type,"IDENTIFIER");
	return 1;
}
