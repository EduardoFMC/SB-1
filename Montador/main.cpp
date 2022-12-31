#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>

#include "tradutor.h"
#include "tokenizador.h"

using namespace std;
// g++ -std=c++17 -o montador main.cpp
// ./montador -p bin_equ_teste.asm
int main(int argc, char *argv[]){
    std::string op = argv[1];
    std::string arquivo = argv[2];
    std::string file_name = arquivo.substr(0, arquivo.find('.')); // remove extensao
    std::string extension;
    string objeto;

    vector<vector<string>> programa = token_parser(arquivo);

    if(op == "-p"){ // .PRE
        preProcessamento(programa);
        create_file(programa, file_name, ".PRE");
        return 0;
    }

    if(op == "-m"){ // .MCR
        preProcessamento(programa);
        processamentoMacro(programa);
        create_file(programa, file_name, ".MCR");
        return 0;
    }

    if(op == "-o"){ // .OBJ
        preProcessamento(programa);
        processamentoMacro(programa);
        map <string,int> ts = primeiraPassagem(programa);
        objeto = segundaPassagem(programa, ts);

        create_file_obj(objeto, file_name, ".OBJ");
        return 0;
    }


//    printar_programa(programa);
//    cout << "\n\n";
//    preProcessamento(programa);
//    processamentoMacro(programa);
//    printar_programa(programa);
//    cout << "\n\n";
//    map <string,int> ts = primeiraPassagem(programa);
//    segundaPassagem(programa, ts);
}

