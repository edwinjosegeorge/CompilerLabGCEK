%{
#include "y.tab.h"
%}

%%
a return A;
b return B;
\n return NEWLINE;
. return OTHER;
%%

int yywrap(){return;}
