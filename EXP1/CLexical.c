/*
Author : Edwin Jose George
Input stream should be CRLF formated for line number to work
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "stack.h"
#include "definition.h"

struct{char ch;int hold;}LOOK_AHEAD={' ',0};
int lineNumber = 1;

FILE *filep;

int read_lexemes(char buffer[],char type[]){
	/*read a valid single token and its type info into type var
		return 1  -> we have more lexemes to scan
		return 0  -> no more lexemes to read
		return -1 -> error reading lexeme
	*/

	int j = 0;
	buffer[0] = '\0';

	//hold flag info
	int reading_identifier=0, reading_symbol=0;
	int reading_numerial=0,  reading_stream=0;
	int state_numerial=0, state_stream=0, state_identifier=0;
	int stream_type = 0;

	while(1){

		//read a single charactor
		if(LOOK_AHEAD.hold){
			buffer[j] = LOOK_AHEAD.ch;
			LOOK_AHEAD.hold = 0;
		}
		else buffer[j] = fgetc(filep);
		if(buffer[j]==NEWLINE)lineNumber++;
		buffer[j+1] = '\0';

		if(buffer[j]==EOF){ // this is the last occurance!
			buffer[j]='\0';

			if(buffer[0]=='\0'){strcpy(type,"END OF FILE");return 0;}
			if(reading_stream && is_stream(buffer,type))return 0;
			if(reading_identifier && is_keyword(buffer,type))return 0;
			if(reading_identifier && is_identifier(buffer,type))return 0;
			if(reading_numerial && is_numerial(buffer,type))return 0;
			if(reading_symbol && is_symbol(buffer,type))return 0;

			//none of the return was triggered! => cannot detect
			printf("ERROR at line %d : cannot detect category | %s \n",lineNumber,buffer);
			return -1;
		}


		if(j == 0){ // this is the first occurance

			//ignore initial whitespaces
			if(buffer[j]==NEWLINE || buffer[j]==CARRIAGE)continue;
			if(buffer[j]==SPACE   || buffer[j]==TAB)continue;

			//prepare to read stream - string,char,comment
			reading_stream = scan_stream(buffer[j],&state_stream);

			if(buffer[j]=='#'){//start of PRE_PROCESSORS
				reading_identifier = 1;
				state_identifier = 1;
				j++;continue;
			}

			//preparing to read operators
			reading_identifier = scan_identifier(buffer[j],&state_identifier);

			//preparing to read numerials
			reading_numerial = scan_numerials(buffer[j],&state_numerial);

			//preparing to read operators
			reading_symbol = is_symbol(buffer,type);

			//no possible tokens?!
			if((reading_stream|reading_identifier|reading_numerial|reading_symbol)==0){
				printf("ERROR: unidentified charactor %c at line %d \n",buffer[j],lineNumber);
				return -1;
			}

			j++;continue;
		}


		if(reading_stream == 1){ // reading string/char/comment stream
			reading_stream = scan_stream(buffer[j],&state_stream);
			if(reading_stream == 1){j++;continue;}
			if(reading_stream == 0){ //reading stream has ended
				stream_type = is_stream(buffer,type);
				if(stream_type == 1)return 1;//success
				if(stream_type ==-1){//process escape sequence
					buffer[1]='\0';
					j = 0;
					reading_identifier=0;reading_symbol=0;
					reading_numerial=0  ;reading_stream=0;
					state_numerial=0; state_stream=0; state_identifier=0;
					stream_type = 0;
					continue;
				}
				printf("ERROR at line %d : cannot detect stream | %s \n",lineNumber,buffer);
				return -1;
			}
		}
		else if(reading_stream == -1){// was waiting to identify a comment
			reading_stream = scan_stream(buffer[j],&state_stream);
			if(reading_stream == 1){j++;continue;} //started to read comment
			/*if(reading_stream == 0)
				that was not a comment, lets continue checking for other types
			*/
		}

		if(reading_identifier){// might belong to identifer grp
			reading_identifier = scan_identifier(buffer[j],&state_identifier);
			if(reading_identifier == 1){j++;continue;}//continue reading identifier

			//current char ends identifer category
			LOOK_AHEAD.hold = 1;
			LOOK_AHEAD.ch = buffer[j];
			buffer[j] = '\0';

			if(is_keyword(buffer,type))return 1;
			if(is_identifier(buffer,type))return 1;

			printf("ERROR at line %d : cannot detect identifier | %s \n",lineNumber,buffer);
			return -1;

		}

		if(reading_numerial){ //might belong to numeral grp
			reading_numerial = scan_numerials(buffer[j],&state_numerial);
			if(reading_symbol == 0 && reading_numerial ){j++;continue;} //reading num
			if(reading_symbol == 0 && reading_numerial == 0){
				//current char have ended numerial
				LOOK_AHEAD.hold = 1;
				LOOK_AHEAD.ch = buffer[j];
				buffer[j] = '\0';

				if(is_numerial(buffer,type))return 1;
				printf("ERROR at line %d : cannot detect numerial | %s \n",lineNumber,buffer);
				return -1;

			}
			if(reading_symbol == 1 && reading_numerial != 0){
				/*there will be no pattern such that first 2 char are both symbol type
				  and numerial type at same time!
				*/
				reading_symbol = 0;
				j++;continue;
			}
			/*if(reading_symbol == 1 && reading_numerial == 0)
				obviously, i must have been reading a operator sequence!
			*/
		}

		if(reading_symbol){
			reading_symbol = is_symbol(buffer,type);
			if(reading_symbol == 0){ // current char ended symbol secuence
				LOOK_AHEAD.hold = 1;
				LOOK_AHEAD.ch = buffer[j];
				buffer[j] = '\0';

				if(is_symbol(buffer,type)==1)return 1;
				printf("ERROR at line %d : cannot detect symbol | %s \n",lineNumber,buffer);
				return -1;
			}
			/*else
					next char might be included to symbol category
			*/
			j++;continue;
		}

		//none of the jumps above (continue/return) was triggered! => cannot detect
		printf("ERROR at line %d : cannot detect category | %s \n",lineNumber,buffer);
		return -1;
	}
}

void main(int argc, char** argv){
	if(argc > 1){
		if((filep=fopen(argv[1], "r"))==NULL) {
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
	char lexemes[500],type[20];
	int reading = read_lexemes(lexemes,type);

	while(reading == 1){
		printf("%4d | %20s | %s\n",lineNumber,type,lexemes);
		reading = read_lexemes(lexemes,type);
	}
	if(reading == 0)printf("%4d | %20s | %s\n",lineNumber,type,lexemes);

	fclose(filep);
	distroy_resv_token();
}
