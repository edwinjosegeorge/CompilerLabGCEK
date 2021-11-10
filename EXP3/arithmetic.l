%{
#include "y.tab.h"
%}

%%
[_a-zA-Z][_a-zA-Z0-9]* {return IDENTIFIER;}
[+-][+-] { unput(yytext[yyleng-1]);return OPERATOR;}

[+-]?[0-9]+([Ee][+-]?[0-9]+)?                          {return NUMBER;}
[+-]?(("."[0-9])|([0-9]+"."))[0-9]*([Ee][+-]?[0-9]+)?  {return NUMBER;}


[\/\*\-\+] {return OPERATOR;}
"("        {return OPEN_BKT;}
")"        {return CLOSE_BKT;}
\n         {return END;}

[" "\t]    {;}
.          {return OTHER;}
%%

int yywrap(){return;}
