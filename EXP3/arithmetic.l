%{
#include "y.tab.h"
%}

%%
[_a-zA-Z][_a-zA-Z0-9]* return IDENTIFIER;
[+-][+-] { unput(yytext[yyleng-1]);return OPERATOR;}

[+-]?[0][Bb][01]+                                   return NUMBER;
[+-]?[0][Xx][0-9A-Fa-f]+                            return NUMBER;
[+-]?[0][0-7]+                                      return NUMBER;
[+-]?[1-9][0-9]*[LlUu]?                             return NUMBER;
[+-]?(("."[0-9])|([0-9]+"."))[0-9]*                 return NUMBER;
[+-]?[0-9]+[Ee][+-]?[0-9]+                          return NUMBER;
[+-]?(("."[0-9])|([0-9]+"."))[0-9]*[Ee][+-]?[0-9]+  return NUMBER;


[\/\*\-\+] return OPERATOR;
"("        return OPEN_BKT;
")"        return CLOSE_BKT;
\n         return END;

[" "\t]    ;
.          return OTHER;
%%

int yywrap(){return;}
