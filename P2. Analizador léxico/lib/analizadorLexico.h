#include <bits/stdc++.h>
#include "Structs.h"

using namespace std;

vector<Token> analizadorLexico(vector<Palabra> palabras);
vector<Token> Automata(Palabra p);

enum class Estado {
    INICIO,
    ID,

    MAS,
    MENOS,
    CERO,
    _HEX_X,
    HEXADECIMAL,
    OCTAL,
    ENTERO,
    _PUN_DEC,
    REAL_SIN_EXPONENTE,
    _EXP,
    _EXP_SIG,
    REAL_CON_EXPONENTE,

    IGUAL,
    MENOR,
    MAYOR,
    
    DIVISION,
    COMENTARIO_MULTILINEA,
    COMENTARIO_MULTILINEA_2,
    
    CADENA,

    ERROR,
    ERROR_NUM
};