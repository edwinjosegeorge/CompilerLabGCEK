/*Non-predictive Recursive Descent parser with backtracking for the given grammar
  E -> T E'
  E' -> + T E' | e
  T -> F T'
  T' -> * F T' | e
  F -> ( E ) | id
  where 'e' denotes epsilon. 'i' can be used as terminal symbol instead of 'id'.
*/

#include<stdio.h>

char lexeme[100];
int pos;

//funcition declaration
int match(char);
int E();
int Eprime();
int T();
int Tprime();
int F();

//Function definition
int match(char c){
  if(c == lexeme[pos]){
    pos++;
    return 1;
  }
  return 0;
}

int E(){
  //E -> T Eprime
  int backtrack=pos;

  pos=backtrack;
  if(T()){
    if(Eprime()){
      return 1;
    }
  }

  pos=backtrack;
  return 0;
}

int Eprime(){
  //Eprime -> + T Eprime | e
  int backtrack=pos;

  pos=backtrack;
  if(match('+')){
    if(T()){
      if(Eprime()){
        return 1;
      }
    }
  }

  pos=backtrack;
  return 1;
}

int T(){
  //T -> F Tprime
  int backtrack=pos;

  pos=backtrack;
  if(F()){
    if(Tprime()){
      return 1;
    }
  }

  pos=backtrack;
  return 0;
}

int Tprime(){
  //Tprime -> * F Tprime | e
  int backtrack=pos;

  pos=backtrack;
  if(match('*')){
    if(F()){
      if(Tprime()){
        return 1;
      }
    }
  }

  pos=backtrack;
  return 1;
}

int F(){
  //F -> ( E ) | id
  int backtrack=pos;

  pos=backtrack;
  if(match('(')){
    if(E()){
      if(match(')')){
        return 1;
      }
    }
  }

  pos=backtrack;
  if(match('i')){
    return 1;
  }

  pos=backtrack;
  return 0;
}

//Driver function
void main(){
  printf("NOTE:\n\t'i' denotes an identifier \n");
  printf("\tEnd the expression with a special symbol '$'\n");
  printf("Enter an arithmetic expression : ");
  scanf("%s",lexeme);

  pos=0;
  if(E() && lexeme[pos]=='$')printf("VALID expression\n");
  else printf("INVALID expression\n");
}
