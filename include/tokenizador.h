#ifndef _TOKENIZADOR_H_
#define _TOKENIZADOR_H_

#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include <locale>

#define DELIMITERS "\",;:.-/+*\\ \\\"{}[]()<>¡!¿?&#=\\t\\n\\r@";
#define CASOS_ESPECIALES false;
#define QUITAR_MAYUS_ACENTOS false;
using namespace std;

extern const std::unordered_map<unsigned char,unsigned char> acentosMap;

class Tokenizador{
    friend ostream& operator<<(ostream& os, const Tokenizador& token);

    public:
        Tokenizador(const string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos);
        Tokenizador(const Tokenizador&);
        Tokenizador();
        ~Tokenizador();
        Tokenizador& operator=(const Tokenizador&);
        void Tokenizar(const string& str, list<string>& tokens, bool vaciarToken=true) const;
        bool Tokenizar(const string& i, const string& f,bool verbose) const;
        bool Tokenizar(const string& i,bool verbose=true) const;
        bool TokenizarListaFicheros(const string& i) const;
        bool TokenizarDirectorio(const string& i) const;
        void DelimitadoresPalabra(const string& nuevoDelimiters);
        void AnyadirDelimitadoresPalabra(const string& nuevoDelimiters);
        string DelimitadoresPalabra() const;
        void CasosEspeciales(const bool& nuevoCasosEspeciales);
        bool CasosEspeciales() const;
        void PasarAminuscSinAcentos(const bool& nuevoPasarAminuscSinAcentos);
        bool PasarAminuscSinAcentos() const;
        string toXML();
        string pasarAminuscQuitarAcentos(const string& str) const;

    private:
        string delimiters;
        bool casosEspeciales;
        bool pasarAminuscSinAcentos;
        

};

#endif