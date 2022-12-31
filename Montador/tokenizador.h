#ifndef TOKENIZADOR_H_INCLUDED
#define TOKENIZADOR_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "tradutor.h"

bool labelSozinha(vector<string> linha){
    if ((linha.size() == 1) && (isLabel(linha[0]))){
        return true;
    } else{
        return false;
    }
}
// tratamento de X+3
vector<string> trataPlus(string tokenPlus){
    vector<string> vec;
    istringstream iss(tokenPlus);
    string s;
    while (getline(iss, s, '+')) {
        vec.push_back(s);
    }
    //cout << vec[0] << endl;
    //cout << vec[1] << endl;
    return vec;
}

// Separa os tokens em linhas, assim saberemos exatamente qual linha de erro irá acontecer e qual
vector<vector<string>> token_parser(string arquivo){
    ifstream file(arquivo);
    string str;
    string labelLinha;
    bool flag = false;
    vector<vector<string>> programa;
    vector<string> linha;
    vector<string> vec; // para X+3
    string hex_prefix = "0X"; // em maisculo por causa da tranformação em maisculo abaixo

    while (getline(file, str)) {
        transform(str.begin(), str.end(), str.begin(), ::toupper); // tranforma em maiusculo
        istringstream iss(str.substr(0, str.find(';'))); // remove comentarios. Possivel erro: é possivel que haja espaço a mais no final da linha
        string token;

        if (str.length() != 0){ // Ignora linhas vazias

            while (getline(iss, token, ' ')){
                token = token.c_str();

                if (token.find_first_not_of(' ') != string::npos){ // remove espaços desnecessarios

                    if (token.find(hex_prefix, 0) == 0){
                        token = token.substr(hex_prefix.length());
                        token = to_string(stoul(token, nullptr, 16));
                    }
                    if (flag){
                        flag = false;
                        linha.push_back(labelLinha);
                    }

                    if (token.find('+') != std::string::npos){
                        vec = trataPlus(token);
                        linha.push_back(vec[0]);
                        linha.push_back("+");
                        linha.push_back(vec[1]);
                    }else{
                        linha.push_back(token);
                    }

                }
            }
            if (labelSozinha(linha)){
                flag = true;
                labelLinha = linha[0];
                linha.clear();
                //continue;
            }
            if (linha.size() != 0 && !flag){ // Como eliminamos na linha 18, precisamos checar se a linha nao é vazia
                programa.push_back(linha);
                linha.clear();
            }

        }
    }
    return programa;

}

void printar_programa(vector<vector<string>> programa) {
   for (int i=0; i < programa.size(); i++){
        for (int j=0; j < programa[i].size(); j++) {
            cout << programa[i][j];
            cout << " ";
        }
        cout << "\n";
    }
}

// criar os aqruivos .PRE .MCR
void create_file(vector<vector<string>> programa,  std::string file_name, std::string extension){

    std::ofstream outfile (file_name + extension); // criar arquivo vazio

    for (int i=0; i < programa.size(); i++){
        for (int j=0; j < programa[i].size(); j++) {
            outfile << programa[i][j];
            outfile << " ";
        }
        outfile << "\n";
    }

    outfile.close(); // por algum motivo meu PC explode se nao colocar isso aqui.
}

void create_file_obj(string objeto, std::string file_name, std::string extension){

    std::ofstream outfile (file_name + extension); // criar arquivo vazio
    outfile << objeto;
    outfile.close(); // por algum motivo meu PC explode se nao colocar isso aqui.
}
#endif // TOKENIZADOR_H_INCLUDED

















