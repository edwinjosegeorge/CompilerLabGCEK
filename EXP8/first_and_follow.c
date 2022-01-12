#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define EPSILON 'e'

struct DATA_REP{char head, tail[24];};
struct DATA_REP GRAMMAR[12], FIRST[12], FOLLOW[12];
int GRAMMAR_LEN, FIRST_LEN, FOLLOW_LEN;

int MARK_CMPT[12][2];
int FIRST_USED[12][12];
int FOLLOW_USED[12][12];

//Usages
//MARK_CMPT[2][0]=1 => completed FIRST[2];
//MARK_CMPT[5][1]=1 => completed FOLLOW[5];
//FIRST_USED[2][3]=1 => FIRST[2] used GRAMMAR[3] to compute
//FOLLOW_USED[3][5]=1 => FOLLOW[3] used GRAMMAR[5] to compute

int update_union(char dest[],char src[]){
  //make union(skip EPSILON), if EPSILON found, return 1, else 0
  int found=0,s=0,d=0,eps=0;
  for(s=0;src[s]!='\0';s+=2){
    found=0;
    if(src[s]==EPSILON){eps=1;continue;}
    for(d=0;dest[d]!='\0';d+=2)if(dest[d]==src[s]){found=1;break;}
    if(found==0){
      dest[d]=src[s];
      dest[d+1]=' ';
      dest[d+2]='\0';
    }
  }
  return eps;
}

void print_struct(struct DATA_REP D[], int size){
  for(int i=0;i<size;i++)
    printf("\t(%d) %c -> { %s }\n",i,D[i].head,D[i].tail);
}

void getGrammar(){
  printf("Enter the number of grammar production [max 12]: ");
  scanf("%d",&GRAMMAR_LEN);
  if(GRAMMAR_LEN>12)GRAMMAR_LEN=12;

  printf("Enter the augmented grammar in the form 'HEAD' 'PRODUCTION'\n");
  for(int i=0;i<GRAMMAR_LEN;i++){
    printf("\t(%d) ",i);
    scanf(" %c %s",&GRAMMAR[i].head, GRAMMAR[i].tail);
  }

  strcat(GRAMMAR[0].tail,"$");
}

int find_first(char c){
  //search if already computed
  int i=0;
  for(i=0;i<FIRST_LEN;i++)if(FIRST[i].head == c)break;
  if(i<FIRST_LEN && MARK_CMPT[i][0]==1)return i;
  else if(i<FIRST_LEN && MARK_CMPT[i][0]==0)return -1;
  else{
    if(FIRST_LEN==12){printf("\nFIRST overflow\n");return -1;}
    FIRST_LEN++;
    FIRST[i].head=c;
    FIRST[i].tail[0]='\0';
  }

  int found_epsilon=0;
  for(int g=0;g<GRAMMAR_LEN;g++){
    if(GRAMMAR[g].head!=c || FIRST_USED[i][g]==1)continue;
    FIRST_USED[i][g]=1;
    if(GRAMMAR[g].tail[0]==c)continue;

    for(int k=0;GRAMMAR[g].tail[k]!='\0';k++){
      if(isalpha(GRAMMAR[g].tail[k]) && isupper(GRAMMAR[g].tail[k])){ //nonterminal
        int gi = find_first(GRAMMAR[g].tail[k]);

        if(gi==-1){
          printf("Recursive bottle neck!");
          return -1;
        }

        //union the first of FIRST[gi].tail to FIRST[i].tail;
        found_epsilon=update_union(FIRST[i].tail,FIRST[gi].tail);
        if(!found_epsilon)break;
        else if(GRAMMAR[g].tail[k+1]=='\0'){
          char temp[5];
          sprintf(temp,"%c ",EPSILON);
          strcat(FIRST[i].tail,temp);
        }
      }
      else{//terminal symbol
        char temp[5];
        sprintf(temp,"%c ",GRAMMAR[g].tail[k]);
        strcat(FIRST[i].tail,temp);
        break;
      }
    }
  }
  MARK_CMPT[i][0]=1;
  return i;
}

int find_follow(char c){
  //search if already computed
  int i=0;
  for(i=0;i<FOLLOW_LEN;i++)if(FOLLOW[i].head == c)break;
  if(i<FOLLOW_LEN && MARK_CMPT[i][1]==1)return i;
  else if(i<FOLLOW_LEN && MARK_CMPT[i][1]==0)return -1;
  else{
    if(FOLLOW_LEN==12){printf("\nFOLLOW overflow\n");return -1;}
    FOLLOW_LEN++;
    FOLLOW[i].head=c;
    FOLLOW[i].tail[0]='\0';
  }

  int found_epsilon=0;
  for(int g=0;g<GRAMMAR_LEN;g++){
    FOLLOW_USED[i][g]=1;
    //processing the tail.
    for(int k=0;GRAMMAR[g].tail[k]!='\0';k++){
      if(GRAMMAR[g].tail[k]!=c)continue;
      while(1){
        k++;
        if(GRAMMAR[g].tail[k]=='\0'){//union follow of head
          int gi = find_follow(GRAMMAR[g].head);

          if(gi==-1){
            printf("Recursive bottle neck!");
            return -1;
          }

          int eps=update_union(FOLLOW[i].tail,FOLLOW[gi].tail);
          if(eps){
            char temp[5];
            sprintf(temp,"%c ",EPSILON);
            strcat(FOLLOW[i].tail,temp);
          }
          break;
        }
        if(isalpha(GRAMMAR[g].tail[k]) && isupper(GRAMMAR[g].tail[k])){ //nonterminal
          int fg=find_first(GRAMMAR[g].tail[k]);
          if(fg==-1){
            printf("Recursive bottle neck\n");
            return -1;
          }
          int eps=update_union(FOLLOW[i].tail,FIRST[fg].tail);
          if(!eps)break;
        }
        else{//terminal symbol
          char temp[5];
          sprintf(temp,"%c ",GRAMMAR[g].tail[k]);
          strcat(FOLLOW[i].tail,temp);
          break;
        }
      }
    }
  }
  MARK_CMPT[i][1]=1;
  return i;
}

int main(){
  getGrammar();

  FIRST_LEN=FOLLOW_LEN=0;
  for(int i=0;i<12;i++){
    MARK_CMPT[i][0]=MARK_CMPT[i][1]=0;
    FIRST[i].tail[0]='\0';
    FOLLOW[i].tail[0]='\0';
    for(int j=0;j<12;j++)FIRST_USED[i][j]=FOLLOW_USED[i][j]=0;
  }

  for(int i=0;i<GRAMMAR_LEN;i++)find_first(GRAMMAR[i].head);
  FOLLOW_LEN++;MARK_CMPT[0][1]=1;
  FOLLOW[0].head=GRAMMAR[0].head;
  strcpy(FOLLOW[0].tail,"$ ");
  for(int i=0;i<GRAMMAR_LEN;i++)find_follow(GRAMMAR[i].head);

  printf("\n Augmented Grammar\n");print_struct(GRAMMAR,GRAMMAR_LEN);
  printf("\n FIRST()\n");print_struct(FIRST,FIRST_LEN);
  printf("\n FOLLOW()\n");print_struct(FOLLOW,FOLLOW_LEN);
}
