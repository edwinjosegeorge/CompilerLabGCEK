lex ablex.l
yacc abyacc.y -d
cc lex.yy.c y.tab.c -w
./a.out
