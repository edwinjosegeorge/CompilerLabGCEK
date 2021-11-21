lex variable.l
yacc variable.y -d
gcc lex.yy.c y.tab.c -w -lm
./a.out
