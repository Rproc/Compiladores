%{
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>


#define YYSTYPE atributos

using namespace std;


//Variaveis Globais
bool appendLogFile = true; //falso apaga a porra toda do arquivo, DEIXE TRUE
int curVar = 0;
int i = 0;
struct atributos
{
	string label;
	string traducao;
	int tipo;
};

typedef struct variavel
{
	string tipo;
	string nome_var;
	string nome_temp;

} variavel;



std::map<string, variavel> varTable;


// Functions
string getTempOnTable(string label);
string getVarType(int);
int checkType(int, int);
string convertRelacional(int, string, int, string);
void createLog (string name, string toWrite, bool);
variavel createVar(string, string, string);
int yylex(void);
void yyerror(string);


string getVarName(){
	return "temp" + to_string(++curVar);
}



%}

%token TK_NUM TK_REAL TK_CHAR TK_BOOL
%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_CHAR TK_TIPO_BOOL
%token TK_FIM TK_ERROR
%token TK_EQUAL TK_GTE TK_LTE TK_NEQUAL TK_MAIOR TK_MENOR
%token TK_AND TK_OR TK_NOT

%start S
%left ')'
%left '+' '-'
%left '*' '/'
%left '('
%right '^' '<' '>' TK_GTE TK_LTE TK_NEQUAL TK_EQUAL TK_NOT '='

%%

S 			: TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout <<"\n\n /*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\nint main(void)\n{\n" << $5.traducao << "\treturn 0;\n}" << endl;
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
			| DECLARATION ';'
			{
				$$ = $1;
				// puts("declaraocao Estou aqui");
				i++;
				std::cout << "Passei em decl (após COM) com i = " << i << std::endl;
			}
			| ATRIB ';'
			{
				$$ = $1;
				i++;
				std::cout << "Passei em ATRIB (após COM) com i = " << i << std::endl;
			}
			;

DECLARATION : TYPE VARLIST
			{
				$$.traducao = $1.traducao + $2.traducao;
				$2.tipo = $1.tipo;
			}
			;

TYPE		: TK_TIPO_INT
			{
				$$.tipo = TK_TIPO_INT;
				$$.traducao = $1.traducao;
			}
			| TK_TIPO_FLOAT
			{
				$$.tipo = TK_TIPO_FLOAT;
				$$.traducao = $1.traducao;
			}
			| TK_TIPO_CHAR
			{
				$$.tipo = TK_TIPO_CHAR;
				$$.traducao = $1.traducao;
			}
			| TK_TIPO_BOOL
			{
				$$.tipo = TK_TIPO_BOOL;
				$$.traducao = $1.traducao;
			}
			;

VARLIST		: VARLIST ',' TK_ID
			{
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao +"\t" + getVarType($0.tipo) + " "+ varName + "; \n";
				createLog("Name", getVarType($0.tipo) + " " + $3.label + " - " + varName, appendLogFile);
				variavel v = createVar($3.label, getVarType($0.tipo), varName);
				varTable[v.nome_var] = v;
			}
			| VARLIST ',' ATRIB
			{
				$$.traducao = $1.traducao + $3.traducao;
			}
			| ATRIB
			{
				$$.traducao = $1.traducao;
				i++;
				std::cout << "Passei em atrib (após VL) com i = " << i << std::endl;
			}
			|TK_ID
			{
				// COLOCAR no HASH
				string varName = getVarName();
				$$.label = $1.label;
				$$.traducao = $1.traducao + "\t" + getVarType($0.tipo)+ " "+ varName + "; \n";
				createLog("Name", getVarType($0.tipo) + " "+ $$.label + " - " + varName, appendLogFile);
				variavel v = createVar($$.label, getVarType($0.tipo), varName);
				varTable[v.nome_var] = v;
			}
			;

