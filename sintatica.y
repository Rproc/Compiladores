%{
#include <iostream>
#include <string>
#include <sstream>

#define YYSTYPE atributos

using namespace std;

string getVarType(int);
int checkType(int, int);
string convertRelacional(int, string, int, string);
int curVar = 0;
string getVarName(){
	return "temp" + to_string(++curVar);
}

struct atributos
{
	string label;
	string traducao;
	int tipo;
};

struct variavel
{
	string tipo;
	string nome_var;

};


int yylex(void);
void yyerror(string);
%}

%token TK_NUM TK_REAL TK_CHAR TK_BOOL
%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_CHAR TK_TIPO_BOOL
%token TK_FIM TK_ERROR
%token TK_EQUAL TK_GTE TK_LTE TK_NEQUAL TK_MAIOR TK_MENOR
%token TK_AND TK_OR TK_NOT

%start S
%left ')'
%left '+'
%left '-'
%left '*'
%left '/'
%left '('

%%

S 			: TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\nint main(void)\n{\n" << $5.traducao << "\treturn 0;\n}" << endl;
			}
			;

BLOCO		: '{' COMANDOS '}'
			{
				$$.traducao = $2.traducao;
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducao = $1.traducao + $2.traducao;
			}
			|
			;

COMANDO 	: E ';'
			;

E 			: '('E')'{

				$$ = $2;
			}
			| '-' E{
				$$.tipo = $2.tipo;
				string varName = getVarName();
				$$.label = '-' + $2.label;
				$$.traducao = $2.traducao + "\t"+getVarType($$.tipo)+ " " + varName +" = " + " - " + $2.label +";\n";
			}
 			| E '+' E
			{
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t"+getVarType($$.tipo)+ " " + varName +" = "+ $1.label +" + "+ $3.label +";\n";
				$$.label = varName;

			}
			| E '-' E
			{
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t" +getVarType($$.tipo)+ " " +varName +" = "+ $1.label +" - "+ $3.label +";\n";
				$$.label = varName;

			}
			| E '*' E
			{
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t" +getVarType($$.tipo)+ " " +   varName+" = "+ $1.label +" * "+ $3.label +";\n";
				$$.label = varName;

			}
			| E '/' E
			{
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t"+getVarType($$.tipo)+ " " +  varName +" = "+ $1.label +" / "+ $3.label +";\n";
				$$.label = varName;
			}
			| E '>' E
			{
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+ "bool " + varName +" = "+ $1.label +" > "+ $3.label +";\n";
				$$.label = varName;
			}
			| E '<' E
			{
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+ "bool " + varName +" = "+ $1.label +" < "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_GTE E
			{
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+ "bool " + varName +" = "+ $1.label +" >= "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_LTE E
			{
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+ "bool " + varName +" = "+ $1.label +" <= "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_EQUAL E
			{
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+ "bool " + varName +" = "+ $1.label +" == "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_NEQUAL E
			{
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+ "bool " + varName +" = "+ $1.label +" != "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_AND E
			{
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t"+getVarType($$.tipo)+ " " +  varName +" = "+ $1.label +" && "+ $3.label +";\n";
				$$.label = varName;
			}
			| TK_REAL
			{
				$$.tipo = TK_REAL;
				string varName = getVarName();
				$$.traducao = "\t" + getVarType($$.tipo) + " "+varName+ " = " + $1.label + ";\n";
				$$.label = varName;
			}
			| TK_NUM
			{
				$$.tipo = TK_NUM;
				string varName = getVarName();
				$$.traducao = "\t"+ getVarType($$.tipo) + " "+varName+ " = " + $1.label + ";\n";
				$$.label = varName;
			}
			| TK_BOOL
			{
				$$.tipo = TK_BOOL;
				string varName = getVarName();
				puts("Estou aqui");
				$$.traducao = "\t"+ getVarType($$.tipo) + " "+varName+ " = " + $1.label + ";\n";
				$$.label = varName;
			}
			| TK_ID
			{
				$$.traducao = $1.traducao;
			}
			;

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{

	yyparse();

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}

string getVarType(int type){
	if(type == TK_NUM)
		return "int";
	if(type == TK_REAL )
		return "float";
	if(type == TK_TIPO_CHAR)
		return "char";
	if(type == TK_BOOL)
		return "bool";
}

int checkType (int t1, int t3){
	if ( (t1 != TK_NUM && t1 != TK_REAL) || (t3 != TK_NUM && t3 != TK_REAL) ) {

		if (t1 == TK_BOOL && t3 == TK_BOOL)
			return TK_BOOL;

		puts("Invalid Type for the Operation");
		exit(0);
	}
	else if (t1 == TK_REAL || t3 == TK_REAL){

		return TK_REAL;

	}
	else{

		return TK_NUM;
	}
}

string convertRelacional(int t1, string t1_label, int t3, string t3_label){
	int teste = checkType(t1, t3);
	string toFloat = "", linha = "";
	if (teste == TK_REAL){
		if(t1 == TK_NUM){
			toFloat = t1_label;
			linha = "\tfloat " + getVarName() + " = " + toFloat +";\n";
		}
		else if (t3 == TK_NUM){
			toFloat = t3_label;
			linha = "\tfloat " + getVarName() + " = " + toFloat +";\n";
		}
	}

}
