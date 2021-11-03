//~~~~~~~~~~~~~~~~~~~~~~~~~defining constants of language~~~~~~~~~~~~~~~~~~~~~~~
#define NEWLINE '\n'
#define TAB '\t'
#define SPACE ' '
#define CARRIAGE '\r'


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
struct stack *RESV_SYMBL = NULL;

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("+"   ,"PLUS"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("-"   ,"MINUS"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("*"   ,"ASTERISK"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("%"   ,"MODULO"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("/"   ,"SLASH"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("++"  ,"INC"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("--"  ,"DEC"));

	RESV_SYMBL = push(RESV_SYMBL,new_resv_token(">"   ,"GREATER_THAN"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token(">="  ,"GREATER_THAN_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("<"   ,"LESS_THAN"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("<="  ,"LESS_THAN_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("=="  ,"DOUBLE_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("!="  ,"NOT_EQUAL"));

	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("!"   ,"EXCLAMATION"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("&&"  ,"DOUBLE_AMP"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("||"  ,"DOUBLE_PIPE"));

	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("|"   ,"SINGLE_PIPE"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("&"   ,"SINGLE_AMP"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token(">>"  ,"SHIFT_RIGHT"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("<<"  ,"SHIFT_LEFT"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("~"   ,"TILDE"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("^"   ,"CAP"));

	RESV_SYMBL = push(RESV_SYMBL,new_resv_token(","   ,"COMMA"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("."   ,"DOT"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("?"   ,"QUES_MARK"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token(":"   ,"COLON"));

	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("{"   ,"CURLY_BKT_OPEN"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("}"   ,"CURLY_BKT_CLOSE"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("("   ,"PARANTHESIS_OPEN"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token(")"   ,"PARANTHESIS_CLOSE"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("["   ,"SQUARE_BKT_OPEN"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("]"   ,"SQUARE_BKT_CLOSE"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token(";"   ,"SEMICOLON"));

	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("="   ,"EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("+="  ,"PLUS_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("-="  ,"MINUS_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("*="  ,"ASTERISK_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("/="  ,"SLASH_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("%="  ,"MODULO_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("|="  ,"PIPE_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("&="  ,"AMP_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token(">>=" ,"SHIFT_RIGHT_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("<<=" ,"SHIFT_LEFT_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("~="  ,"TILDE_EQUAL"));
	RESV_SYMBL = push(RESV_SYMBL,new_resv_token("^="  ,"CAP_EQUAL"));

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

	table = RESV_SYMBL;
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

int is_symbol(char pattern[], char type[]){
	/*Returns the acceptance info of sybmols
		  returns  0 -> no valid operator found
			returns  1 -> valid operator found
			returns -1 -> partial match
	*/
	struct stack *resv_symbols = NULL;
	struct sys_token_info *tkn = NULL;
	int ret_val = 0,partial=0,i=0;
	int len_pat = strlen(pattern);
	int len_tkn_pat;

	for(resv_symbols=RESV_SYMBL; resv_symbols!=NULL;
			resv_symbols=resv_symbols->next){
		tkn = resv_symbols->info;

		if(strcmp(pattern,tkn->pattern)==0){
			strcpy(type,tkn->type);
			return 1;
		}

		len_tkn_pat = strlen(tkn->pattern);
		if(len_tkn_pat <= len_pat)continue;

		partial = 0;
		for(i=0; i<len_pat; i++){
			if(pattern[i] == tkn->pattern[i])partial = 1;
			else{partial=0;break;}
		}
		if(partial==1)ret_val=-1;
	}
	return ret_val;
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
//~~~~~~~~~~~~~~~~~~~~~~~~~handling string/char/comment~~~~~~~~~~~~~~~~~~~~~~~~~
int scan_stream(char pattern, int*state){
	/*identifies stream of char/string const, single/multi comments, esc sequence
	returns  1 -> reading the stream
	returns  0 -> not reading the stream
	returns -1 -> waiting for 1 more char
	'state' denotes the DFA state matching stream. auto updates this variable
	*/
	if((*state) == 0){
		if(pattern == '\''){(*state)=1; return  1;}
		if(pattern == '\"'){(*state)=4; return  1;}
		if(pattern == '/' ){(*state)=7; return -1;}
		if(pattern == '\\'){(*state)=14;return  1;}
		(*state)=12;return 0;
	}
	if((*state) == 1){
		if(pattern == '\\'){(*state)=2;return 1;}
		if(pattern == '\''){(*state)=3;return 0;}
		if(pattern == NEWLINE || pattern == CARRIAGE){(*state)=12;return 0;}
		return 1;
	}
	if((*state) == 2){(*state)=1;return 1;}
	if((*state) == 3)return 0;
	if((*state) == 4){
		if(pattern == '\\'){(*state)=5;return 1;}
		if(pattern == '\"'){(*state)=6;return 0;}
		if(pattern == NEWLINE || pattern == CARRIAGE){(*state)=12;return 0;}
		return 1;
	}
	if((*state) == 5){(*state)=4;return 1;}
	if((*state) == 6)return 0;
	if((*state) == 7){
		if(pattern == '/'){(*state)=8 ;return 1;}
		if(pattern == '*'){(*state)=10;return 1;}
		(*state) = 12;return 0;
	}
	if((*state) == 8){
		if(pattern == NEWLINE){(*state)=9;return 0;}
		if(pattern == '\\'){(*state)=13;return 1;}
		return 1;
	}
	if((*state) == 9 )return 0;
	if((*state) == 10){
		if(pattern == '*'){(*state)=11;return 1;}
		return 1;
	}
	if((*state) == 11){
		if(pattern == '*')return 1;
		if(pattern == '/'){(*state)=9;return 0;}
		(*state)=10;return 1;
	}
	if((*state) == 12)return 0;
	if((*state) == 13){(*state)=8 ;return 1;}
	if((*state) == 14){(*state)=15;return 0;}
	if((*state) == 15)return 0;
}

int is_stream(char pattern[], char type[20]){
	/*Returns the acceptance info of stream from the DFA. Also loads type with
	  the type of identified stream.
		  returns  0 -> invalid
			returns  1 -> identifed stream. The 'type' holds the identifed category
			returns -1 -> found escape sequence. decrement the buffer!!
	*/

	int state = 0;
	for(int i=0;pattern[i]!='\0';i++){
		scan_stream(pattern[i],&state);
	}

	if(state==3 ){strcpy(type,"CHAR CONST");     return  1;}
	if(state==6 ){strcpy(type,"STRING CONST");   return  1;}
	if(state==8 ){strcpy(type,"COMMENT");        return  1;}
	if(state==9 ){strcpy(type,"COMMENT");        return  1;}
	if(state==15){strcpy(type,"ESCAPE SEQUENCE");return -1;}
	// state==7  -> single forward slash means nothing!
	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~handling numerials~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int scan_numerials(char pattern, int *state){
	/*compare pattern on numeral rules.
	'state' denotes the DFA state matching numerial. auto updates this variable
		if exact match   -> return  1
		if partial match -> return -1
		if no match      -> return  0
	*/
	if((*state) == 0){
		if(pattern == '.'){(*state)=10;return -1;}
		if(pattern == '0'){(*state)=3 ;return  1;}
		if(pattern >= '1' && pattern <= '9'){(*state)=2;return  1;}
		if(pattern == '+' || pattern == '-'){(*state)=1;return -1;}
		(*state)=15;return 0;
	}
	if((*state) == 1){
		if(pattern == '.'){(*state)=10;return -1;}
		if(pattern == '0'){(*state)=3 ;return  1;}
		if(pattern >= '1' && pattern <= '9'){(*state)=2;return  1;}
		(*state)=15;return 0;
	}
	if((*state) == 2){
		if(pattern == '.'){(*state)=11;return  1;}
		if(pattern >= '0' && pattern <= '9'){(*state)=2 ;return  1;}
		if(pattern == 'E' || pattern == 'e'){(*state)=12;return -1;}
		(*state)=15;return 0;
	}
	if((*state) == 3){
		if(pattern == '.'){(*state)=11;return  1;}
		if(pattern == 'E' || pattern == 'e'){(*state)=12;return -1;}
		if(pattern == 'B' || pattern == 'b'){(*state)=6 ;return -1;}
		if(pattern == 'X' || pattern == 'x'){(*state)=7 ;return -1;}
		if(pattern >= '0' && pattern <= '7'){(*state)=4 ;return  1;}
		if(pattern == '8' || pattern == '9'){(*state)=5 ;return -1;}
		(*state)=15;return 0;
	}
	if((*state) == 4){
		if(pattern == '.'){(*state)=11;return  1;}
		if(pattern >= '0' && pattern <= '7'){(*state)=4 ;return  1;}
		if(pattern == 'E' || pattern == 'e'){(*state)=12;return -1;}
		if(pattern == '8' || pattern == '9'){(*state)=5 ;return -1;}
		(*state)=15;return 0;
	}
	if((*state) == 5){
		if(pattern == '.'){(*state)=11;return  1;}
		if(pattern == 'E' || pattern == 'e'){(*state)=12;return -1;}
		if(pattern >= '0' && pattern <= '9'){(*state)=5 ;return -1;}
		(*state)=15;return 0;
	}
	if((*state) == 6){
		if(pattern == '0' || pattern == '1'){(*state)=8 ;return  1;}
		(*state)=15;return 0;
	}
	if((*state) == 7){
		if(pattern >= '0' && pattern <= '9'){(*state)=9 ;return  1;}
		if(pattern >= 'A' && pattern <= 'F'){(*state)=9 ;return  1;}
		if(pattern >= 'a' && pattern <= 'f'){(*state)=9 ;return  1;}
		(*state)=15;return 0;
	}
	if((*state) == 8){
		if(pattern == '0' || pattern == '1'){(*state)=8 ;return  1;}
		(*state)=15;return 0;
	}
	if((*state) == 9){
		if(pattern >= '0' && pattern <= '9'){(*state)=9 ;return  1;}
		if(pattern >= 'A' && pattern <= 'F'){(*state)=9 ;return  1;}
		if(pattern >= 'a' && pattern <= 'f'){(*state)=9 ;return  1;}
		(*state)=15;return 0;
	}
	if((*state) == 10){
		if(pattern >= '0' && pattern <= '9'){(*state)=11;return  1;}
		(*state)=15;return 0;
	}
	if((*state) == 11){
		if(pattern >= '0' && pattern <= '9'){(*state)=11;return  1;}
		if(pattern == 'E' || pattern == 'e'){(*state)=12;return -1;}
		(*state)=15;return 0;
	}
	if((*state) == 12){
		if(pattern >= '0' && pattern <= '9'){(*state)=14;return  1;}
		if(pattern == '+' || pattern == '-'){(*state)=13;return -1;}
		(*state)=15;return 0;
	}
	if((*state) == 13){
		if(pattern >= '0' && pattern <= '9'){(*state)=14;return  1;}
		(*state)=15;return 0;
	}
	if((*state) == 14){
		if(pattern >= '0' && pattern <= '9'){(*state)=14;return  1;}
		(*state)=15;return 0;
	}
	return 0;
}

int is_numerial(char pattern[], char type[20]){
	/*Returns the acceptance info of numerials from the DFA. Also loads type with
	  the type of numerials identified.
		  returns  0 -> not a numerial
			returns  1 -> identifed numerial. The 'type' holds the identifed category
	*/

	int state = 0;
	for(int i=0;pattern[i]!='\0';i++){
		scan_numerials(pattern[i],&state);
	}

	if(state == 2 ){strcpy(type,"DECIMAL CONST");     return 1;}
	if(state == 3 ){strcpy(type,"DECIMAL CONST");     return 1;}
	if(state == 4 ){strcpy(type,"OCTAL CONST");       return 1;}
	if(state == 8 ){strcpy(type,"BINARY CONST");      return 1;}
	if(state == 9 ){strcpy(type,"HEXADECIMAL CONST"); return 1;}
	if(state == 11){strcpy(type,"FLOAT CONST");       return 1;}
	if(state == 14){strcpy(type,"EXPONENT CONST");    return 1;}
	return 0;
}
