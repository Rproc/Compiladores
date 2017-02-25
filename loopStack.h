#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct Loop {
    string beginLabel;
    string endLabel;
    string continueLabel;
}Loop;

typedef struct {
    vector<Loop> loops;
} LoopStack;

void pushLoop(Loop loop, LoopStack* stack){
   stack->loops.push_back(loop); 
}

Loop popLoop(LoopStack* stack){
    Loop loop = stack->loops.back();
    
    stack->loops.pop_back();
    
    return loop;
}

Loop getLoop (LoopStack* stack){
    
    Loop loop = stack->loops.back();
    
    return loop;
}

LoopStack* createLoopStack(){
    return (LoopStack*) malloc(sizeof(LoopStack));
}

/*
int main(){
    
    LoopStack* pilha = createLoopStack();
    
    Loop loop1;
    loop1.beginLabel = "inicio_while_1";
    loop1.endLabel = "fim_while_1";
    
    Loop loop2;
    loop2.beginLabel = "inicio_while_2";
    loop2.endLabel = "fim_while_2";
    
    Loop loop3;
    loop3.beginLabel = "inicio_while_3";
    loop3.endLabel = "fim_while_3";
    
    
    pushLoop(loop1, pilha);
    pushLoop(loop2, pilha);
    pushLoop(loop3, pilha);
    
    
    for (int i = 0; i < pilha->loops.size(); i++) {

        cout << pilha->loops[i].beginLabel << " " << pilha->loops[i].endLabel << endl; 
    }
    
    
    cout << endl << endl;
    Loop loop = popLoop(pilha);
    
   // vector<Loop> loops = pilha->loops;
    for (int i = 0; i < pilha->loops.size(); i++) {
        
        cout << pilha->loops[i].beginLabel << " " << pilha->loops[i].endLabel << endl; 
    }
    
    return 0;
}*/