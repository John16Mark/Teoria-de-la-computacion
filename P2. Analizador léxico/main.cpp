#include <bits/stdc++.h>
#include "lib/analizadorLexico.h"
#include "lib/Structs.h"

using namespace std;

set<int> lineas_error;

int main(int argc, char* argv[]) {

    vector<char> caracteres_para_separar = {'[', ']', '{', '}', '(', ')', ','};

    if(argc != 2) {
        cout << "\033[91mIntroduzca la ruta del archivo .java como argumento.\n\033[0m";
        return 0;
    }

    ifstream archivo(argv[1]);
    string linea;
    int contador_linea = 0;
    vector<Palabra> palabras;
    
    while (getline(archivo, linea)) {
        contador_linea++;
        istringstream iss(linea);
        string p;

        while (iss >> p) {
            Palabra palabra = {p, contador_linea};
            palabras.push_back(palabra);
        }
    }

    vector<Token> tokens;
    tokens = analizadorLexico(palabras);

    imprimir_vector(tokens);

    for(Token t : tokens) {
        if(t.tipo == TipoToken::INVALIDO && lineas_error.find(t.linea) == lineas_error.end()) {
            lineas_error.insert(t.linea);
        }
    }

    cout << endl;
    for(int i : lineas_error) {
        cout << "\033[31m\tError en l"<< (char) 161 << "nea " << i << "\033[0m" <<endl;
    }

    return 0;
}

