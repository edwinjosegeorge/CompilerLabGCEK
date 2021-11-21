%{
#include "y.tab.h"
%}

%%
[A-Za-z] return letter;
[0-9] return digit;
\n return NEWLINE;
. return OTHER;
%%

int yywrap(){return;}
