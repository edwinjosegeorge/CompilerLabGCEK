lex arithmetic.l
yacc arithmetic.y -d
cc lex.yy.c y.tab.c -w
./a.out
