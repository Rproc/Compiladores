//Mexer no BOOLEAN

%{
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <stdio.h>
#include "escopo.h"
#include "loopStack.h"

#define YYSTYPE atributos

using namespace std;


string gambiarra_print = "";
string gambiarra_read = "";

//Variaveis Globais
bool appendLogFile = true; //falso apaga a porra toda do arquivo, DEIXE TRUE
int curVar = 0;
int curLabel = 0;
int i = 0;
struct atributos
{
	string label;
	string traducao;
	int tipo;
	int tamanho;
};

typedef struct atributos atributos;

//std::map<string, variavel> varTable;
map_stack* pilha = createMapStack();
LoopStack* pilhaLoops = createLoopStack();



//VarTable escopoGlobal;
// pushEscopo(pilha, escopoGlobal);

Declaracoes declaracoes;



// Functions
variavel getVarOnStack(string label);
string getVarType(int);
int checkType(int, int);
atributos castFunction(int, string, int, string, int, string);
void createLog (string name, string toWrite, bool);
int getTokenType(string);
int checkTypeArith(int, int);
atributos castArith(atributos, atributos, string);
atributos castFunctionArith(int, string, int, string, int, string);
string declararVariaveis();
string getLabel(int);
atributos concatString (atributos,atributos);
int getNumber(string str);

void createVarTableLog(VarTable);

int yylex(void);
void yyerror(string);


string getVarName(){
	return "temp" + to_string(++curVar);
}



%}

%token TK_NUM TK_REAL TK_CHAR TK_BOOL TK_STRING TK_GLOBAL
%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_CHAR TK_TIPO_BOOL TK_TIPO_STRING
%token TK_FIM TK_ERROR
%token TK_EQUAL TK_GTE TK_LTE TK_NEQUAL TK_MAIOR TK_MENOR
%token TK_AND TK_OR TK_NOT
%token TK_IF TK_WHILE TK_DO TK_FOR  TK_ELSE
%token TK_BREAK TK_BREAK_ALL TK_BREAK_FUNC TK_CONTINUE 
%token TK_PRINT TK_READ
%token TK_PP TK_MM

%start S
%left ')'
%left '+' '-'
%left '*' '/'
%left '('
%right '^' '<' '>' TK_GTE TK_LTE TK_NEQUAL TK_EQUAL TK_NOT '='

%%

S			: PUSH_SCOPE T POP_SCOPE
			{
				$$.traducao = $2.traducao;
			}
			
			;

T			:TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{ 
				cout <<"\n\n/*Compilador Bolado*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n"  << declararVariaveis() << "\nint main(void)\n{\n" << $5.traducao << "\treturn 0;\n}" << endl;
				
				ofstream outputFile;
				outputFile.open("src.c");
				outputFile <<"\n\n/*Compilador Bolado*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n"  << declararVariaveis() << "\nint main(void)\n{\n" << $5.traducao << "\treturn 0;\n}" << endl;
				outputFile.close();
			}
			;

BLOCO		: PUSH_SCOPE '{' COMANDOS '}' POP_SCOPE
			{
				
				$$.traducao = $3.traducao;
				
			}
			;

PUSH_SCOPE: {
				VarTable escopo;
				pushEscopo(pilha,escopo);
				
				$$.traducao = "";
				$$.label = "";
			}
			
POP_SCOPE:	{
			//	cout << "escopoAtual " << pilha->escopoAtual << endl;
				createVarTableLog(pilha->escopos[pilha->escopoAtual]);
				pop(pilha);
				
				$$.traducao = "";
				$$.label = "";
			};

COMANDOS	: COMANDO COMANDOS
			{

				$$.traducao = $1.traducao + $2.traducao;
				
				//cout << "Traducao Comandos" << endl << $2.traducao << endl;
			}
			|
			{
				$$.traducao = "";
			}
			;

