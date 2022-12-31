#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>

#include "tradutor.h"
#include "tokenizador.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[]){
    std::string op = argv[1];
    std::string arquivo = argv[2];
    std::string file_name = arquivo.substr(0, arquivo.find('.'));
    std::string extension;
    string objeto;

    vector<vector<string>> programa = tokenParser(arquivo);

    if(op == "-p"){ // .PRE
        preprocess(programa);
        createFile(programa, file_name, ".PRE");
        return 0;
    }

    if(op == "-m"){ // .MCR
        preprocess(programa);
        processMACRO(programa);
        createFile(programa, file_name, ".MCR");
        return 0;
    }

    if(op == "-o"){ // .OBJ
        preprocess(programa);
        processMACRO(programa);
        map <string,int> ts = passOne(programa);
        objeto = passTwo(programa, ts);

        createFileObj(objeto, file_name, ".OBJ");
        return 0;
    }
}

