//Mexer no BOOLEAN

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

typedef struct atributos atributos;
typedef struct variavel
{
	string tipo;
	string nome_var;
	string nome_temp;

} variavel;

// typedef

std::map<string, variavel> varTable;


// Functions
string getTempOnTable(string label);
string getVarType(int);
int checkType(int, int);
atributos castFunction(int, string, int, string, int, string);
void createLog (string name, string toWrite, bool);
variavel createVar(string, string, string);
int getTokenType(string);
int checkTypeArith(int, int);
atributos castArith(atributos, atributos, string);
atributos castFunctionArith(int, string, int, string, int, string);
string declararVariaveis();
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
%token TK_IF TK_WHILE

%start S
%left ')'
%left '+' '-'
%left '*' '/'
%left '('
%right '^' '<' '>' TK_GTE TK_LTE TK_NEQUAL TK_EQUAL TK_NOT '='

%%

S 			: TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout <<"\n\n/*Compilador Bolado*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\nint main(void)\n{\n" << declararVariaveis() << $5.traducao << "\treturn 0;\n}" << endl;
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
				i++;
			}
			| ATRIB ';'
			{
				$$ = $1;
				i++;
			}
			;

DECLARATION : TYPE VARLIST
			{
				$2.tipo = $1.tipo;
				$$.traducao = $1.traducao + $2.traducao;
				// $$.tipo = ;
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
				$$.traducao = $1.traducao + $3.traducao;// +"\t" + getVarType($0.tipo) + " "+ varName + "; \n";
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
				$$.tipo = $1.tipo;
				i++;
			}
			|TK_ID
			{
				// COLOCAR no HASH
				string varName = getVarName();
				$$.label = $1.label;
				$$.traducao = $1.traducao;// + "\t" + getVarType($0.tipo)+ " "+ varName + "; \n";
				createLog("Name", getVarType($0.tipo) + " "+ $$.label + " - " + varName, appendLogFile);
				variavel v = createVar($$.label, getVarType($0.tipo), varName);
				std::cout << "Tipo " << getVarType($0.tipo) << " com i = "<< i<< std::endl;
				varTable[v.nome_var] = v;
			}
			;

