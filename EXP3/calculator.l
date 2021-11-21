%{
#include "y.tab.h"
%}

%%
[0-9]+([Ee][+-]?[0-9]+)? {
    yylval=atoi(yytext);
    return NUMBER;
}

[\+\-\*\/\^\(\)] {return yytext[0];}
\n         {return END;}

[" "\t]    {;}
.          {return OTHER;}
%%

int yywrap(){return;}
