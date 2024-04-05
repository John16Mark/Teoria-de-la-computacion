#include <bits/stdc++.h>
#include "analizadorLexico.h"
#include "Structs.h"

using namespace std;

bool comentarioMulti = false;
bool comentarioMono = false;
bool cadena = false;
int linea_comentada = 0;
bool esCadena = false;

string lexema = "";

set<string> palabras_reservadas = {
	"public",
	"private",
	"class",
	"package",
	"protected",
	"static",
	"void",
	"main",
	"double",
	"float",
	"int",
	"short",
	"String",
	"for",
	"while",
	"out",
	"println",
	"print"};

vector<Token> analizadorLexico(vector<Palabra> palabras) {
    vector<Token> tokens;
	for (Palabra p : palabras) {
		vector<Token> aux = Automata(p);
		for(Token t : aux) {
			tokens.push_back(t);
		}
	}
    return tokens;
}

vector<Token> Automata(Palabra p) {
	vector<Token> ts;
	Estado estado;
	if (comentarioMulti) {
		estado = Estado::COMENTARIO_MULTILINEA;
	} else if (cadena) {
		estado = Estado::CADENA;
	} else
    	estado = Estado::INICIO;

	for(int i=0; i<p.palabra.length(); i++) {
		char c = p.palabra[i];
		switch (estado)
		{
		case Estado::INICIO:
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
				estado = Estado::ID;
				lexema += c;
			} else if (c == '0') {
				estado = Estado::CERO;
				lexema += c;
			} else if (c >= '1' && c <= '9') {
				estado = Estado::ENTERO;
				lexema += c;
			} else if (c == '+') {
				estado = Estado::MAS;
				lexema += c;
			} else if (c == '-') {
				estado = Estado::MENOS;
				lexema += c;
			} else if (c == '=') {
				estado = Estado::IGUAL;
				lexema += c;
			} else if (c == '%') {
				estado = Estado::INICIO;
				lexema += c;
				Token t = {TipoToken::OPERADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == '*') {
				estado = Estado::INICIO;
				lexema += c;
				Token t = {TipoToken::OPERADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == '/') {
				estado = Estado::DIVISION;
				lexema += c;
			} else if (c == '>') {
				estado = Estado::MAYOR;
				lexema += c;
			} else if (c == '<') {
				estado = Estado::MENOR;
				lexema += c;
			} else if (c == '"') {
				estado = Estado::CADENA;
				lexema += c;
				cadena = true;
			} else if (c == '.') {
				estado = Estado::INICIO;
				lexema += c;
				Token t = {TipoToken::PUNTO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} 
			else if (c == '{') {
				estado = Estado::INICIO,
				lexema += c;
				Token t = {TipoToken::LLAVE_IZQ, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == '}') {
				estado = Estado::INICIO,
				lexema += c;
				Token t = {TipoToken::LLAVE_DER, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == '[') {
				estado = Estado::INICIO,
				lexema += c;
				Token t = {TipoToken::CORCH_IZQ, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == ']') {
				estado = Estado::INICIO,
				lexema += c;
				Token t = {TipoToken::CORCH_DER, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == '(') {
				estado = Estado::INICIO,
				lexema += c;
				Token t = {TipoToken::PAREN_IZQ, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == ')') {
				estado = Estado::INICIO,
				lexema += c;
				Token t = {TipoToken::PAREN_DER, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == ',') {
				estado = Estado::INICIO,
				lexema += c;
				Token t = {TipoToken::COMA, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else if (c == ';') {
				estado = Estado::INICIO,
				lexema += c;
				Token t = {TipoToken::PUNTO_COMA, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			}
			else {
				estado = Estado::ERROR;
				lexema += c;
			}
			break;

		case Estado::ID:
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
				estado = Estado::ID;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t;
				if(palabras_reservadas.find(lexema) != palabras_reservadas.end())
					t = {TipoToken::PALABRA_RESERVADA, lexema, p.linea};
				else
					t = {TipoToken::IDENTIFICADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::MAS:
			if (c == '0') {
				estado = Estado::CERO;
				lexema += c;
			} else if (c >= '1' && c <= '9') {
				estado = Estado::ENTERO;
				lexema += c;
			}
			break;

		case Estado::MENOS:
			if (c == '0') {
				estado = Estado::CERO;
				lexema += c;
			} else if (c >= '1' && c <= '9') {
				estado = Estado::ENTERO;
				lexema += c;
			}
			break;

		case Estado::CERO:
			if (c == 'x' || c == 'X') {
				estado = Estado::_HEX_X;
				lexema += c;
			} else if (c >= '0' && c <= '7') {
				estado = Estado::OCTAL;
				lexema += c;
			} else if (c == '.') {
				estado = Estado::REAL_SIN_EXPONENTE;
				lexema += c;
			}
			break;

		case Estado::_HEX_X:
			if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) {
				estado = Estado::HEXADECIMAL;
				lexema += c;
			} else {
				estado = Estado::ERROR_NUM;
				lexema += c;
			}
			break;

		case Estado::HEXADECIMAL:
			if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) {
				estado = Estado::HEXADECIMAL;
				lexema += c;
			} else if ((c > 'F' && c <= 'Z') || (c > 'f' && c <= 'z')  || c == '.') {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::NUMERO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;
		
		case Estado::OCTAL:
			if ((c >= '0' && c <= '7')) {
				estado = Estado::OCTAL;
				lexema += c;
			} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '8' || c == '9' || c == '.') {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::NUMERO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::ENTERO:
			if (c >= '0' && c <= '9') {
				estado = Estado::OCTAL;
				lexema += c;
			} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else if (c == '.') {
				estado = Estado::_PUN_DEC;
				lexema += c;
			}
			break;

		case Estado::_PUN_DEC:
			if (c >= '0' && c <= '9') {
				estado = Estado::REAL_SIN_EXPONENTE;
				lexema += c;
			} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '.') {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::INVALIDO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::REAL_SIN_EXPONENTE:
			if (c >= '0' && c <= '9') {
				estado = Estado::REAL_SIN_EXPONENTE;
				lexema += c;
			} else if (c == 'E') {
				estado = Estado::_EXP;
				lexema += c;
			} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '.') {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::NUMERO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::_EXP:
			if (c == '+' || c == '-') {
				estado = Estado::_EXP_SIG;
				lexema += c;
			} else if (c >= '0' && c <= '9') {
				estado = Estado::REAL_CON_EXPONENTE;
				lexema += c;
			} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '.') {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::INVALIDO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::_EXP_SIG:
			if (c >= '0' && c <= '9') {
				estado = Estado::REAL_CON_EXPONENTE;
				lexema += c;
			} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '.') {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::INVALIDO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::REAL_CON_EXPONENTE:
			if (c >= '0' && c <= '9') {
				estado = Estado::REAL_CON_EXPONENTE;
				lexema += c;
			} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '.') {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::NUMERO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::IGUAL:
			if (c == '=') {
				estado = Estado::INICIO;
				lexema += c;
				Token t = {TipoToken::COMPARADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::ASIGNADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::MENOR:
			if (c == '=') {
				estado = Estado::INICIO;
				lexema += c;
				Token t = {TipoToken::COMPARADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::COMPARADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::MAYOR:
			if (c == '=') {
				estado = Estado::INICIO;
				lexema += c;
				Token t = {TipoToken::COMPARADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::COMPARADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::DIVISION:
			if(c == '*') {
				estado = Estado::COMENTARIO_MULTILINEA;
				comentarioMulti = true;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				lexema += c;
				Token t = {TipoToken::OPERADOR, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		case Estado::COMENTARIO_MULTILINEA:
			if (c == '*') {
				estado = Estado::COMENTARIO_MULTILINEA_2;
				lexema += c;
			} else {
				estado = Estado::COMENTARIO_MULTILINEA;
				lexema += c;
			}
			break;

		case Estado::COMENTARIO_MULTILINEA_2:
			if (c == '/') {
				estado = Estado::INICIO;
				lexema += "";
				comentarioMulti = false;
			} else if (c == '*') {
				estado = Estado::COMENTARIO_MULTILINEA_2;
				lexema += c;
			} else {
				estado = Estado::COMENTARIO_MULTILINEA;
				lexema += c;
			}
			break;

		case Estado::CADENA:
			if (c == '"') {
				estado = Estado::INICIO;
				lexema += c;
				cadena = false;
				Token t = {TipoToken::STRING, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
			} else {
				estado = Estado::CADENA;
				lexema += c;
			}
			break;

		case Estado::ERROR_NUM:
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '.') {
				estado = Estado::ERROR_NUM;
				lexema += c;
			} else {
				estado = Estado::INICIO;
				Token t = {TipoToken::INVALIDO, lexema, p.linea};
				ts.push_back(t);
				lexema = "";
				i--;
			}
			break;

		default:
			break;
		}
	}

	if(estado == Estado::ID) {
		Token t;
		if(palabras_reservadas.find(lexema) != palabras_reservadas.end())
			t = {TipoToken::PALABRA_RESERVADA, lexema, p.linea};
		else
			t = {TipoToken::IDENTIFICADOR, lexema, p.linea};
		ts.push_back(t);
		lexema = "";
	} else if(estado == Estado::CERO || estado == Estado::HEXADECIMAL || estado == Estado::OCTAL || estado == Estado::ENTERO || estado == Estado::REAL_SIN_EXPONENTE || estado == Estado::REAL_CON_EXPONENTE) {
		Token t = {TipoToken::NUMERO, lexema, p.linea};
		ts.push_back(t);
		lexema = "";
	} else if(estado == Estado::DIVISION || estado == Estado::MAS || estado == Estado::MENOS) {
		Token t = {TipoToken::OPERADOR, lexema, p.linea};
		ts.push_back(t);
		lexema = "";
	} else if(estado == Estado::IGUAL) {
		Token t = {TipoToken::ASIGNADOR, lexema, p.linea};
		ts.push_back(t);
		lexema = "";
	} else if(estado == Estado::MENOR || estado == Estado::MAYOR) {
		Token t = {TipoToken::COMPARADOR, lexema, p.linea};
		ts.push_back(t);
		lexema = "";
	} else if (estado == Estado::INICIO || estado == Estado::COMENTARIO_MULTILINEA || estado == Estado::COMENTARIO_MULTILINEA_2 || estado == Estado::CADENA) {
		
	} else {
		Token t = {TipoToken::INVALIDO, lexema, p.linea};
		ts.push_back(t);
		lexema = "";
	}

    return ts;
}
