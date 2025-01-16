#ifndef _INDEXADORHASH_H_
#define _INDEXADORHASH_H_

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>
#include <bits/stdc++.h>
#include "indexadorInformacion.h"
#include "tokenizador.h"
#include "stemmer.h"
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>


using namespace std;
class IndexadorHash{
    friend ostream& operator<<(ostream& s, const IndexadorHash& p);

    public:
        IndexadorHash();
        IndexadorHash(const string& fichStopWords, const string& delimitadores, const bool& detectComp, const bool& minuscSinAcentos, const string& dirIndice, const int& tStemmer, const bool& almEnDisco, const bool& almPosTerm);
        IndexadorHash(const string& directorioIndexacion);
        IndexadorHash(const IndexadorHash&);
        ~IndexadorHash();
        IndexadorHash& operator= (const IndexadorHash&);
        bool Indexar(const string& ficheroDocumentos);
        bool IndexarDirectorio(const string& dirAIndexar);
        bool GuardarIndexacion();
        bool RecuperarIndexacion (const string& directorioIndexacion);
        void ImprimirIndexacion() const;
        bool IndexarPregunta(const string& preg);
        bool DevuelvePregunta(string& preg) const;
        bool DevuelvePregunta(const string& word, InformacionTerminoPregunta& inf) const;
        bool DevuelvePregunta(InformacionPregunta& inf) const;
        void ImprimirIndexacionPregunta(); 
        void ImprimirPregunta();
        bool Devuelve(const string& word, InformacionTermino& inf) const;
        bool Devuelve(const string& word, const string& nomDoc, InfTermDoc& InfDoc) const;
        bool Existe(const string& word) const;
        bool BorraDoc(const string& nomDoc);
        void VaciarIndiceDocs();
        void VaciarIndicePreg();
        int NumPalIndexadas() const;
        int NumDocIndexados() const;
        string DevolverFichPalParada () const;
        void ListarPalParada() const;
        int NumPalParada() const;
        string DevolverDelimitadores () const;
        bool DevolverCasosEspeciales () const;
        bool DevolverPasarAminuscSinAcentos () const;
        bool DevolverAlmacenarPosTerm () const;
        string DevolverDirIndice () const;
        int DevolverTipoStemming () const;
        bool DevolverAlmEnDisco () const;
        void ListarInfColeccDocs() const;
        void ListarTerminos() const;
        bool ListarTerminos(const string& nomDoc) const;
        void ListarDocs() const;
        bool ListarDocs(const string& nomDoc) const;
        unordered_map<string, InfDoc> getIndiceDocs() const{return indiceDocs;}
        unordered_map<string, InformacionTermino> getIndice() const{return indice;}
        unordered_map<string, InformacionTerminoPregunta> getIndicePregunta() const{ return indicePregunta; }
        InfColeccionDocs getInfColeccionDocs() const{return informacionColeccionDocs;}
        string indiceToXML();
        string indiceDocsToXML();
        string indicePreguntaToXML();
        string stopWordsToXML();
        string toXML();
        Tokenizador getTokenizador() const{return tok;}
        string getPregunta() const{return pregunta;}
        InformacionPregunta getInfoQuery() const{ return infPregunta;}


    private:
        unordered_map<string, InformacionTermino> indice;
        unordered_map<string, InfDoc> indiceDocs;
        InfColeccionDocs informacionColeccionDocs;
        string pregunta;
        unordered_map<string, InformacionTerminoPregunta> indicePregunta;
        InformacionPregunta infPregunta;
        unordered_set<string> stopWords;
        string ficheroStopWords;
        Tokenizador tok;
        string directorioIndice;
        int tipoStemmer;
        bool almacenarEnDisco;
        bool almacenarPosTerm;

};

#endif