ATRIB 		: TK_ID '=' E
			{
				string varName = getTempOnTable($1.label);
				string infere_tipo = "";
				if(varName == ""){
					varName = getVarName();
					variavel v = createVar($$.label, getVarType($3.tipo), varName);
					varTable[v.nome_var] = v;

					//se a variavel nao esta no mapa cria-se e seta o tipo
					infere_tipo = getVarType($3.tipo) + " ";
				}
				$$.traducao = $1.traducao + $3.traducao+ "\t"+ infere_tipo + varName  +" = " + $3.label +";\n";
				i++;
				std::cout << "Estou em ATRIB " << i << ' ' << getVarType($0.tipo) << std::endl;
				createLog("Name", getVarType($3.tipo) + " "+ $$.label + " - " + varName, appendLogFile);
			}
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
				$$.traducao = $1.traducao + $3.traducao + "\t" +getVarType($$.tipo)+ " " + varName +" = "+ $1.label +" * "+ $3.label +";\n";
				$$.label = varName;

			}
			| E '/' E
			{
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t"+getVarType($$.tipo)+ " " +  varName +" = "+ $1.label +" / "+ $3.label +";\n";
				$$.label = varName;
			}
			| E '^' E
			{
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t" +getVarType($$.tipo)+ " " + varName +" = " + "pow ("+ $1.label +" , "+ $3.label + ")"+";\n";
				$$.label = varName;

			}
			| E '>' E
			{
				$$.tipo = TK_TIPO_BOOL;
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+getVarType($$.tipo)+ " " + varName +" = "+ $1.label +" > "+ $3.label +";\n";
				cout << getVarType($$.tipo) << endl;
				$$.label = varName;
			}
			| E '<' E
			{
				$$.tipo = TK_TIPO_BOOL;
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+getVarType($$.tipo)+ " " + varName +" = "+ $1.label +" < "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_GTE E
			{
				$$.tipo = TK_TIPO_BOOL;
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+getVarType($$.tipo)+ " " + varName +" = "+ $1.label +" >= "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_LTE E
			{
				$$.tipo = TK_TIPO_BOOL;
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+getVarType($$.tipo)+ " " + varName +" = "+ $1.label +" <= "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_EQUAL E
			{
				$$.tipo = TK_TIPO_BOOL;
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+getVarType($$.tipo)+ " " + varName +" = "+ $1.label +" == "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_NEQUAL E
			{
				$$.tipo = TK_TIPO_BOOL;
				string linha = convertRelacional($1.tipo, $1.label, $3.tipo, $3.label);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + linha +"\t"+getVarType($$.tipo)+ " " + varName +" = "+ $1.label +" != "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_AND E
			{
				$$.tipo = TK_TIPO_BOOL;
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t"+getVarType($$.tipo)+ " " +  varName +" = "+ $1.label +" && "+ $3.label +";\n";
				$$.label = varName;
			}
			| E TK_OR E
			{
				$$.tipo = TK_TIPO_BOOL;
				$$.tipo = checkType($1.tipo, $3.tipo);
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao + "\t"+getVarType($$.tipo)+ " " +  varName +" = "+ $1.label +" || "+ $3.label +";\n";
				$$.label = varName;
			}
			| TK_NOT E
			{
				$$.tipo = checkType($2.tipo, $2.tipo);
				string varName = getVarName();
				$$.traducao = $2.traducao + "\t"+getVarType($$.tipo)+ " " +  varName +" = " "! "+ $2.label +";\n";
				$$.label = varName;
			}
			| TK_REAL
			{
				$$.tipo = TK_TIPO_FLOAT;
				string varName = getVarName();
				$$.traducao = "\t" + getVarType($$.tipo) + " "+varName+ " = " + $1.label + ";\n";
				$$.label = varName;
			}
			| TK_NUM
			{
				$$.tipo = TK_TIPO_INT;
				string varName = getVarName();
				$$.traducao = "\t"+ getVarType($$.tipo) + " "+varName+ " = " + $1.label + ";\n";
				$$.label = varName;
			}
			| TK_BOOL
			{
				$$.tipo = TK_TIPO_BOOL;
				string varName = getVarName();
				// puts("Estou aqui");
				$$.traducao = "\t"+ getVarType($$.tipo) + " "+varName+ " = " + $1.label + ";\n";
				$$.label = varName;
			}
			| TK_CHAR
			{
				// puts("Estou aqui");
				$$.tipo = TK_TIPO_CHAR;
				string varName = getVarName();
				$$.traducao = "\t" + getVarType($$.tipo) + " " + varName + " = " + $1.label + ";\n";
				$$.label = varName;

			}
			| TK_ID
			{
				$$.traducao = $1.traducao;
				//puts("Estou aqui");
				$$.label = $1.label;

			}
			;

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{

	//criar datamap em arquivo




	yyparse();
	// show content:
	string linhas;
	for (std::map<string,variavel>::iterator it=varTable.begin(); it!=varTable.end(); ++it){
		variavel var = it->second;
		linhas += var.tipo + " " + var.nome_var + " " + var.nome_temp + "\n";

	}
	createLog("varTable", linhas, false);


	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}

string getVarType(int type){
	if(type == TK_TIPO_INT)
		return "int";
	if(type == TK_TIPO_FLOAT )
		return "float";
	if(type == TK_TIPO_CHAR)
		return "char";
	if(type == TK_TIPO_BOOL)
		return "bool";
}

int checkType (int t1, int t3){
	if ( (t1 != TK_TIPO_INT && t1 != TK_TIPO_FLOAT) || (t3 != TK_TIPO_INT && t3 != TK_TIPO_FLOAT) ) {

		if (t1 == TK_TIPO_BOOL && t3 == TK_TIPO_BOOL)
			return TK_TIPO_BOOL;

		puts("Invalid Type for the Operation");
		exit(0);
	}
	else if (t1 == TK_TIPO_FLOAT || t3 == TK_TIPO_FLOAT){

		return TK_TIPO_FLOAT;

	}
	else{

		return TK_TIPO_INT;
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
	return linha;

}

void createLog (string name, string toWrite, bool append){

	FILE *p_arquivo;
	//char *nome = "arquivo.txt";
	string parameter = "w";

	if(append)
		parameter = "a";

	if((p_arquivo = fopen(name.c_str(), parameter.c_str()) ) == NULL)
	{
		printf("\n\nNao foi possivel abrir o arquivo.\n");
		return;
	}

	fprintf(p_arquivo,"%s\n", toWrite.c_str());

	fclose(p_arquivo);

}

variavel createVar(string nome_var, string tipo, string nome_temp){

	variavel var;
	var.tipo = tipo;
	var.nome_var = nome_var;
	var.nome_temp = nome_temp;

	return var;
}

string getTempOnTable(string label){

	if ( varTable.count(label) ){
		//variavel ja foi declarada
		return varTable[label].nome_temp;
	}else{
		return "";
	}

}
