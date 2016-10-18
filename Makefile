all: 	
	clear
	lex lexica.l
	yacc -d sintatica.y
	g++ -o glf y.tab.c -lfl -std=c++11

	./glf < exemplo.foca
