#include <bits/stdc++.h>
#include "Structs.h"

vector<Palabra> dividir_todo(vector<Palabra> v, vector<char> caracteres) {
    vector<Palabra> partes = v;

    for(char c : caracteres) {
        vector<Palabra> aux;

        // Para cada elemento del vector, separar por el caracter
        for(int i=0; i<partes.size(); i++) {

            vector<Palabra> car = dividir_cada_caracter(partes[i], c);
            for(int j=0; j<car.size(); j++) {
                aux.push_back(car[j]);
            }
        }

        // Partes ahora tendrá todas las partes separadas por el caracter
        partes.clear();
        for(int i=0; i<aux.size(); i++) {
            partes.push_back(aux[i]);
        }
    }

    return partes;
}

vector<Palabra> dividir_cada_caracter(Palabra palabra, char delimitador) {
    vector<Palabra> partes;
    string s;

    for (char c: palabra.palabra) {
        if (c == delimitador) {
            // Si la cadena auxiliar no está vacía, crear la palabra y añadir al vector
            if (!s.empty()) {
                Palabra p = {s, palabra.linea};
                partes.push_back(p);
                s.clear();
            }
            // Añadir el caracter como palabra
            Palabra p = {string(1, delimitador), palabra.linea};
            partes.push_back(p);
        } else
            s += c;
    }
    
    // Si la cadena auxiliar no está vacía, crear la palabra y añadir al vector
    if (!s.empty()) {
        Palabra p = {s, palabra.linea};
        partes.push_back(p);
    }

    return partes;
}

string getTipoToken(TipoToken tt) {
    switch (tt)
    {
    case OPERADOR:
        return "OPERADOR";
        break;

    case COMPARADOR:
        return "COMPARADOR";
        break;

    case ASIGNADOR:
        return "ASIGNADOR";
        break;

    case PUNTO:
        return "PUNTO";
        break;
    
    case IDENTIFICADOR:
        return "IDENTIFICADOR";
        break;

    case NUMERO:
        return "NUMERO";
        break;

    case STRING:
        return "STRING";
        break;

    case PALABRA_RESERVADA:
        return "PALABRA_RESERVADA";
        break;
    
    case LLAVE_IZQ:
        return "LLAVE_IZQ";
        break;

    case LLAVE_DER:
        return "LLAVE_DER";
        break;

    case CORCH_IZQ:
        return "CORCH_IZQ";
        break;

    case CORCH_DER:
        return "CORCH_DER";
        break;

    case PAREN_IZQ:
        return "PAREN_IZQ";
        break;

    case PAREN_DER:
        return "PAREN_DER";
        break;

    case COMA:
        return "COMA";
        break;

    case PUNTO_COMA:
        return "PUNTO_COMA";
        break;

    case INVALIDO:
        return "INVALIDO";
        break;

    default:
        return "";
        break;
    }
}

void imprimir_vector(vector<Token> v) {
    for (Token t : v) {
        cout << t.toString() << '\n';
    }
}

void imprimir_vector(vector<string> v) {
    for (const string& s : v) {
        cout << s << '\n';
    }
}

void imprimir_vector(vector<Palabra> v) {
    for (Palabra p : v) {
        cout << p.linea << ' ' << p.palabra << '\n';
    }
}