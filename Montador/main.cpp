#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

#include "tradutor.h"
using namespace std;

int main(){
    //cout << "dsadasdas";
    vector<vector<string>> programa = token_parser("bin.asm");
    for ( int i =0 ; i < programa.size();i++){
        for ( int j =0 ; j < programa[i].size();j++){
        cout << programa[i][j];
        cout << "\n";
        }
    }


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