ATRIB 		: TK_ID '=' E
			{
				string varName = getTempOnTable($1.label);
				string infere_tipo = "", store = "";
				variavel v;

				std::cout << "Tipo da Atrib"<< getVarType($0.tipo) << std::endl;

				//variavel n existe na tabela
				if(varName == ""){
					varName = getVarName();


					if(getVarType($0.tipo) == ""){
						infere_tipo = getVarType($3.tipo);
					}
					else
						infere_tipo = getVarType($0.tipo);


					v = createVar($$.label, infere_tipo, varName);

					// std::cout << "Tipo " << getVarType($0.tipo) << " com i = "<< i<< std::endl;
					// std::cout << "(VAR3) Tipo " << getVarType($3.tipo) << " com i = "<< i<< std::endl;

					varTable[v.nome_var] = v;

				}
				// Cast na atribuição com Temp "Store"
				if( (varTable[$1.label].tipo != getVarType($3.tipo) ) ){
					puts ("Cast Atrib");
					store = getVarName();
					string linha =  store + " = (" +varTable[$1.label].tipo+") " + $3.label + ";\n";
					string linha2 = "\t"  + varName + " = " + store + ";\n";
					$$.traducao = $1.traducao + $3.traducao + "\t"  + linha + linha2;

					variavel v = createVar(store, infere_tipo,store);
					varTable[store] = v;
				}
				// Tipo Inferido ou cast não necessário
				else
					$$.traducao = $1.traducao + $3.traducao+ "\t"+ infere_tipo + ' '+ varName  + " = " + $3.label +";\n";

				i++;
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
				$$.traducao = $2.traducao + "\t" + varName +" = " + "-" + $2.label +";\n";
				variavel v = createVar(varName, getVarType($$.tipo), varName);
				varTable[varName] = v;

			}
 			| E '+' E
			{
				$$ = castArith($1, $3, "+");
			}
			| E '-' E
			{
				$$ = castArith($1, $3, "-");
			}
			| E '*' E
			{
				$$ = castArith($1, $3, "*");
			}
			| E '/' E
			{
				$$ = castArith($1, $3, "/");
			}
			// | E '^' E
			// {
			// 	$$.tipo = checkType($1.tipo, $3.tipo);
			// 	string varName = getVarName();
			// 	$$.traducao = $1.traducao + $3.traducao + "\t" +getVarType($$.tipo)+ " " + varName +" = " + "pow ("+ $1.label +" , "+ $3.label + ")"+";\n";
			// 	$$.label = varName;
			//
			// }
			| E '>' E
			{
				$$.tipo = TK_TIPO_BOOL;
				atributos atr = castFunction($1.tipo, $1.label, $3.tipo, $3.label, $$.tipo, ">");
				$$.traducao = $1.traducao + $3.traducao + atr.traducao;
				$$.label = atr.label;
			}
			| E '<' E
			{
				$$.tipo = TK_TIPO_BOOL;
				atributos atr = castFunction($1.tipo, $1.label, $3.tipo, $3.label, $$.tipo, "<");
				$$.traducao = $1.traducao + $3.traducao + atr.traducao;
				$$.label = atr.label;
			}
			| E TK_GTE E
			{
				$$.tipo = TK_TIPO_BOOL;
				atributos atr = castFunction($1.tipo, $1.label, $3.tipo, $3.label, $$.tipo, ">=");
				$$.traducao = $1.traducao + $3.traducao + atr.traducao;
				$$.label = atr.label;
			}
			| E TK_LTE E
			{
				$$.tipo = TK_TIPO_BOOL;
				atributos atr = castFunction($1.tipo, $1.label, $3.tipo, $3.label, $$.tipo, "<=");
				$$.traducao = $1.traducao + $3.traducao + atr.traducao;
				$$.label = atr.label;
			}
			| E TK_EQUAL E
			{
				$$.tipo = TK_TIPO_BOOL;
				atributos atr = castFunction($1.tipo, $1.label, $3.tipo, $3.label, $$.tipo, "==");
				$$.traducao = $1.traducao + $3.traducao + atr.traducao;
				$$.label = atr.label;
			}
			| E TK_NEQUAL E
			{
				$$.tipo = TK_TIPO_BOOL;
				atributos atr = castFunction($1.tipo, $1.label, $3.tipo, $3.label, $$.tipo, "!=");
				$$.traducao = $1.traducao + $3.traducao + atr.traducao;
				$$.label = atr.label;
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
				$$.traducao = "\t" +varName + " = " + $1.label + ";\n";
				$$.label = varName;

				variavel v = createVar(varName, getVarType($$.tipo), varName);
				varTable[varName] = v;
			}
			| TK_NUM
			{
				$$.tipo = TK_TIPO_INT;
				string varName = getVarName();
				$$.traducao = "\t" +varName + " = " + $1.label + ";\n";
				$$.label = varName;
				variavel v = createVar(varName, getVarType($$.tipo), varName);
				varTable[varName] = v;
			}
			| TK_BOOL
			{
				$$.tipo = TK_TIPO_BOOL;
				string varName = getVarName();
				// puts("Estou aqui");
				$$.traducao = "\t" + varName+ " = " + $1.label + ";\n";
				$$.label = varName;
				variavel v = createVar(varName, getVarType($$.tipo), varName);
				varTable[varName] = v;
			}
			| TK_CHAR
			{
				// puts("Estou aqui");
				$$.tipo = TK_TIPO_CHAR;
				string varName = getVarName();
				$$.traducao = "\t" + varName + " = " + $1.label + ";\n";
				$$.label = varName;
				variavel v = createVar(varName, getVarType($$.tipo), varName);
				varTable[varName] = v;
			}
			| TK_ID
			{

				string id = getTempOnTable($1.label);

				if (id == ""){
					cout << "Erro de Compilação Variavel '" << $1.label << "' inexistente" <<endl;
					exit(0);
				}
				else{

					$$.traducao = $1.traducao;
					$$.label = id;
					$$.tipo = getTokenType(varTable[$1.label].tipo);
				}
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
		linhas += var.tipo + "\t" + var.nome_var + "\t" + var.nome_temp + "\n";

	}
	createLog("varTable", linhas, false);


	return 0;
}

string declararVariaveis(){

	string linhas;
	for (std::map<string,variavel>::iterator it=varTable.begin(); it!=varTable.end(); ++it){
		variavel var = it->second;
		linhas += "\t" + var.tipo + ' ' + var.nome_temp + ";\n";

	}
	linhas += "\n";
	return linhas;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}

int getTokenType(string type){
	if(type == "int")
		return TK_TIPO_INT;
	if(type ==  "float")
		return TK_TIPO_FLOAT;
	if(type == "char")
		return TK_TIPO_CHAR;
	if(type == "bool")
		return TK_TIPO_INT;

}

string getVarType(int type){
	if(type == TK_TIPO_INT)
		return "int";
	if(type == TK_TIPO_FLOAT )
		return "float";
	if(type == TK_TIPO_CHAR)
		return "char";
	if(type == TK_TIPO_BOOL)
		return "int";
}