COMANDO 	: E ';'
			| TK_IF '(' E ')' BLOCO
			{
				// VarTable varTableEscopo;
				// pushEscopo(escopos, varTableEscopo);

			    int teste = checkType($3.tipo, $3.tipo);

			    if (teste != TK_TIPO_BOOL && teste != TK_TIPO_INT){
			        puts("Invalid Type for the IF Statment");
			        exit(0);
			    }
				string varName = getVarName();
				string gotoLabel = getLabel(TK_IF);
				string linha = "\t" + varName + " = !" + $3.label + ";\n";
				string showLabel = "\t"+gotoLabel + ":\n\n";

				variavel v = createVar(varName, getVarType(teste), varName);
				addVar2Escopo(pilha, v);//[varName] = v;
				declaracoes.push_back(v);

				string stmt = "\n\tif(" + varName + ") " + "goto " + gotoLabel +";\n" + $5.traducao + "\n" + showLabel;
			    $$.traducao = $3.traducao + linha + stmt;
			}
			| TK_IF '(' E ')' BLOCO TK_ELSE BLOCO
			{
				// VarTable varTableEscopo;
				// pushEscopo(escopos, varTableEscopo);

			    int teste = checkType($3.tipo, $3.tipo);

			    if (teste != TK_TIPO_BOOL && teste != TK_TIPO_INT){
			        puts("Invalid Type for the IF Statment");
			        exit(0);
			    }
				string varName = getVarName();
				//END_IF
				string gotoLabel = getLabel(TK_IF);
				
				//INICIO_ELSE
				
				string inicio_else = "inicio_else_" + to_string(curLabel);
				
				
				string linha = "\t" + varName + " = !" + $3.label + ";\n";
				//string showLabel = gotoLabel + ":\n\n";

				variavel v = createVar(varName, getVarType(teste), varName);
				addVar2Escopo(pilha, v);//[varName] = v;
				declaracoes.push_back(v);

				string stmt = "\n\tif(" + varName + ") " + "goto " + inicio_else +";\n" + $5.traducao + "\n\tgoto " + gotoLabel + ";\n\t" + inicio_else + ":\n" + $7.traducao + "\n\t" + gotoLabel + ":\n";
				
				
			    $$.traducao = $3.traducao + linha + stmt;
			}
			| PUSH_LOOP LOOP POP_LOOP
			{
				$$.traducao = $2.traducao;
				
				//cout << "Traducao do Push_Loop_Pop " << "\n" << $2.traducao << endl;
			}
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
			| PRINT ';' 
			{
				$$ = $1;
				gambiarra_print = "";
			}
			| READ ';'
			{
				$$ = $1;	
			}
			| TK_BREAK ';'{
			 	
			 	if(pilhaLoops->loops.empty()){
			 		cout << "Erro de compilação. 'break' deveria estar dentro de um laço de repetição ";
			 		exit(0);
			 	}else{
			 		Loop loopAtual = getLoop(pilhaLoops);
			 		$$.traducao = "\tgoto " + loopAtual.endLabel+";//break comum\n";
			 	}
			 	
			 }
			| TK_BREAK_ALL ';'{
			 	
			 	if(pilhaLoops->loops.empty()){
			 		cout << "Erro de compilação. 'break' deveria estar dentro de um laço de repetição ";
			 		exit(0);
			 	}else{
			 		Loop loopMaisExterno = pilhaLoops->loops[0];
			 		$$.traducao = "\tgoto " + loopMaisExterno.endLabel+";//break all\n";
			 	}
			 	
			 }
			| TK_BREAK_FUNC ';' {
			 	
			 	//cout << "Break func " << $1.label << " parametro " << getNumber($1.label) << endl;
			 	$$.traducao = $1.traducao;
			 
			 	int parametro_break = getNumber($1.label);
			 	if(pilhaLoops->loops.size() < parametro_break ){
			 		cout << "Erro de compilação. 'break' deveria estar dentro de um laço de repetição ";
			 		exit(0);
			 	}else{
			 		Loop loop = pilhaLoops->loops[ pilhaLoops->loops.size() - parametro_break ];
			 		$$.traducao = "\tgoto " + loop.endLabel+";//break_func\n";
			 		
			 		//std::cout << "DANDO GO TO PARA " << loop.beginLabel << std::endl;
			 	}
			 	
			} 
			| TK_CONTINUE ';'{
				
				 if(pilhaLoops->loops.empty()){
			 		cout << "Erro de compilação. 'continue' deveria estar dentro de um laço de repetição ";
			 		exit(0);
			 	}else{
			 		Loop loopAtual = getLoop(pilhaLoops);
			 		$$.traducao = "\tgoto " + loopAtual.continueLabel + ";//continue comum\n";
			 	}			
			}
			| GLOBAL ';'
			{
				$$ = $1;	
			}
			| OPERADOR_UNARIO ';'
			{
				$$ = $1;
			}
			| OPERADOR_COMPOSTO ';'
			{
				
				$$ = $1;
			}

			;
			
