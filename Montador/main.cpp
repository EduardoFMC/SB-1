#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

#include "tradutor.h"
#include "tokenizador.h"

using namespace std;

int main(){
    // TESTE com macro
//    vector<vector<string>> programa = token_parser("fatoriamacro_testes.asm");
//
//    //printar_programa(programa);
//    //printf("\n\n\n");
//    //preProcessamento(programa); // 1 Parte. Lida apenas com EQU e IF
//    processamentoMacro(programa);
//
//    printar_programa(programa);
//
//    //cout << "\n\n";
//    //map <string,int> ts = primeiraPassagem(programa);
//
//    //segundaPassagem(programa, ts);

    // TESTE sem macro
    vector<vector<string>> programa = token_parser("bin_equ_teste.asm");

    printar_programa(programa);
    printf("\n\n\n");
    preProcessamento(programa); // 1 Parte. Lida apenas com EQU e IF
    printar_programa(programa);
    printf("\n\n\n");
    map <string,int> ts = primeiraPassagem(programa);
    segundaPassagem(programa, ts);


}

//int main(int argc, char *argv[]){
//    string operacao = argv[1];
//    string entrada = argv[2];
//    string saida = argv[3];
//
//
//    if (operacao == "-p"){
//        printf("-");
//        //preProcessamento(entrada, saida);
//    } else if (operacao == "-m"){
//        printf("-");
//        //processaMacro(entrada, saida);
//    } else{
//        printf("-");
//
//        //processaObjeto(entrada, saida);
//    }
//
//    return 0;
//}