int checkType (int t1, int t3){

	//cout << "Tipo1 " << getVarType(t1) << "Tipo3 " << getVarType(t3) << endl;
	if ( (t1 != TK_TIPO_INT && t1 != TK_TIPO_FLOAT) || (t3 != TK_TIPO_INT && t3 != TK_TIPO_FLOAT) ) {

		if (t1 == TK_TIPO_BOOL && t3 == TK_TIPO_BOOL)
			return TK_TIPO_BOOL;

		else if (t1 == TK_TIPO_CHAR && t3 == TK_TIPO_CHAR)
			return TK_TIPO_CHAR;

		puts("Invalid Type for the Operation");
		//exit(0);
	}
	else if (t1 == TK_TIPO_FLOAT || t3 == TK_TIPO_FLOAT){

		return TK_TIPO_FLOAT;

	}
	else{

		return TK_TIPO_INT;
	}
}

atributos castFunction(int t1, string t1_label, int t3, string t3_label, int t0, string sinal){
	int teste = checkType(t1, t3);
	string linha = "", linha2 = "";

	string varName = getVarName();
	atributos retorno;

	if (teste == TK_TIPO_FLOAT){

		string store = getVarName();
		retorno.label = store;

		variavel v = createVar(varName, getVarType(teste), varName);
		varTable[varName] = v;
		v = createVar(store, getVarType(teste), store);
		varTable[store] = v;

		if(t1 == TK_TIPO_INT){
			linha = "\t" + varName + " = (float) " + t1_label +";\n";
			linha2 = "\t" + store +" = "+ varName + " " + sinal + " " +t3_label +";\n";
		}
		else if (t3 == TK_TIPO_INT){
			linha = "\tfloat " + varName + " = (float) " + t3_label +";\n";
			linha2 = "\t" + store +" = "+ t1_label + " " + sinal + " " + varName +";\n";
		}
	}
	else if (teste == TK_TIPO_INT){

		linha2 = "\t" + varName +" = "+ t1_label + " " + sinal + " " + t3_label +";\n";
		variavel v = createVar(varName, getVarType(teste), varName);
		varTable[varName] = v;
	}

	retorno.traducao = linha + linha2;
	retorno.tipo = t0;
	return retorno;

}
atributos castFunctionArith(int t1, string t1_label, int t3, string t3_label, int t0, string sinal){
	int teste = checkType(t1, t3);
	string linha = "", linha2 = "";

	string varName = getVarName();
	string store = getVarName();
	if (teste == TK_TIPO_FLOAT){

		variavel v = createVar(varName, getVarType(teste), varName);
		varTable[varName] = v;
		v = createVar(store, getVarType(teste), store);
		varTable[store] = v;

		if(t1 == TK_TIPO_INT){
			linha = "\t" + varName + " = (float) " + t1_label +";\n";
			linha2 = "\t" + store +" = "+ varName + " " + sinal + " " +t3_label +";\n";
		}
		else if (t3 == TK_TIPO_INT){
			linha = "\t" + varName + " = (float) " + t3_label +";\n";
			linha2 = "\t" + store +" = "+ t1_label + " " + sinal + " " + varName +";\n";
		}
	}
	atributos retorno;
	retorno.traducao = linha + linha2;
	retorno.label = store;
	retorno.tipo = t0;
	return retorno;

}

int checkTypeArith(int t1, int t3){
	if ( (t1 != TK_TIPO_INT && t1 != TK_TIPO_FLOAT) || (t3 != TK_TIPO_INT && t3 != TK_TIPO_FLOAT) ) {
		puts("Invalid Types for Arithmetics Operators!");
		exit(0);

	}
	if(t1 == TK_TIPO_FLOAT || t3 == TK_TIPO_FLOAT)
		return TK_TIPO_FLOAT;

	else
		return TK_TIPO_INT;
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
atributos castArith(atributos s1, atributos s3, string sinal){

	atributos ss;
	ss.tipo = checkTypeArith(s1.tipo, s3.tipo);
	//Sem Cast
	if (s1.tipo == s3.tipo){
		string varName = getVarName();
		ss.traducao = s1.traducao + s3.traducao + "\t" + varName + " = "+ s1.label +" " + sinal + " "+ s3.label +";\n";
		ss.label = varName;

		variavel v = createVar(varName, getVarType(ss.tipo), varName);
		varTable[varName] = v;
	}
	//Com cast
	else{
		atributos atr = castFunctionArith(s1.tipo, s1.label, s3.tipo, s3.label, ss.tipo, sinal);
		ss.traducao = s1.traducao + s3.traducao + atr.traducao;
		ss.label = atr.label;
	}
	return ss;

}