OPERADOR_COMPOSTO:	TK_ID '+' '=' E 
					{
						variavel var = getVarOnStack($1.label);
						if(var.tipo != getVarType(TK_TIPO_INT) && var.tipo != getVarType(TK_TIPO_FLOAT)){
							cout << "operador += não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//caminho feliz
						//string linha = $1.label + " = " + $1.label + " + " + $3.label; 

						
						// Cast na atribuição com Temp "Store"
						if( var.tipo != getVarType($4.tipo) ) {
							// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
							
							//string varName;
							string store = getVarName();
							string linha =  store + " = (" +var.tipo+") " + $4.label + ";\n";
							string linha2 = "\t"  + var.nome_temp + " = " + store + ";\n";
							
							$$.traducao = $1.traducao + $4.traducao + "\t"  + linha + linha2;
		
							variavel v = createVar(store, getVarOnStack($1.label).tipo,store);
		
							addVar2Escopo(pilha, v);
							declaracoes.push_back(v);
					
						}	// Tipo Inferido ou cast não necessário
						else{
							if (getVarType($4.tipo) == "char*"){
								cout << "Este Operador += não é destinado a Strings" << endl;
							}
							else{
								string linha = "\t" + var.nome_temp + " = " + var.nome_temp + " + " + $4.label +";\n";
								$$.traducao = $4.traducao+ "\n" + linha;
							}
								
							
						}
			
					
					}
					| TK_ID '-' '=' E 
					{
						variavel var = getVarOnStack($1.label);
						if(var.tipo != getVarType(TK_TIPO_INT) && var.tipo != getVarType(TK_TIPO_FLOAT)){
							cout << "operador -= não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//caminho feliz
						//string linha = $1.label + " = " + $1.label + " + " + $3.label; 

						
						// Cast na atribuição com Temp "Store"
						if( var.tipo != getVarType($4.tipo) ) {
							// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
							
							//string varName;
							string store = getVarName();
							string linha =  store + " = (" +var.tipo+") " + $4.label + ";\n";
							string linha2 = "\t"  + var.nome_temp + " = " + store + ";\n";
							
							$$.traducao = $1.traducao + $4.traducao + "\t"  + linha + linha2;
		
							variavel v = createVar(store, getVarOnStack($1.label).tipo,store);
		
							addVar2Escopo(pilha, v);
							declaracoes.push_back(v);
					
						}	// Tipo Inferido ou cast não necessário
						else{
							if (getVarType($4.tipo) == "char*"){
								cout << "Este Operador -= não é destinado a Strings" << endl;
							}
							else{
								string linha = "\t" + var.nome_temp + " = " + var.nome_temp + " - " + $4.label +";\n";
								$$.traducao = $4.traducao+ "\n" + linha;
							}
								
							
						}
					}
					| TK_ID '*' '=' E 
					{
						variavel var = getVarOnStack($1.label);
						if(var.tipo != getVarType(TK_TIPO_INT) && var.tipo != getVarType(TK_TIPO_FLOAT)){
							cout << "operador *= não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//caminho feliz
						//string linha = $1.label + " = " + $1.label + " + " + $3.label; 

						
						// Cast na atribuição com Temp "Store"
						if( var.tipo != getVarType($4.tipo) ) {
							// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
							
							//string varName;
							string store = getVarName();
							string linha =  store + " = (" +var.tipo+") " + $4.label + ";\n";
							string linha2 = "\t"  + var.nome_temp + " = " + store + ";\n";
							
							$$.traducao = $1.traducao + $4.traducao + "\t"  + linha + linha2;
		
							variavel v = createVar(store, getVarOnStack($1.label).tipo,store);
		
							addVar2Escopo(pilha, v);
							declaracoes.push_back(v);
					
						}	// Tipo Inferido ou cast não necessário
						else{
							if (getVarType($4.tipo) == "char*"){
								cout << "Este Operador *= não é destinado a Strings" << endl;
							}
							else{
								string linha = "\t" + var.nome_temp + " = " + var.nome_temp + " * " + $4.label +";\n";
								$$.traducao = $4.traducao+ "\n" + linha;
							}
								
						
						}
				
					}
					| TK_ID '/' '=' E 
					{
						variavel var = getVarOnStack($1.label);
						if(var.tipo != getVarType(TK_TIPO_INT) && var.tipo != getVarType(TK_TIPO_FLOAT)){
							cout << "operador /= não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//caminho feliz
						//string linha = $1.label + " = " + $1.label + " + " + $3.label; 

						
						// Cast na atribuição com Temp "Store"
						if( var.tipo != getVarType($4.tipo) ) {
							// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
							
							//string varName;
							string store = getVarName();
							string linha =  store + " = (" +var.tipo+") " + $4.label + ";\n";
							string linha2 = "\t"  + var.nome_temp + " = " + store + ";\n";
							
							$$.traducao = $1.traducao + $4.traducao + "\t"  + linha + linha2;
		
							variavel v = createVar(store, getVarOnStack($1.label).tipo,store);
		
							addVar2Escopo(pilha, v);
							declaracoes.push_back(v);
					
						}	// Tipo Inferido ou cast não necessário
						else{
							if (getVarType($4.tipo) == "char*"){
								cout << "Este Operador /= não é destinado a Strings" << endl;
							}
							else{
								string linha = "\t" + var.nome_temp + " = " + var.nome_temp + " / " + $4.label +";\n";
								$$.traducao = $4.traducao+ "\n" + linha;
							}
								
						
						}
				
					}
				
					;
			
OPERADOR_UNARIO:	TK_ID TK_PP 
					{
						
						variavel var = getVarOnStack($1.label);
						if(var.tipo != getVarType(TK_TIPO_INT)){
							cout << "operador ++ não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						string varName = getVarName();
						variavel v = createVar(varName, var.tipo, varName);
						
						//a = 4;
						// print(a++); printa 4
						// print(++a) printa 5
						
						addVar2Escopo(pilha, v);
						declaracoes.push_back(v);
						
						string linha = "\t" + varName + " =  1;\n";
						string linha2 = "\t" + var.nome_temp + " = "+ varName +" + " + var.nome_temp + ";\n";
						
						$$.traducao = linha + linha2;

	
					}
					| TK_PP TK_ID 
					{
						
						variavel var = getVarOnStack($1.label);
						if(var.tipo != getVarType(TK_TIPO_INT)){
							cout << "operador ++ não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//string varName = getVarName();
					//	variavel v = createVar(varName, var.tipo, varName);
						
						//a = 4;
						// print(a++); printa 4
						// print(++a) printa 5
						
						addVar2Escopo(pilha, var);
						declaracoes.push_back(var);
						
						//string linha = "\t" + varName + " =  1;\n";
						string linha2 = "\t" + var.nome_temp + " = " + var.nome_temp + " + "+ "1" + ";\n";
						
						$$.traducao = linha2;
					}
					| TK_ID TK_MM
					{
						
						variavel var = getVarOnStack($1.label);
						if(var.tipo != getVarType(TK_TIPO_INT)){
							cout << "operador -- não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						string varName = getVarName();
						variavel v = createVar(varName, var.tipo, varName);
						
						//a = 4;
						// print(a++); printa 4
						// print(++a) printa 5
						
						addVar2Escopo(pilha, v);
						declaracoes.push_back(v);
						
						string linha = "\t" + varName + " =  1;\n";
						string linha2 = "\t" + var.nome_temp + " = " + var.nome_temp + " - " + varName + ";\n";
						
						$$.traducao = linha + linha2;

	
					}
					| TK_MM TK_ID
					{
						
						variavel var = getVarOnStack($1.label);
						if(var.tipo != getVarType(TK_TIPO_INT)){
							cout << "operador ++ não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//string varName = getVarName();
					//	variavel v = createVar(varName, var.tipo, varName);
						
						//a = 4;
						// print(a++); printa 4
						// print(++a) printa 5
						
						addVar2Escopo(pilha, var);
						declaracoes.push_back(var);
						
						//string linha = "\t" + varName + " =  1;\n";
						string linha2 = "\t" + var.nome_temp + " = " + var.nome_temp + " - " + "1" + ";\n";
						
						$$.traducao = linha2;
					}
					;
			
GLOBAL: 	TK_GLOBAL TYPE TK_ID {
			

				//se variavel NAO existe no escopo global
				if ( pilha->escopos[0][$3.label].nome_var == ""  ){
					
					string varName = getVarName();
					variavel v = createVar($3.label, getVarType($2.tipo), varName);
					
					addVar2Global(pilha, v);
					declaracoes.push_back(v);

				}else{
					cout << "Variavel " << $3.label << " ja foi declarada no escopo global" <<endl;
					exit(0);
				}
	
			}
			|
			TK_GLOBAL TYPE TK_ID '=' E{
			
				//std::map<string,variavel>::iterator it;
			
				//busca no escopo global se variavel ja existe
				//it = pilha->escopos[0].find($3.label);
				
				//se variavel nao existe no escopo global
				if ( pilha->escopos[0][$3.label].nome_var == ""  ){
					
					string varName = getVarName();
					variavel v = createVar($3.label, getVarType($2.tipo), varName);
					
					addVar2Global(pilha, v);
					declaracoes.push_back(v);
					
									// Cast na atribuição com Temp "Store"
					if( v.tipo != getVarType($5.tipo) ) {
						// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
						string store = getVarName();
						string linha =  store + " = (" +v.tipo+") " + $5.label + ";\n";
						string linha2 = "\t"  + varName + " = " + store + ";\n";
						
						$$.traducao = $3.traducao + $5.traducao + "\t"  + linha + linha2;
	
						variavel v = createVar(store, getVarOnStack($3.label).tipo,store);
	
						addVar2Escopo(pilha, v);
						declaracoes.push_back(v);
				
					}	// Tipo Inferido ou cast não necessário
					else{
						if (getVarType($5.tipo) == "char*"){
							$$.traducao = $3.traducao + $5.traducao + "\tstrcpy(" + varName  + ", " + $5.label +");\n";
						}
						else
							$$.traducao = $3.traducao + $5.traducao + "\t" + varName  + " = " + $5.label +";\n";
						
					}
				
				}	
				//daqui
			}
			;
			
LOOP:		WHILE
			{ 
				$$ = $1;
			//	cout<< "traducao de while" << $1.traducao << endl;
				
			}
			| DO
			{
				$$ = $1;
			}
			| FOR
			{
				$$ = $1;
			}
			;

WHILE : 	TK_WHILE '(' E ')' BLOCO
			{
				int teste = checkType($3.tipo, $3.tipo);
	
				if (teste != TK_TIPO_BOOL && teste != TK_TIPO_INT){
					puts("Invalid Type for the WHILE Statment");
					exit(0);
				}
				string varName = getVarName();
				
				Loop loop = getLoop(pilhaLoops);
				
				//string beginLabel = "inicio" + getLabel(TK_WHILE);
				string beginLabel = loop.beginLabel;
				//curLabel--; //Gambiarra para ficar inicio_while_1 e fim_while_1
	
				// string endLabel = "fim" + getLabel(TK_WHILE);
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
	
				string linha = "\t" + varName + " = !" + $3.label + ";\n";
				string showLabel = "\tgoto "+ beginLabel + ";\n\n";
	
				variavel v = createVar(varName, getVarType(teste), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
				
				// parte que atualiza o indice do loop == $3.traducao + linha
				// o continueLabel esta para ser usado por um comando continue, caso nao haja um
				// ele é apenas um label vazio
				string stmt =  "\t" + beginLabel +":"+ "\tif(" + varName + ") " + "goto " + endLabel +";\n" + $5.traducao + "\n" + "\t" + 
				continueLabel + "://continueLabel\n" + $3.traducao + linha + showLabel + "\t"  + endLabel + ":\n\n";
			    $$.traducao = $3.traducao + linha + stmt;
				
			}
			;
DO			: TK_DO BLOCO TK_WHILE '(' E ')' ';'
			{
				int teste = checkType($5.tipo, $5.tipo);
	
				if (teste != TK_TIPO_BOOL && teste != TK_TIPO_INT){
					puts("Invalid Type for the DO...WHILE Statment");
					exit(0);
				}
				
				//string varName = getVarName();
				
				Loop loop = getLoop(pilhaLoops);
				
				string beginLabel = loop.beginLabel;
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
	
				string linha = "\tif(" + $5.label + ")";
				string showLabel = "\tgoto "+ beginLabel;
				
				//label do_while bloco
				string stmt  = "\t" + beginLabel + ":\n" + $2.traducao + "\n\t" + continueLabel + ":\n";
				stmt		+= $5.traducao + linha + showLabel + ";\n\t" + endLabel + ":\n"; 
				
				$$.traducao = stmt;
			}
			;
			
FOR:		TK_FOR '(' DECLARATION ';' E ';' ATRIB ')' BLOCO
			{
				//cout << "ENCONTREI UM FOR " << getVarType($5.tipo) <<" : " << $5.tipo <<endl;
				
				if( $5.tipo != TK_TIPO_BOOL ){
					cout <<  "ERRO DE COMPILACAO: for espera uma expressao boleana no segundo parametro" <<endl;
					exit(0);
				}
				
				string varName = getVarName();
				
				variavel v = createVar(varName, getVarType($5.tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
					
					
				Loop loop = getLoop(pilhaLoops);
				
				string beginLabel = loop.beginLabel;
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
				
				string linha = "\t" + varName + " = !" + $5.label + ";\n";
				
				string atrib_inicial = $3.traducao;
				string showLabel = "\n\t" + beginLabel + ": \n" + $5.traducao + linha + "\n";
				string verifica = "\tif(" + varName + ") " + "\tgoto "+ endLabel + ";\n";
				
				string dentroFor = $9.traducao + "\n\t" + continueLabel + ": \n" + $7.traducao + $5.traducao + linha + "\n";
				
				$$.traducao = atrib_inicial + showLabel + verifica + dentroFor + "\tgoto " + beginLabel + ";\n\t" + endLabel + ":\n";
			}
			|
			TK_FOR '(' DECLARATION ';' E ';' OPERADOR_UNARIO ')' BLOCO
			{
				//cout << "ENCONTREI UM FOR " << getVarType($5.tipo) <<" : " << $5.tipo <<endl;
				
				if( $5.tipo != TK_TIPO_BOOL ){
					cout <<  "ERRO DE COMPILACAO: for espera uma expressao boleana no segundo parametro" <<endl;
					exit(0);
				}
				
				string varName = getVarName();
				
				variavel v = createVar(varName, getVarType($5.tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
					
					
				Loop loop = getLoop(pilhaLoops);
				
				string beginLabel = loop.beginLabel;
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
				
				string linha = "\t" + varName + " = !" + $5.label + ";\n";
				
				string atrib_inicial = $3.traducao;
				string showLabel = "\n\t" + beginLabel + ": \n" + $5.traducao + linha + "\n";
				string verifica = "\tif(" + varName + ") " + "\tgoto "+ endLabel + ";\n";
				
				string dentroFor = $9.traducao + "\n\t" + continueLabel + ": \n" + $7.traducao + $5.traducao + linha + "\n";
				
				$$.traducao = atrib_inicial + showLabel + verifica + dentroFor + "\tgoto " + beginLabel + ";\n\t" + endLabel + ":\n";
			}
			|			
			TK_FOR '(' DECLARATION ';' E ';' OPERADOR_COMPOSTO ')' BLOCO
			{
				//cout << "ENCONTREI UM FOR " << getVarType($5.tipo) <<" : " << $5.tipo <<endl;
				
				if( $5.tipo != TK_TIPO_BOOL ){
					cout <<  "ERRO DE COMPILACAO: for espera uma expressao boleana no segundo parametro" <<endl;
					exit(0);
				}
				
				string varName = getVarName();
				
				variavel v = createVar(varName, getVarType($5.tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
					
					
				Loop loop = getLoop(pilhaLoops);
				
				string beginLabel = loop.beginLabel;
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
				
				string linha = "\t" + varName + " = !" + $5.label + ";\n";
				
				string atrib_inicial = $3.traducao;
				string showLabel = "\n\t" + beginLabel + ": \n" + $5.traducao + linha + "\n";
				string verifica = "\tif(" + varName + ") " + "\tgoto "+ endLabel + ";\n";
				
				string dentroFor = $9.traducao + "\n\t" + continueLabel + ": \n" + $7.traducao + $5.traducao + linha + "\n";
				
				$$.traducao = atrib_inicial + showLabel + verifica + dentroFor + "\tgoto " + beginLabel + ";\n\t" + endLabel + ":\n";
			}
			
			;
			
PUSH_LOOP: {
				string label = getLabel(TK_WHILE);
				
				//cout << "Pushando o Loop While" << endl;
				//string label = "loop_1";
				string beginLabel = "inicio" + label;
				string endLabel = "fim" + label;
				string continueLabel = "continue" + label;
				
				Loop loop;
				loop.endLabel = endLabel;
				loop.beginLabel = beginLabel;
				loop.continueLabel = continueLabel;
				
				
				pushLoop(loop, pilhaLoops);
				
				$$.traducao = "";
				$$.label = "";
			}
			
POP_LOOP:	{
				popLoop(pilhaLoops);
				
				//cout << "Popando o Loop While" << endl;

				
				$$.traducao = "";
				$$.label = "";
			};

PRINT : 		TK_PRINT TK_PRINT_ARGS
				{
				    //variavel v = getVarOnStack($2.label);
				    
					$$.traducao = gambiarra_print + "\tstd::cout "  + $2.traducao + " << std::endl;\n";
					
				//	cout << "traducao de print args = " <<  $2.traducao<<endl;
				//	cout  << "traducao de print = " <<  $$.traducao<<endl;
				}
				;
		
TK_PRINT_ARGS:	TK_PRINT_ARGS ',' TK_PRINT_ARG
				{
					$$.traducao = $1.traducao + $3.traducao;
					
					//cout << "derivacao print args" << $$.traducao << endl;
				}
				| TK_PRINT_ARG
				{
					$$.traducao = $1.traducao; 
				};
				
TK_PRINT_ARG:	E
				{
					gambiarra_print = $1.traducao;
					$$.traducao = " << " + $1.label;
				//	cout << "traducao de print arg = " <<  $$.traducao <<endl;
				//	cout << "gambiarra_print  = " <<  $1.traducao <<endl;
					
				};


READ:			TK_READ TK_READ_ARGS
				{

					$$.traducao = gambiarra_print + "\tstd::cin"  + $2.traducao + ";\n";

				}
TK_READ_ARGS:	TK_READ_ARGS ',' TK_READ_ARG
				{
					$$.traducao = $1.traducao + $3.traducao;
					
					//cout << "derivacao print args" << $$.traducao << endl;
				}
				| TK_READ_ARG
				{
					$$.traducao = $1.traducao; 
				};
				
TK_READ_ARG:	E
				{
					gambiarra_read = $1.traducao;
					$$.traducao = " >> " + $1.label;
				//	cout << "traducao de print arg = " <<  $$.traducao <<endl;
				//	cout << "gambiarra_print  = " <<  $1.traducao <<endl;
					
				};
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
			|
			TK_TIPO_STRING
			{
				$$.tipo = TK_TIPO_STRING;
				$$.traducao = $1.traducao;
			}
			;

VARLIST		: VARLIST ',' TK_ID
			{
				string varName = getVarName();
				$$.traducao = $1.traducao + $3.traducao;// +"\t" + getVarType($0.tipo) + " "+ varName + "; \n";
				createLog("Name", getVarType($0.tipo) + " " + $3.label + " - " + varName, appendLogFile);
				variavel v = createVar($3.label, getVarType($0.tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
			| VARLIST ',' ATRIB
			{
				$$.traducao = $1.traducao + $3.traducao;
				$1.tipo = $0.tipo;
				$3.tipo = $0.tipo;
				// cout << "Em " <<$1.label <<" Tipo do VARLIST em Var, Atrib: " << getVarType($0.tipo) << "\nEm "<< $3.label<< " Tipo da Atrib em Var, Atrib: " << getVarType($3.tipo) << endl;
			}
			| TK_ID '=' E
			{
				variavel var = getVarOnStack($1.label); //Buscar só no escopo atual
				string varName = "";
				$1.tamanho = $3.tamanho;

				string infere_tipo = "", store = "";
				//variavel v;

				//std::cout << "TK_ID = E" << endl;

				//variavel n existe na tabela
				if(varName == ""){
					varName = getVarName();
					// cout << "ENTREI NO IF " <<getVarType($0.tipo) << endl;

					if(getVarType($0.tipo) != ""){
					//	cout << "$0 tipo nao vazio" << endl;
						infere_tipo = getVarType($0.tipo);
						
					}
					else{
					//	cout << "$0 tipo vazio" << endl;
						infere_tipo = getVarType($3.tipo);
						
					}

					var = createVar($1.label, infere_tipo, varName);

					// std::cout << "Tipo " << getVarType($0.tipo) << " com i = "<< i<< std::endl;
					// std::cout << "(VAR3) Tipo " << getVarType($3.tipo) << " com i = "<< i<< std::endl;

					addVar2Escopo(pilha, var);
					declaracoes.push_back(var);

					
				}
				
				// Cast na atribuição com Temp "Store"
				if( (getVarOnStack($1.label).tipo != getVarType($3.tipo) ) ){
					// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
					store = getVarName();
					string linha =  store + " = (" +getVarOnStack($1.label).tipo+") " + $3.label + ";\n";
					string linha2 = "\t"  + varName + " = " + store + ";\n";
					$$.traducao = $1.traducao + $3.traducao + "\t"  + linha + linha2;

					variavel v = createVar(store, getVarOnStack($1.label).tipo,store);

					addVar2Escopo(pilha, v);
					declaracoes.push_back(v);
				}
				// Tipo Inferido ou cast não necessário
				else{
					if (getVarType($3.tipo) == "char*"){
						$$.traducao = $1.traducao + $3.traducao + "\tstrcpy(" + varName  + ", " + $3.label +");\n";
					}
					else
						$$.traducao = $1.traducao + $3.traducao + "\t" + varName  + " = " + $3.label +";\n";
					
					
				}
				
				i++;
				createLog("Name", getVarType($3.tipo) + " "+ $$.label + " - " + varName, appendLogFile);
			
			}
			|TK_ID
			{
				// COLOCAR no HASH
				string varName = getVarName();
				$$.label = $1.label;
				//$$.tamanho = 20;
				$$.traducao = $1.traducao;// + "\t" + getVarType($0.tipo)+ " "+ varName + "; \n";
				createLog("Name", getVarType($0.tipo) + " "+ $$.label + " - " + varName, appendLogFile);
				variavel v = createVar($$.label, getVarType($0.tipo), varName);
				v.tamanho = 20;
				// std::cout << "Tipo " << getVarType($0.tipo) << " com i = "<< i<< std::endl;
				addVar2Escopo(pilha, v);;
				declaracoes.push_back(v);
			}
			;

ATRIB 		: TK_ID '=' E
			{
				variavel var = getVarOnStack($1.label); //Buscar só no escopo atual
				string varName = var.nome_temp;
				
				//cout << $3.label <<" tam da E em atrib "<< $3.tamanho << endl;

				string infere_tipo = "", store = "";
				
				//usado para quando precisa dar free e outro malloc para alteracao de string
				string trad = "";
				//variavel v;

				//std::cout << "TK_ID = E" << endl;

				//variavel n existe na tabela
				if(varName == ""){
					varName = getVarName();
					// cout << "ENTREI NO IF " <<getVarType($0.tipo) << endl;

					if(getVarType($0.tipo) != ""){
					//	cout << "$0 tipo nao vazio" << endl;
						infere_tipo = getVarType($0.tipo);
						
					}
					else{
					//	cout << "$0 tipo vazio" << endl;
						infere_tipo = getVarType($3.tipo);
						
					}

					var = createVar($$.label, infere_tipo, varName);
					
					
					//se for string verificar o tamanho dela para realizar a copia 
					// que acontece no if de baixo
					if($3.tipo == TK_TIPO_STRING){
						variavel str = getVarOnStack($3.label);
						var.tamanho = str.tamanho;
						
						
						//verifica se $3 foi resultado de concatenaçao da variavel
						if($3.tamanho > var.tamanho)
							var.tamanho = $3.tamanho;
					}
				
					// std::cout << "Tipo " << getVarType($0.tipo) << " com i = "<< i<< std::endl;
					// std::cout << "(VAR3) Tipo " << getVarType($3.tipo) << " com i = "<< i<< std::endl;

					addVar2Escopo(pilha, var);
					declaracoes.push_back(var);

					
				}else{
					//se a variavel ja foi declarada
					//cout << " VARIAVEL FOI DECLARADA "<< var.tipo << endl;
					if(var.tipo == getVarType(TK_TIPO_STRING)){
						string willy = getVarName();					
						variavel willy_var = createVar(willy, var.tipo, willy);
						
						//variavel temporaria armazena variavel antiga
						trad = $1.traducao + $3.traducao + "\t"+ willy_var.nome_temp + " = " + varName + ";\n";

						int tam = var.tamanho + $3.tamanho;
						trad += "\t"+varName + " = (char*) malloc(sizeof(char) * "+ to_string(tam) + ");\n";
						//$$.traducao = $1.traducao + $3.traducao + "\tstrcpy(" + varName  + ", " + $3.label +");\n";
						trad +=  "\tstrcpy(" + varName  + ", " + $3.label +");\n";
						trad += "\tfree("+ willy + ");\n";
						
						//cout << " TRAD EM ATRIB " <<trad << endl;
						
						//atualiza o tamanho da variavel existente e salva na pilha
						var.tamanho = tam;
						addVar2Escopo(pilha ,var );
						declaracoes.push_back(willy_var);
					}
				}
				
				// Cast na atribuição com Temp "Store"
				if( (getVarOnStack($1.label).tipo != getVarType($3.tipo) ) ){
					// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
					store = getVarName();
					string linha =  store + " = (" +getVarOnStack($1.label).tipo+") " + $3.label + ";\n";
					string linha2 = "\t"  + varName + " = " + store + ";\n";
					$$.traducao = trad + $1.traducao + $3.traducao + "\t"  + linha + linha2;

					variavel v = createVar(store, getVarOnStack($1.label).tipo,store);

					addVar2Escopo(pilha, v);
					declaracoes.push_back(v);
				}
				// Tipo Inferido ou cast não necessário
				else{
					
					if (getVarType($3.tipo) == "char*"){
						$$.tamanho = $3.tamanho - 2;
						
						if(trad == "")
							$$.traducao = $1.traducao + $3.traducao + "\tstrcpy(" + varName  + ", " + $3.label +");\n";
						else
							$$.traducao = trad;
						
					}
					else
						$$.traducao = trad +  $1.traducao + $3.traducao + "\t" + varName  + " = " + $3.label +";\n";
	
					
				}
				
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
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);

			}
 			| E '+' E
			{
				if ($1.tipo == TK_TIPO_STRING || $3.tipo == TK_TIPO_STRING){
					//cout << "No E+E, concat " << $1.traducao << endl;
				//	cout << $1.tamanho << $3.tamanho << endl;
					$$ = concatString($1, $3);
				}
				else{
					$$ = castArith($1, $3, "+");
				}
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
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
			| TK_NUM
			{
				$$.tipo = TK_TIPO_INT;
				string varName = getVarName();
				$$.traducao = "\t" +varName + " = " + $1.label + ";\n";
				$$.label = varName;
				variavel v = createVar(varName, getVarType($$.tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
			| TK_BOOL
			{
				$$.tipo = TK_TIPO_BOOL;
				string varName = getVarName();
				// puts("Estou aqui");
				$$.traducao = "\t" + varName+ " = " + $1.label + ";\n";
				$$.label = varName;
				variavel v = createVar(varName, getVarType($$.tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
			| TK_CHAR
			{
				// puts("Estou aqui");
				$$.tipo = TK_TIPO_CHAR;
				string varName = getVarName();
				$$.traducao = "\t" + varName + " = " + $1.label + ";\n";
				$$.label = varName;
				variavel v = createVar(varName, getVarType($$.tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
			| TK_STRING
			{
				// puts("ACHEI UMA STRING");
				$$.tipo = TK_TIPO_STRING;
				string varName = getVarName();
				// $$.traducao = "\t" + varName + " = " + $1.label + ";\n";
				$$.traducao = "\tstrcpy(" + varName + "," + $1.label + ");\n";
				$$.label = varName;
				
				variavel v = createVar(varName, getVarType($$.tipo), varName);
				// nao conta o abre e fecha aspas
				v.tamanho = $1.label.size() - 2;
				
				//cout << "Imprimindo Label: " << $1.label <<endl;
				//cout<< " tamanho da string " << v.tamanho << endl;
				
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
			| TK_ID
			{
				variavel v = getVarOnStack($1.label);
				string id = v.nome_temp;

				if (id == ""){
					cout << "Erro de Compilação Variavel '" << $1.label << "' inexistente" <<endl;
					exit(0);
				}
				else{

					$$.traducao = $1.traducao;
					$$.label = id;
					$$.tipo = getTokenType(v.tipo);
					$$.tamanho = v.tamanho;
					
					//cout << " achei uma variavel "<< v.nome_var << " " << v.nome_temp << " " << v.tamanho << endl;
				//	cout << "REGRA TK_ID: " <<$$.label << $$.tipo <<": "+v.tipo << endl;
				}
			}
			|
			
			TK_GLOBAL TK_ID
			{
				variavel v = pilha->escopos[0][$2.label];
				string id = v.nome_temp;

				if (id == ""){
					cout << "Erro de Compilação Variavel '" << $1.label << "' inexistente no escopo global" <<endl;
					exit(0);
				}
				else{

					$$.traducao = $1.traducao;
					$$.label = id;
					$$.tipo = getTokenType(v.tipo);
					$$.tamanho = v.tamanho;
					
					//cout << " achei uma variavel "<< v.nome_var << " " << v.nome_temp << " " << v.tamanho << endl;
				//	cout << "REGRA TK_ID: " <<$$.label << $$.tipo <<": "+v.tipo << endl;
				}
			}
			;

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] ){

	// pushEscopo(pilha, escopoGlobal);

	//criar datamap em arquivo
	yyparse();
	

	return 0;
}

string declararVariaveis(){
	return getDeclaracoes(declaracoes);
}

void yyerror( string MSG ){
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
	if(type == "char*")
		return TK_TIPO_STRING;

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
	if(type == TK_TIPO_STRING)
		return "char*";
	
	return "";	
}

int checkType (int t1, int t3){

	//cout << "Tipo1 " << getVarType(t1) << "Tipo3 " << getVarType(t3) << endl;
	if ( (t1 != TK_TIPO_INT && t1 != TK_TIPO_FLOAT) || (t3 != TK_TIPO_INT && t3 != TK_TIPO_FLOAT) ) {

		if (t1 == TK_TIPO_BOOL && t3 == TK_TIPO_BOOL)
			return TK_TIPO_BOOL;

		else if (t1 == TK_TIPO_CHAR && t3 == TK_TIPO_CHAR)
			return TK_TIPO_CHAR;

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

atributos castFunction(int t1, string t1_label, int t3, string t3_label, int t0, string sinal){
	int teste = checkType(t1, t3);
	string linha = "", linha2 = "";

	string varName = getVarName();
	atributos retorno;

	if (teste == TK_TIPO_FLOAT){

		string store = getVarName();
		retorno.label = store;

		variavel v = createVar(varName, getVarType(teste), varName);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);
		v = createVar(store, getVarType(teste), store);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);

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
		retorno.label = varName;
		linha2 = "\t" + varName +" = "+ t1_label + " " + sinal + " " + t3_label +";\n";
		variavel v = createVar(varName, getVarType(teste), varName);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);
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
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);
		v = createVar(store, getVarType(teste), store);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);

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

		//cout << "TIPOS DE T1 E T3 " << t1 << " " << t3 << endl;
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

void createVarTableLog (VarTable escopo){

	string linhas;
	// for (int i = 0; i < pilha->escopos.size(); i++){
	// 	VarTable varTable = pilha->escopos[i];
	linhas += "Escopo " + to_string(pilha->escopoAtual) + "\n";

	// 	// linhas += "\n";
	for (std::map<string,variavel>::iterator it=escopo.begin(); it!=escopo.end(); ++it){
		variavel var = it->second;
		linhas += var.tipo + "\t" + var.nome_var + "\t" + var.nome_temp + "\t" + to_string(var.tamanho) + "\n";
	}
	linhas += "\n";
	// }

	createLog("varTable", linhas, true);
}

variavel getVarOnStack(string label){

	
	//out <<  " GET TEMP ON TABLE: buscando: " << label<< " ESCOPO ATUAL  " << pilha->escopoAtual << endl;

	for (int i = pilha->escopoAtual; i >= 0 ; i--)
	{	
		VarTable varTable = pilha->escopos[i];
	//	cout<< "buscando no Escopo: " << i <<endl;
		for (std::map<string,variavel>::iterator it=varTable.begin(); it!=varTable.end(); ++it){
			variavel var = it->second;
		//	cout << var.tipo + "\t" + var.nome_var + "\t" + var.nome_temp + "\n" << endl;
		}
	}


	VarTable varTable = pilha->escopos[pilha->escopoAtual];
	if ( varTable.count(label) ){
		//variavel ja foi declarada
	//	cout<< "achei " << label << " no escopo atual" << endl;
		return varTable[label];
	}else{
		int escopo = pilha->escopoAtual-1;
		for(int i = escopo; i > -1; i--){
			VarTable varTable = pilha->escopos[i];
			if ( varTable.count(label) ){
				//variavel ja foi declarada
			//	cout<< "achei " << label << " no escopo " << i << endl;
			//	cout << varTable[label].nome_temp << " " << varTable[label].tipo << endl;
				return varTable[label];
			}
		}
	//	cout << "nao achei " << label << endl;

		return createVar("", "","");
	}


	// cout << "Nein Nein Nein variavel "<< label << endl;
	// exit(0);	

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
		//varTable[varName] = v;
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);
	}
	//Com cast
	else{
		atributos atr = castFunctionArith(s1.tipo, s1.label, s3.tipo, s3.label, ss.tipo, sinal);
		ss.traducao = s1.traducao + s3.traducao + atr.traducao;
		ss.label = atr.label;
	}
	return ss;

}

string getLabel(int token){

	if (token == TK_IF)
		return "fim_if_" + to_string(++curLabel);
		
//	else if (token == TK_ELSE)
	//	return "else";

	else if (token == TK_WHILE)
		return "_loop_" + to_string(++curLabel);
		
}

atributos concatString (atributos a1 ,atributos a2){
	
	string varName = getVarName();
	variavel var = createVar(varName, getVarType(TK_TIPO_STRING), varName);
	
	variavel v1 = getVarOnStack(a1.label);
	variavel v2 = getVarOnStack(a2.label);
	
	var.tamanho = a1.tamanho + a2.tamanho;
	
	//cout << "VarTamanho " << v1.tamanho << " " << v2.tamanho << endl;
	//cout << "dados variaveis encontradas" <<endl;
	//cout << v1.nome_temp << " " << v1.nome_var << endl;
	//cout << v2.nome_temp << " " << v2.nome_var << endl;
	
	declaracoes.push_back(var);
	
	string linha = "\tstrcat("+ varName +", " + a1.label+");\n";
	string linha2 = "\tstrcat("+ varName +", " + a2.label+");\n";
	
	//String concatenada ta no VarName
	atributos atr;
	
	atr.label = varName;
	atr.traducao = linha + linha2;
	atr.tipo = TK_TIPO_STRING;
	atr.tamanho = var.tamanho;
	
	
	//cout << " CONCAT STRING" << endl;
	//cout << a1.label << " " << a1.traducao << a1.tipo << endl;
//	cout << a2.label << " " <<  a2.traducao << a2.tipo << endl;
	
	return atr;
	
}

int getNumber(string str){
	int result = 0;
	
	for (int i = 0; i < str.length(); ++i)	{
		if(str.at(i) >= '0' &&  str.at(i) <= '9'){
			result *= 10;
			result += str.at(i) - '0'; 
		}
	}
	return result;
}

