#ifndef _INDEXADOR_INFORMACION_H_
#define _INDEXADOR_INFORMACION_H_

#include <iostream>
#include <unordered_map>
#include <list>
#include <chrono>
#include "tokenizador.h"

using namespace std; 

class InfTermDoc{
    friend ostream& operator<<(ostream& s, const InfTermDoc& p);
    
    public:
        InfTermDoc (const InfTermDoc &);
        InfTermDoc ();
        ~InfTermDoc ();
        InfTermDoc & operator= (const InfTermDoc &);
        void plusFt(){ft++;}
        void setFt(int newFt){ft = newFt;}
        void pushPosTerm(int pos){posTerm.push_back(pos);}
        int getFt(){return ft;}
        string toXML();

    
    private:
        int ft;
        list<int> posTerm;
};


class InformacionTermino{
    friend ostream& operator<<(ostream& s, const InformacionTermino& p);

    public:
        InformacionTermino(const InformacionTermino &);
        InformacionTermino();
        ~InformacionTermino();
        InformacionTermino & operator=(const InformacionTermino&);
        void plusFtc(){ftc++;}
        void setFtc(int newFtc){ftc = newFtc;}
        void minusFtc(int minus){ftc -= minus;}
        void pushDoc(int first, InfTermDoc second){l_docs.insert(make_pair(first,second));}
        int getFtById(int id){return l_docs[id].getFt();}
        void eraseDocById(int id){if(l_docs.find(id) != l_docs.end()) l_docs.erase(id);}
        bool existDocById(int id){return l_docs.find(id) != l_docs.end();}
        void LimpiaListaDocumentos(){l_docs.clear();}
        unordered_map<int,InfTermDoc>& getDoc() {return l_docs;}
        string toXML();
        int getTotalDocs() const{ return l_docs.size();}
        int getFtc() const{ return ftc;}

    private:
        int ftc;
        unordered_map<int,InfTermDoc> l_docs;

};


class InfDoc{
    friend ostream& operator<<(ostream& s, const InfDoc& p);
    
    public:
        InfDoc (const InfDoc &);
        InfDoc ();
        ~InfDoc ();
        InfDoc & operator= (const InfDoc &);
        int getIdDoc() const{return idDoc;}        
        int getNumPal(){return numPal;}
        int getNumPalSinParada() const{return numPalSinParada;}        
        int getNumPalDiferentes(){return numPalDiferentes;}
        int getTamBytes(){return tamBytes;}
        void setIdDoc(int newDocId){idDoc = newDocId;}
        void setNumPal(int newNumPal){numPal = newNumPal;}
        void setNumPalSinParada(int newNumPalSinParada){numPalSinParada = newNumPalSinParada;}
        void setNumPalDiferentes(int newNumPalDiferentes){numPalDiferentes = newNumPalDiferentes;}
        void setTamBytes(int newTamBytes){tamBytes = newTamBytes;}
        string toXML();

        

    private:
        int idDoc;
        int numPal;
        int numPalSinParada;
        int numPalDiferentes;
        int tamBytes;
        std::chrono::system_clock::time_point fechaModificacion;

};

class InfColeccionDocs{
    friend ostream& operator<<(ostream& s, const InfColeccionDocs& p);
    
    public:
        InfColeccionDocs (const InfColeccionDocs &);
        InfColeccionDocs ();
        ~InfColeccionDocs ();
        InfColeccionDocs & operator= (const InfColeccionDocs &);
        void minusNumDoc(){numDocs--;}
        void minusNumTotalPal(int newNumTotalPal){numTotalPal -= newNumTotalPal;}
        void minusNumTotalPalSinParada(int newNumTotalPalSinParada){numTotalPalSinParada -= newNumTotalPalSinParada;}
        void minusNumTotalPalDiferentes(int newNumTotalPalDiferentes){numTotalPalDiferentes -= newNumTotalPalDiferentes;}
        void minusTamBytes(int newTamBytes){tamBytes-=newTamBytes;}
        void setNumDoc(int newNumDoc){numDocs = newNumDoc;}
        void setNumTotalPal(int newNumTotalPal){numTotalPal += newNumTotalPal;}
        void setNumTotalPalSinParada(int newNumTotalPalSinParada){numTotalPalSinParada += newNumTotalPalSinParada;}
        void setNumTotalPalDiferentes(int newNumTotalPalDiferentes){numTotalPalDiferentes += newNumTotalPalDiferentes;}
        void setTamBytes(int newTamBytes){tamBytes += newTamBytes;}
        string toXML();
        int getNumDocs(){return numDocs;}
        int getNumTotalPalSinParada() const{return numTotalPalSinParada;}

    private:
        int numDocs;
        int numTotalPal;
        int numTotalPalSinParada;
        int numTotalPalDiferentes;
        int tamBytes;
};


class InformacionTerminoPregunta{
    friend ostream& operator<<(ostream& s, const InformacionTerminoPregunta& p);
    
    public:
        InformacionTerminoPregunta (const InformacionTerminoPregunta &);
        InformacionTerminoPregunta ();
        ~InformacionTerminoPregunta ();
        InformacionTerminoPregunta & operator= (const InformacionTerminoPregunta&);
        void plusFt(){ft++;}
        void setFt(int newFt){ft = newFt;}
        void pushPosTerm(int pos){posTerm.push_back(pos);}
        string toXML();
        int getFt() const{return ft;}

    private:
        int ft;        
        list<int> posTerm;

};

class InformacionPregunta{
    friend ostream& operator<<(ostream& s, const InformacionPregunta& p);
    
    public:
        InformacionPregunta (const InformacionPregunta &);
        InformacionPregunta ();
        ~InformacionPregunta ();
        InformacionPregunta & operator= (const InformacionPregunta &);
        void plusNumTotalPal(){numTotalPal++;}
        void plusNumTotalPalSinParada(){numTotalPalSinParada++;}
        void plusNumTotalPalDiferentes(){numTotalPalDiferentes++;}
        void setNumTotalPal(int newNum){numTotalPal = newNum;}
        void setNumTotalPalDiferentes(int newNum){numTotalPalDiferentes = newNum;}
        void setNumPalSinParada(int newNum){numTotalPalSinParada = newNum;}
        string toXML();
        int getNumTotalPal() const{return numTotalPal;}
        int getNumTotalPalSinParada() const{return numTotalPalSinParada;}
        int getNumTotalPalDiferentes() const{return numTotalPalDiferentes;}

        
    private:
        int numTotalPal;
        int numTotalPalSinParada;
        int numTotalPalDiferentes;

};

#endif
