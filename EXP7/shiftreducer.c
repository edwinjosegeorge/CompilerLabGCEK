#include<stdio.h>
#include<string.h>

int GRAMMAR_LEN = 6;
char GRAMMAR[][13]={
                  "S -> E",
                  "E -> E+E",
                  "E -> E-E",
                  "E -> E*E",
                  "E -> (E)",
                  "E -> i"
                };

int  ACCEPTED, ERROR;
int  state[16],state_no;
int  input_no ,symbol_no;
char input[16],symbol[16];
char action[16];

void Parser();
int Goto(int,char);

int main(){
  char states_str[50], temp_str[5]; //variable to hold the int states as strings;

  printf("The grammar is \n");
  for(int i=0;i<GRAMMAR_LEN; i++)printf("\t(%d) %s\n",i,GRAMMAR[i]);

  printf("\nEnter the input string [max 14 charac] : ");
  scanf("%s",input);

  //setting up environments - stacks
  ACCEPTED=0;ERROR=0;input_no=0;
  input[14]='\0';strcat(input,"$");
  strcpy(symbol,"$");symbol_no=0;
  state_no=0;state[state_no]=0;


  int iteration=0;
  printf("+-----+");for(int j=0;j<4;j++)printf("------------------+");printf("\n");
  printf("| %3s | %-16s | %-16s | %-16s | %-16s |\n","NO","STATE","SYMBOLS","INPUT","ACTION");
  printf("+-----+");for(int j=0;j<4;j++)printf("------------------+");printf("\n");

  //start the Parse
  while(input[input_no]!='\0' && ERROR==0){

    //converting int states to string states
    states_str[0]='\0';
    for(int i=0;i<=state_no;i++){
      sprintf(temp_str,"%d ",state[i]);
      strcat(states_str,temp_str);
    }

    printf("| %3d ",iteration++);
    printf("| %-16s ",states_str);
    printf("| %-16s ",symbol);
    printf("| %-16s ",input+input_no);
    Parser();
    printf("| %-16s |\n",action);
  }
  printf("+-----+");for(int j=0;j<4;j++)printf("------------------+");printf("\n");

  printf("String "); if(ACCEPTED)printf("accepted ");else printf("rejected ");
  printf("with");if(!ERROR)printf("out");printf(" errors\n");
}

int Goto(int st, char e){
  if(st==0 && e=='E')return 1;
  if(st==2 && e=='E')return 7;
  if(st==4 && e=='E')return 8;
  if(st==5 && e=='E')return 9;
  if(st==6 && e=='E')return 10;
  return -1;
}

void Parser(){
  //Parse and return the action performed
  strcpy(action,"ERROR");
  if(state_no < 0)return;

  int c_st=state[state_no]; //current state
  int c_in=input[input_no]; //current input
  int shift = -1;
  int reduce = -1;

  //parse table
       if(c_in=='+' && ( c_st==1||c_st==7||c_st==8||c_st==9||c_st==10 ))shift=4;
  else if(c_in=='-' && ( c_st==1||c_st==7||c_st==8||c_st==9||c_st==10 ))shift=5;
  else if(c_in=='*' && ( c_st==1||c_st==7||c_st==8||c_st==9||c_st==10 ))shift=6;
  else if(c_in=='(' && ( c_st==0||c_st==2||c_st==4||c_st==5||c_st==6  ))shift=2;
  else if(c_in=='i' && ( c_st==0||c_st==2||c_st==4||c_st==5||c_st==6  ))shift=3;
  else if(c_in==')' && c_st==7)shift=11;

  else if(c_st==3  && (c_in=='+'||c_in=='-'||c_in=='*'||c_in==')'||c_in=='$'))reduce=5;
  else if(c_st==11 && (c_in=='+'||c_in=='-'||c_in=='*'||c_in==')'||c_in=='$'))reduce=4;
  else if(c_st==8  && (c_in==')'||c_in=='$'))reduce=1;
  else if(c_st==9  && (c_in==')'||c_in=='$'))reduce=2;
  else if(c_st==10 && (c_in==')'||c_in=='$'))reduce=3;

  else if(c_st==1 && c_in=='$'){
    ACCEPTED=1;
    input_no++;
    strcpy(action,"ACCEPT");
    return;
  }
  else {ERROR = 1;return;}

  if(shift!=-1){
    state[++state_no]=shift;
    symbol[++symbol_no]=input[input_no++];
    symbol[symbol_no+1]='\0';
    sprintf(action,"SHIFT  state %d",shift);
    return;
  }
  else{
    int size=strlen(GRAMMAR[reduce])-5;
    char* handle=symbol+symbol_no-size+1;
    char* production=GRAMMAR[reduce]+5;

    if(strcmp(handle,production)==0){
      symbol_no -= size-1;
      state_no -= size-1;
      symbol[symbol_no] = GRAMMAR[reduce][0];
      symbol[symbol_no+1] = '\0';

      state[state_no] = Goto(state[state_no-1],GRAMMAR[reduce][0]);
      if(state[state_no]!= -1){
        sprintf(action,"REDUCE prodt %d",reduce);
        return;
      }
    }
  }
  ERROR=1;
}
