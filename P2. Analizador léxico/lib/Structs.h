#ifndef __Token
#define __Token

#include <bits/stdc++.h>

using namespace std;

void imprimir_vector(vector<string> v);

enum TipoToken {
    OPERADOR,
    IDENTIFICADOR,
    NUMERO,
    STRING,
    PALABRA_RESERVADA,
    LLAVE_IZQ,
    LLAVE_DER,
    CORCH_IZQ,
    CORCH_DER,
    PAREN_IZQ,
    PAREN_DER,
    COMA,
    PUNTO,
    PUNTO_COMA,
    COMPARADOR,
    ASIGNADOR,
    INVALIDO
};

string getTipoToken(TipoToken tt);

typedef struct Token {
    TipoToken tipo;
    string lexema;
    int linea;

    std::string toString() {
        if(tipo == INVALIDO)
            return "< \033[91m" + getTipoToken(tipo) + "\033[0m, " + lexema + " >";
        else if(tipo == PALABRA_RESERVADA)
            return "< \033[94m" + getTipoToken(tipo) + "\033[0m, " + lexema + " >";
        else if(tipo == LLAVE_IZQ || tipo == LLAVE_DER || tipo == CORCH_IZQ || tipo == CORCH_DER || tipo == PAREN_IZQ || tipo == PAREN_DER)
            return "< \033[96m" + getTipoToken(tipo) + "\033[0m, " + lexema + " >";
        else if(tipo == STRING)
            return "< \033[92m" + getTipoToken(tipo) + "\033[0m, " + lexema + " >";
        else
            return "< \033[93m" + getTipoToken(tipo) + "\033[0m, " + lexema + " >";
        //+ std::to_string(finalGrade);
    }
} Token;

void imprimir_vector(vector<Token> v);

typedef struct Palabra {
    string palabra;
    int linea;
} Palabra;

vector<Palabra> dividir_todo(vector<Palabra> v, vector<char> caracteres);
vector<Palabra> dividir_cada_caracter(Palabra palabra, char delimitador);
void imprimir_vector(vector<Palabra> v);

#endif