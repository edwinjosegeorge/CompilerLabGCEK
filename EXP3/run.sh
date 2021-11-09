lex ab_lex.l
yacc ab_yacc.y -d
cc lex.yy.c y.tab.c -w
./a.out
