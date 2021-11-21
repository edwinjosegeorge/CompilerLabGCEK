lex expression.l
yacc expression.y -d
gcc lex.yy.c y.tab.c -w -lm
./a.out
