#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

#include "tradutor.h"
using namespace std;

int main(){
    //cout << "dsadasdas";
    vector<vector<string>> programa = token_parser("bin_equ.asm");
    preProcessamento(programa);
    printar_programa(programa);
    cout << "\n\n";
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
