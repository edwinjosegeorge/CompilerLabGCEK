lex calculator.l
yacc calculator.y -d
gcc lex.yy.c y.tab.c -w -lm
./a.out
