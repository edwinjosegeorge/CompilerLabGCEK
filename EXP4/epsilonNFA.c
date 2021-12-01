#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define epsilon "e"

//------------------------------------------------------------------------------

struct stack{
  void *info;
  struct stack *next;
};

struct stack *push(struct stack *A,void *info){
  //push node to top and returns to top addr
  struct stack *tmp = malloc(sizeof(struct stack));
  tmp->info = info;
  tmp->next = A;
  return tmp;
}

struct stack *pop(struct stack *A){
  //pops and delete the node from top and returns new addr
  if(A != NULL){
    struct stack *tmp = A->next;
    free(A);
    A = tmp;
  }
  return A;
}

//------------------------------------------------------------------------------

struct state{
  char name[4];
  struct stack *transition;
};

struct transit{
  char symbol[4];
  struct state *toName;
};

//------------------------------------------------------------------------------

struct stack *NFA = NULL;

struct state *getState(char name[]){
  //returns the address of state from NFA
  struct stack *nfa = NFA;
  struct state *S;

  //search the state...
  while(nfa != NULL){
    S = nfa->info;
    if(strcmp(S->name,name)==0)return S;
    nfa = nfa->next;
  }

  //no state found...
  return NULL;
}

struct state *createState(char name[]){
  //create new state
  struct state *S = malloc(sizeof(struct state));
  strcpy(S->name,name);
  NFA = push(NFA,S);
  return S;
}

struct transit *getTransition(struct state *from, char symbol[], struct state *to){
  //returns the address of transition from state "from" to state "to" upon
  //receiving input "symbol"
  struct stack *transition = from->transition;
  struct transit *T;

  //search the transition...
  while(transition != NULL){
    T  = transition->info;
    if(strcmp(T->symbol,symbol)==0)
      if(T->toName == to)return T;
    transition = transition->next;
  }

  //no transition found...
  return NULL;
}

struct transit *createTransition(struct state *from, char symbol[], struct state *to){
  //create new transition
  struct transit *T = malloc(sizeof(struct transit));
  strcpy(T->symbol,symbol);
  T->toName = to;
  from->transition = push(from->transition,T);
  return T;
}

//------------------------------------------------------------------------------

void deleteNFA(){
  //deletes the complete NFA structure
  struct state *S;
  struct transit *T;

  while(NFA != NULL){
    S = NFA->info;
    while(S->transition != NULL){
      T = S->transition->info;
      free(T);
      S->transition = pop(S->transition);
    }
    free(S);
    NFA = pop(NFA);
  }
}

//------------------------------------------------------------------------------

struct stack *findEpsilonTrans(struct stack *epsTran, struct state *fromState){
  //recursively find the epsilon transition

  //add to stack only if its not there!
  struct stack *node = epsTran;
  for(;node!=NULL;node=node->next){
    if(node->info == fromState)return epsTran;
  }
  epsTran = push(epsTran,fromState);

  //iterate through transitions
  struct transit *T;
  struct stack *transition = fromState->transition;
  for(;transition!=NULL;transition=transition->next){
    T = transition->info;
    if(strcmp(T->symbol,epsilon)==0)
      epsTran = findEpsilonTrans(epsTran,T->toName);
  }
  return epsTran;
}

//------------------------------------------------------------------------------
void main(){
  int count;
  struct transit *trans;
  struct state *from, *to;
  struct stack *node, *epsTran;
  char fromName[4], symbol[4], toName[4];

  printf("Enter the number of transitions : ");
  scanf("%d",&count);

  printf("Enter the transition of format \n");
  printf("'from' 'symbol' 'to' \n");
  printf(" Show epsilon symbol by '%s' \n\n",epsilon);

  for(int i=1;i<=count;i++){
    printf("%d/%d : ",i,count);
    scanf("%s %s %s",fromName,symbol,toName);

    //creating and adding new states and transitions
    from = getState(fromName);
    if(from == NULL){from=createState(fromName);}
    to = getState(toName);
    if(to == NULL){to=createState(toName);}
    trans = getTransition(from,symbol,to);
    if(trans == NULL){trans=createTransition(from,symbol,to);}
  }


  printf("\nSearching Epsilon transitions \n\n");
  for(node=NFA,epsTran=NULL; node!=NULL;node=node->next){
    from = node->info;
    epsTran = findEpsilonTrans(epsTran,from);


    printf("state %s = { ",from->name);
    while(epsTran != NULL){
      to = epsTran->info;
      if(epsTran->next == NULL)printf("%s }\n",to->name);
      else printf("%s, ",to->name);
      epsTran = pop(epsTran);
    }
  }

  deleteNFA();
}
