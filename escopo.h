#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct variavel
{
	string tipo;
	string nome_var;
	string nome_temp;
    int tamanho;

} variavel;

typedef map <string, variavel> VarTable;

// pilha de mapas de variaveis para cada escopo
typedef struct map_stack {
	vector< VarTable > escopos;
  	int escopoAtual;
} map_stack;

//adiciona um mapa de variaveis na pilha (usado sempre q um novo escopo é criado)
void pushEscopo(map_stack *pilha, VarTable mapaEscopo){
	// cout << "entrei na push" << endl;
  	pilha->escopoAtual += 1;
  	pilha->escopos.push_back(mapaEscopo);
}

//remove o escopo mais acima da pilha e o retorna
VarTable pop(map_stack* pilha){

    if(pilha->escopos.empty()){
        cout << "POP_FUNCTION: Não há escopos a serem removidos" << endl;
        exit(0); 
    }

  	VarTable escopo = pilha->escopos.back();

    pilha->escopos.pop_back();
    pilha->escopoAtual -= 1;

    return escopo;

}

map_stack* createMapStack(){

    map_stack *pilha = (map_stack*) malloc(sizeof(map_stack));
    
    VarTable escopinho;
    pushEscopo(pilha, escopinho);
    
	pilha->escopoAtual = 0;
    return pilha;
}

variavel createVar(string nome_var, string tipo, string nome_temp){

	variavel var;
	var.tipo = tipo;
	var.nome_var = nome_var;
	var.nome_temp = nome_temp;

	return var;
}



void addVar2Escopo (map_stack* pilha, variavel v){

	pilha->escopos[pilha->escopoAtual][v.nome_var] = v;

}


void addVar2Global (map_stack* pilha, variavel v){

	pilha->escopos[0][v.nome_var] = v;

}


typedef std::vector<variavel> Declaracoes;



string getDeclaracoes(Declaracoes declaracoes){
    string linhas = "";
    for (int i = 0; i < declaracoes.size(); ++i)
    {
        variavel v =  declaracoes[i];
        if(v.tipo != "char*"){
            linhas +=  v.tipo + " " + v.nome_temp + ";\n";   
        }
        else{
            //linhas +=  "char " + v.nome_temp + "[500];\n";
            linhas += "char* " +  v.nome_temp + " = (char*) malloc(sizeof(char) * " + to_string(v.tamanho )+ " );\n";
        }
            
    }

    return linhas;
}

/*

int main(void){
  	map_stack *pilha = createMapStack(); //Struct

 
    VarTable mapa2;
    variavel v2 = createVar("b","int","temp2");

    pushEscopo(pilha, mapa2);
    
    VarTable mapa3;
    variavel v3 = createVar("nao_global","int","temp3");

    pushEscopo(pilha, mapa3);

    addVar2Global(pilha,v2);
    
    std::cout << pilha->escopos[0]["g"].nome_var << endl;
    
 //  	for(int i = 0; i < pilha->escopos.size(); i++){
    //   	string linhas;
    //   	VarTable varTable = pilha->escopos[i];
	// 	for (std::map<string,variavel>::iterator it=varTable.begin(); it!=varTable.end(); ++it){
    //       variavel var = it->second;
    //       linhas += var.tipo + "\t" + var.nome_var + "\t" + var.nome_temp + "\n";
    //
    //   	}
    //   	cout<<linhas<<endl;
    // }



}
*/