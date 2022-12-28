#ifndef TRADUTOR_H_INCLUDED
#define TRADUTOR_H_INCLUDED

#include <bits/stdc++.h>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <cctype>
#include <string>


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

vector<string> diretivas = {"CONST", "EQU", "IF", "SPACE", "SECTION"};

// Separa os tokens em linhas, assim saberemos exatamente qual linha de erro irá acontecer e qual
vector<vector<string>> token_parser(string arquivo){
    ifstream file(arquivo);
    string str;
    vector<vector<string>> programa;
    vector<string> linha;
    string hex_prefix = "0X"; // em maisculo por causa da tranformação em maisculo abaixo

    while (getline(file, str)) {
        transform(str.begin(), str.end(), str.begin(), ::toupper); // tranforma em maiusculo
        istringstream iss(str.substr(0, str.find(';'))); // remove comentarios. Possivel erro: é possivel que haja espaço a mais no final da linha
        string token;

        if (str.length() != 0){ // Ignora linhas vazias

            while (getline(iss, token, ' ')){
                token = token.c_str();

//                if (token[0] == ';'){ // Remove comentario, mas apenas se tiver espaço antes
//                    break;
//                }
                if (token.find_first_not_of(' ') != string::npos){ // remove espaços desnecessarios

                    if (token.find(hex_prefix, 0) == 0){
                        token = token.substr(hex_prefix.length());
                        token = to_string(stoul(token, nullptr, 16));
                    }

                    linha.push_back(token);
                }
            }

            programa.push_back(linha);
            linha.clear();
        }
    }
    return programa;

}

vector<string> sepOps(string ops) {
    string tmp;
    stringstream ss(ops);
    vector<string> words;

    while(getline(ss, tmp, ',')) {
        words.push_back(tmp);
    }

    return words;
}


bool isLabel(string token) {
    if (token[token.length()-1] == ':') {
        return true;
    }
    return false;
}

string getLabel(string token) {
    return token.substr(0, token.size()-1);
}

