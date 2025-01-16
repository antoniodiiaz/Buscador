#ifndef _BUSCADOR_H_
#define _BUSCADOR_H_


#include <iostream>
#include <cmath>
#include "indexadorHash.h"
#include <numeric>
#include <sys/resource.h>
#include <iomanip> 


class ResultadoRI {
    friend ostream& operator<<(ostream&, const ResultadoRI&);

    public:
        ResultadoRI(const double& kvSimilitud, const long int& kidDoc, const int& np);
        double VSimilitud() const;
        int NumPregunta() const { return numPregunta;}
        long int IdDoc() const;
        bool operator< (const ResultadoRI& lhs) const;
    private:
        double vSimilitud;
        long int idDoc;
        int numPregunta;
};

class Buscador: public IndexadorHash{
    friend ostream& operator<<(ostream& s, const Buscador& p);

    public:
        double getcputime();
        Buscador(const string& directorioIndexacion, const int& f);
        Buscador(const Buscador&);
        ~Buscador();
        Buscador& operator=(const Buscador&);
        bool Buscar(const int& numDocumentos = 99999);
        bool Buscar(const string& dirPreguntas, const int& numDocumentos, const int& numPregInicio, const int& numPregFin);
        void ImprimirResultadoBusqueda(const int& numDocumentos=9999) const;
        bool ImprimirResultadoBusqueda(const int& numDocumentos, const string& nombreFichero) const;
        int DevolverFormulaSimilitud() const;
        bool CambiarFormulaSimilitud(const int& f);
        void CambiarParametrosDFR(const double& kc);    
        double DevolverParametrosDFR() const;
        void CambiarParametrosBM25(const double& kk1, const double& kb);
        void DevolverParametrosBM25(double& kk1, double& kb) const;
        double IDF(int N, int nqi);
        int mi_reduce(const unordered_map<string,InfDoc>& docs);
        string obtenerNombreArchivo(const std::string& ruta) const;
        double DFR(const pair<string,InfDoc> &documento,const unordered_map<string,InfDoc> &documentos,unordered_map<string,InformacionTermino> &indice,const unordered_map<string,InformacionTerminoPregunta> &indicePregunta);
        double DFR(const pair<string,InfDoc> &documento,const unordered_map<string,InfDoc> &documentos,const string &queryNoTokenizada,unordered_map<string,InformacionTermino> &indice,const unordered_map<string,InformacionTerminoPregunta> &indicePregunta);
        double BM25(const pair<string,InfDoc> &documento,const unordered_map<string,InfDoc> &documentos,unordered_map<string,InformacionTermino> &indice,const unordered_map<string,InformacionTerminoPregunta> &indicePregunta);
        double BM25(const pair<string,InfDoc> &documento,const unordered_map<string,InfDoc> &documentos,const string &queryNoTokenizada,unordered_map<string,InformacionTermino> &indice,const unordered_map<string,InformacionTerminoPregunta> &indicePregunta);

    private:
        Buscador();
        priority_queue<ResultadoRI> docsOrdenados;
        int formSimilitud;
        double c;
        double kl;
        double b;
    
};

#endif