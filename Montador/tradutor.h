#ifndef TRADUTOR_H_INCLUDED
#define TRADUTOR_H_INCLUDED

#include <bits/stdc++.h>
#include <fstream>
#include <regex>

using namespace std;

map <string,int> opcodes = {
{"ADD", 1},
{"SUB", 2},
{"MULT", 3},
{"DIV", 4},
{"JMP", 5},
{"JMPN", 6},
{"JMPP", 7},
{"JMPZ", 8},
{"COPY", 9},
{"LOAD", 10},
{"STORE", 11},
{"INPUT", 12},
{"OUTPUT", 13},
{"STOP", 14}};

vector<string> diretivas = {"BEGIN", "CONST", "END", "EQU", "EXTERN", "IF", "PUBLIC", "SPACE", "SECTION"};

// FAREMOS TRATAMENTO DO PROGRAMA LINHA A LINHA, COM IINSTRUÇÃO EM UM LUGAR
// ASSIM SERA CADA TOKEN POR LINHA
// EXEMPLO
/*
MUL N
STORE N
ENDMACRO
INPUT N
LOAD N
*/

/*
MUL
N
STORE
N
ENDMACRO
INPUT
N
LOAD
N
*/

// Separa os tokens em linhas, assim saberemos exatamente qual linha de erro irá acontecer e qual
vector<vector<string>> token_parser(string arquivo){
    ifstream file(arquivo);
    string str;
    vector<vector<string>> programa;
    vector<string> linha;
    while (getline(file, str)) {
        istringstream iss(str);
        string token;
        while (getline(iss, token, ' ')){
            token = token.c_str();
            linha.push_back(token);
        }
        programa.push_back(linha);
        linha.clear();
    }
    return programa;
}

#endif // TRADUTOR_H_INCLUDED