bool inTS(string token, map <string,int> ts) {
    if (ts.find(token) == ts.end()) {
        return false;
    }
    return true;
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

bool isSymbol(string &token) {
    string::iterator it;

    for (it = token.begin(); it != token.end(); it++){
        if (isdigit(*it) == 0) {
            return true;
        }
    }
    return false;
}

map <string,int> primeiraPassagem(vector<vector<string>> &programa){
    int contador_posicao = 0;
    int contador_linha = 1;
    map <string,int> ts;
    string label;
    string op;
    string opn;

    for (int i=0; i < programa.size(); i++, contador_linha++){
        if (isLabel(programa[i][0])) {
            label = getLabel(programa[i][0]);
            op = programa[i][1];

            if (inTS(label, ts)) {
                throw invalid_argument("Label already defined");
            } else {
                ts.insert(pair<string, int>(label, contador_posicao));
            }
        } else {
            op = programa[i][0];
        }

        if (opcodes.count(op)) {
            if (op == "COPY") {
                contador_posicao += 3;
            } else if (op == "STOP") {
                contador_posicao += 1;
            } else {
                contador_posicao += 2;
            }
        } else if (count(diretivas.begin(), diretivas.end(), op)) {
            if (op == "CONST") {
                contador_posicao += 1;
            } else if (op == "SPACE") {
                if (programa[i].size() > 2) {
                    contador_posicao += stoi(programa[i][2]);
                } else {
                    contador_posicao += 1;
                }
            }
        } else {
            throw invalid_argument("Unknown operation");
        }
    }

    return ts;
}

int getValue (string str, map <string,int> mp) {
    return mp.find(str)->second;
}

string getValueEQUS (string str, map <string,string> mp) {
    return mp.find(str)->second;
}

void segundaPassagem(vector<vector<string>> &programa, map <string,int> ts) {
    int contador_posicao = 0;
    int contador_linha = 1;
    string label;
    string op;
    string ops_i;
    vector<string> ops;
    string objeto = "";
    string objeto_temp;

    for (int i=0; i < programa.size(); i++, contador_linha++){
        if (isLabel(programa[i][0])) {
            label = getLabel(programa[i][0]);
            op = programa[i][1];

            if (programa[i].size() > 2) {
                ops_i = programa[i][2];
            } else {
                ops_i = "";
            }
        } else {
            op = programa[i][0];

            if (programa[i].size() > 1) {
                ops_i = programa[i][1];
            } else {
                ops_i = "";
            }
        }

        if (op != "SECTION") {
            ops = sepOps(ops_i);

            for (int p=0; p < ops.size(); p++) {
                if (isSymbol(ops[p])) {
                    if (inTS(ops[p], ts) == 0) {
                        throw invalid_argument("Unknown symbol");
                    }
                }
            }

        if (opcodes.count(op)) {
            if ((op == "COPY") && (ops.size() != 2)) {
                throw invalid_argument("Invalid operand");
            }

            if ((op == "STOP") && (ops.size() != 0)) {
                throw invalid_argument("Invalid operand");
            }

            if ((op != "COPY") && (op != "STOP") && (ops.size()) != 1) {
                throw invalid_argument("Invalid operand");
            } else {
                contador_posicao += 1 + ops.size();
            }

            objeto = to_string(getValue(op, opcodes));

            for (int o=0; o < ops.size(); o++) {
                objeto_temp = to_string(getValue(ops[o], ts));
                objeto += " " + objeto_temp;
            }

            cout << objeto;
            cout << "\n";

        } else if (count(diretivas.begin(), diretivas.end(), op)) {
            if (op == "CONST") {
                objeto = ops[0];

                contador_posicao += 1;
            }
            if (op == "SPACE") {
                if (ops.size() == 1) {
                    objeto = "";
                    for (int j=0; j < atoi(ops[0].c_str()); j++) {
                        objeto += "XX ";
                    }
                    contador_posicao += atoi(ops[0].c_str());
                } else {
                    objeto = "XX"; // LEMBRAR QUE NÃO SE DEVE SERR COLOCADO XX MAS 0 QUANDO FOR SPACE
                    contador_posicao += 1;
                }
            }
                                        cout << objeto;
            cout << "\n";
        } else {
            throw invalid_argument("Unknown operation");
        }

        }
        ops.clear();
    }

}

string getLine(vector<string> strs) {
    string result;
    ostringstream imploded;
    copy(strs.begin(), strs.end(),
               ostream_iterator<string>(imploded, " "));
    result = imploded.str();
    result.pop_back();
    return result;
}

void preProcessamento (vector<vector<string>> &programa) {
    int section_text = 0;
    vector<int> remove_index;
    map <string,int> equs;
    int value;
    string label;

    if (getLine(programa[0]) == "SECTION TEXT") {
        return;
    }

    for (int i=0; i < programa.size(); i++){
        if (getLine(programa[i]) == "SECTION TEXT") {
            section_text = 1;
            continue;
        }

        if (section_text) {
            // Tá dentro de texto, pode checar IF
            if (programa[i][0] == "IF") {
                if (inTS(programa[i][1], equs)) {
                    value = getValue(programa[i][1], equs);
                    remove_index.push_back(i);
                    if (value == 0) {
                        remove_index.push_back(i+1);
                    }
                } else {
                    cout << "Erro: operando não é EQU";
                }
            } else {
                if (programa[i].size() > 1) {
                    if ((programa[i][1] == "SPACE") || (programa[i][1] == "CONST")) {
                        if (programa[i].size() > 2) {
                            if (inTS(programa[i][2], equs)) {
                                value = getValue(programa[i][2], equs);
                                programa[i][2] = to_string(value);
                            }
                        }
                    }
                }
            }
        } else {
            // Tá fora de texto, precisa checar EQU
            if (programa[i][1] == "EQU") {
                if (isLabel(programa[i][0])) {
                    label = getLabel(programa[i][0]);
                    value = atoi(programa[i][2].c_str());
                    equs.insert(pair<string, int>(label, value));
                    remove_index.push_back(i);
                } else {
                    cout << "Erro: Falta rótulo em EQU";
                }
            } else {
                cout << programa[i][1];
                cout << "Erro: operação feita antes da seção de texto\n";
            }
        }
    }

    sort(remove_index.begin(), remove_index.end(), greater<int>());

    for (int i=0; i < remove_index.size(); i++) {
        programa.erase(programa.begin() + remove_index[i]);
    }

}

bool ehArg(string value, map<string,string> inds) {
    if (inds.find(value) == inds.end()) {
      return false;
    }
    return true;
}

string joinOps(vector<string> strs) {
    string result;
    ostringstream imploded;
    copy(strs.begin(), strs.end(),
               ostream_iterator<string>(imploded, ","));
    result = imploded.str();
    result.pop_back();

    return result;
}

bool inMACROS(string token, map <string,vector<vector<string>>> macros) {
    if (macros.find(token) == macros.end()) {
        return false;
    }
    return true;
}

int get_value(string token) {
    token.erase(0,1);
    return atoi(token.c_str());
}

void processamentoMacro(vector<vector<string>> &programa) {
    map <string,vector<vector<string>>> macros;
    map <string,string> macro_args;
    vector<string> macro_line;
    vector<string> args;
    bool inside_macro = false;
    string macro_atual;
    string str_args;
    vector<string> args_repl;
    vector<string> repl_line;
    vector<int> repl_macros;
    vector<pair <int,int>> end_macros;
    pair <int,int> end_macro;
    int end_correcao = 0;

    for (int i=0; i < programa.size(); i++){
        if (inside_macro) {
            // Dentro de macro
            if (programa[i][0] == "ENDMACRO") {
                inside_macro = false;
                macro_args.clear();
                end_macro.second = i;
                end_macros.push_back(end_macro);
            } else {
                for (int j=0; j < programa[i].size(); j++) {
                    if (j == 1) {
                        // Quando há argumentos, é necessário substituir pelo index #i
                        args = sepOps(programa[i][1]);

                        for (int a=0; a < args.size(); a++) {
                            if (ehArg(args[a], macro_args)) {
                                args[a] = macro_args[args[a]];
                            }
                        }

                        str_args = joinOps(args);
                        macro_line.push_back(str_args);
                    } else {
                        // Se não é argumento, não muda
                        macro_line.push_back(programa[i][j]);
                    }
                }
                macros[macro_atual].push_back(macro_line);
                macro_line.clear();
            }
        } else {
            if (programa[i].size() > 1) {
                // Início de macro
                if (programa[i][1] == "MACRO") {
                    inside_macro = true;
                    end_macro.first = i;
                    macro_atual = getLabel(programa[i][0]);
                    macros.insert(pair<string,vector<vector<string>>>(macro_atual, vector<vector<string>>()));

                    if (programa[i].size() == 3) {
                        args = sepOps(programa[i][2]);
                        for (int a=0; a < args.size(); a++) {
                            macro_args.insert(pair<string,string>(args[a], "#" + to_string(a)));
                        }
                    }

                    continue;
                }
            }

            // Não faz parte de definição de macro
            if (inMACROS(programa[i][0], macros)) {
                repl_macros.push_back(i);

                if (programa[i].size() == 2) {
                    // Pegar argumentos passados pelo usuário
                    args_repl = sepOps(programa[i][1]);
                }

                for (int m=0; m < macros[programa[i][0]].size(); m++) {
                    for (int n=0; n < macros[programa[i][0]][m].size(); n++) {
                        if (n == 1) {
                            // Se há argumentos na linha da MACRO, é preciso substituir pelos argumentos passados
                            args = sepOps(macros[programa[i][0]][m][n]);

                            for (int b=0; b < args.size(); b++) {
                                if (args[b][0] == '#') {
                                    args[b] = args_repl[get_value(args[b])];
                                }
                            }

                            str_args = joinOps(args);
                            repl_line.push_back(str_args);
                        } else {
                            repl_line.push_back(macros[programa[i][0]][m][n]);
                        }
                    }

                    programa.insert(programa.begin() + (i + m + 1), repl_line);
                    repl_line.clear();
                }
            }
        }
    }

    // Remover as linhas onde houve chamado a MACRO
    sort(repl_macros.begin(), repl_macros.end(), greater<int>());
    for (int i=0; i < repl_macros.size(); i++) {
        programa.erase(programa.begin() + repl_macros[i]);
    }

    // Remover as declarações das MACROS
    // Fator de correção necessário porque começa removendo as linhas da primeira macro, afetando o endereço das próximas
    for (int i=0; i < end_macros.size(); i++) {
        end_macros[i].first -= end_correcao;
        end_macros[i].second -= end_correcao;

        for (int c=end_macros[i].second; c >= end_macros[i].first; c--) {
            programa.erase(programa.begin() + c);
        }

        end_correcao += 1 + end_macros[i].second - end_macros[i].first;

    }
}

// DEIXAR O TOKENIZADOR DE FORMA A SEPARAR MELHOR

#endif // TRADUTOR_H_INCLUDED
