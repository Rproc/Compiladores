all: 	
	clear
	------------------------------------------------------------------
	echo -n > varTable # remove arquivo de log para inicializaçao
	lex lexica.l
	yacc -d sintatica.y
	g++ -o glf y.tab.c -lfl -std=c++11

	./glf < exemplo.foca
	
	
	#Executando Codigo Intermediario
	g++ -o s src.c 
	./s

	