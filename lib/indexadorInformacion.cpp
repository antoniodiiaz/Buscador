#include "../include/indexadorInformacion.h"
InformacionTermino::InformacionTermino(const InformacionTermino &it){
    this->ftc = it.ftc;
    this->l_docs.clear();
    for(const auto& par : it.l_docs){
        this->l_docs.insert({par.first,InfTermDoc(par.second)});                
    }
    
}

InformacionTermino::InformacionTermino(){
    this->ftc = 0;
}

InformacionTermino::~InformacionTermino(){
    this->ftc = 0;
    this->l_docs.clear();
} 


InformacionTermino&
InformacionTermino::operator=(const InformacionTermino& it){
    if(this != &it){
        this->ftc = it.ftc;
        this->l_docs.clear();
        for(auto par : it.l_docs){
            this->l_docs.insert({par.first,InfTermDoc(par.second)});                
        }        
    }
    return *this;        
}

string
InformacionTermino::toXML(){
    string xml;
    xml = "<InformacionTermino>\n";
    xml += "<ftc>\n" + to_string(ftc);
    xml += "\n</ftc>\n";
    if(l_docs.size() > 0){
        xml += "<l_docs>\n";
        for(pair<int,InfTermDoc> par : l_docs){
            xml += "<id>\n" + to_string(par.first);
            xml += "\n</id>\n";
            xml += par.second.toXML();
            
        }
        xml += "</l_docs>\n";

    }
    xml += "</InformacionTermino>\n";
    return xml;
}


InfTermDoc::InfTermDoc(const InfTermDoc &itd){
    this->ft = itd.ft;
    if(!itd.posTerm.empty()){
        for(const auto& elemento : itd.posTerm){
            this->posTerm.push_back(elemento);
        }
    }
}

InfTermDoc::InfTermDoc(){
    this->ft = 0;
}

InfTermDoc::~InfTermDoc (){
    this->ft = 0;
    this->posTerm.clear();
}

InfTermDoc& InfTermDoc::operator= (const InfTermDoc &itd){
    if(this != &itd){
        this->~InfTermDoc();
        this->ft = 0;
        if(!itd.posTerm.empty()){
            for(const auto& elemento : itd.posTerm){
                this->posTerm.push_back(elemento);
            }
        }
    }
    return *this;
}

string 
InfTermDoc::toXML(){
    string xml;
    xml = "<InfTermDoc>\n";
    xml += "<ft>\n";
    xml += to_string(this->ft);
    xml += "\n</ft>\n";
    if(posTerm.size() > 0){
        xml += "<posTerm>\n";
        for(int pos : posTerm){
            xml += to_string(pos);
            xml += "\n";
        }
        xml += "</posTerm>\n";
    }
    xml += "</InfTermDoc>\n";
    return xml;
    
}

InfDoc::InfDoc (const InfDoc &id): idDoc(id.idDoc),numPal(id.numPal),numPalSinParada(id.numPalSinParada),numPalDiferentes(id.numPalDiferentes),tamBytes(id.tamBytes),fechaModificacion(id.fechaModificacion){
}

InfDoc::InfDoc(): idDoc(),numPal(),numPalSinParada(),numPalDiferentes(),tamBytes(){
}

InfDoc::~InfDoc (){
    this->idDoc = 0;
    this->numPal = 0;
    this->numPalSinParada = 0;
    this->numPalDiferentes = 0;
    this->tamBytes = 0;
}

InfDoc& 
InfDoc::operator=(const InfDoc &id){
    if(this != &id){
        this->~InfDoc();
        this->idDoc = id.idDoc;
        this->numPal = id.numPal;
        this->numPalSinParada = id.numPalSinParada;
        this->numPalDiferentes = id.numPalDiferentes;
        this->tamBytes = id.tamBytes;
        this->fechaModificacion = id.fechaModificacion;
    }
    return *this;
}

string
InfDoc::toXML(){
    string xml;
    xml = "<InfDoc>\n";
    xml += "<idDoc>\n" + to_string(this->idDoc);
    xml += "\n</idDoc>\n";
    xml += "<numPal>\n" + to_string(this->numPal);
    xml += "\n</numPal>\n";
    xml += "<numPalSinParada>\n" + to_string(this->numPalSinParada);
    xml += "\n</numPalSinParada>\n";
    xml += "<numPalDiferentes>\n" + to_string(this->numPalDiferentes);
    xml += "\n</numPalDiferentes>\n";
    xml += "<tamBytes>\n" + to_string(this->tamBytes);
    xml += "\n</tamBytes>\n";
    xml += "</InfDoc>\n";
    return xml;
}

InfColeccionDocs::InfColeccionDocs (const InfColeccionDocs &icd){
    this->numDocs = icd.numDocs;
    this->numTotalPal = icd.numTotalPal;
    this->numTotalPalSinParada = icd.numTotalPalSinParada;
    this->numTotalPalDiferentes = icd.numTotalPalDiferentes;
    this->tamBytes = icd.tamBytes;
}

InfColeccionDocs::InfColeccionDocs (){
    this->numDocs = 0;
    this->numTotalPal = 0;
    this->numTotalPalSinParada = 0;
    this->numTotalPalDiferentes = 0;
    this->tamBytes = 0;
}

InfColeccionDocs::~InfColeccionDocs (){
    this->numDocs = 0;
    this->numTotalPal = 0;
    this->numTotalPalSinParada = 0;
    this->numTotalPalDiferentes = 0;
    this->tamBytes = 0;
}

InfColeccionDocs& 
InfColeccionDocs::operator= (const InfColeccionDocs &icd){
    if(this != &icd){
        this->~InfColeccionDocs();
        this->numDocs = icd.numDocs;
        this->numTotalPal = icd.numTotalPal;
        this->numTotalPalSinParada = icd.numTotalPalSinParada;
        this->numTotalPalDiferentes = icd.numTotalPalDiferentes;
        this->tamBytes = icd.tamBytes;
    }
    return *this;
}
string
InfColeccionDocs::toXML(){
    string xml;
    xml = "<InfColeccionDocs>\n";
    xml += "<numDocs>\n" + to_string(numDocs);
    xml += "\n</numDocs>\n";
    xml += "<numTotalPal>\n" + to_string(numTotalPal);
    xml += "\n</numTotalPal>\n";
    xml += "<numTotalPalSinParada>\n" + to_string(numTotalPalSinParada);
    xml += "\n</numTotalPalSinParada>\n";
    xml += "<numTotalPalDiferentes>\n" + to_string(numTotalPalDiferentes);
    xml += "\n</numTotalPalDiferentes>\n";
    xml += "<tamBytes>\n" + to_string(tamBytes);
    xml += "\n</tamBytes>\n";
    xml += "</InfColeccionDocs>\n";
    return xml;
}

InformacionTerminoPregunta::InformacionTerminoPregunta (const InformacionTerminoPregunta &itp){
    this->ft = itp.ft;
    if(!itp.posTerm.empty()){
        for(const auto& elemento : itp.posTerm){
            this->posTerm.push_back(elemento);
        }
    }
}


InformacionTerminoPregunta::InformacionTerminoPregunta (){
    this->ft = 0;
}

InformacionTerminoPregunta::~InformacionTerminoPregunta (){
    this->ft = 0;
    this->posTerm.clear();
}

InformacionTerminoPregunta&
InformacionTerminoPregunta::operator= (const InformacionTerminoPregunta& itp){
    if(this != &itp){
        this->~InformacionTerminoPregunta();
        this->ft = itp.ft;
        if(!itp.posTerm.empty()){
            for(const auto& elemento : itp.posTerm){
                this->posTerm.push_back(elemento);
            }
        }
    }
    return *this;
}

string
InformacionTerminoPregunta::toXML(){
    string xml;
    xml = "<InformacionTerminoPregunta>\n";
    xml += "<ft>\n";
    xml += to_string(this->ft);
    xml += "\n</ft>\n";
    if(posTerm.size() > 0){
        xml += "<posTerm>\n";
        for(int pos : posTerm){
            xml += to_string(pos);
            xml += "\n";
        }
        xml += "</posTerm>\n";
    }
    xml += "</InformacionTerminoPregunta>\n";
    return xml;
}

InformacionPregunta::InformacionPregunta (const InformacionPregunta &ip){
    this->numTotalPal = ip.numTotalPal;
    this->numTotalPalDiferentes = ip.numTotalPalDiferentes;
    this->numTotalPalSinParada = ip.numTotalPalSinParada;
}

InformacionPregunta::InformacionPregunta (){
    this->numTotalPal = 0;
    this->numTotalPalDiferentes = 0;
    this->numTotalPalSinParada = 0;
}

InformacionPregunta::~InformacionPregunta (){
    this->numTotalPal = 0;
    this->numTotalPalDiferentes = 0;
    this->numTotalPalSinParada = 0;
}

InformacionPregunta&
InformacionPregunta::operator= (const InformacionPregunta &ip){
    if(this != &ip){
        this->~InformacionPregunta();
        this->numTotalPal = ip.numTotalPal;
    this->numTotalPalDiferentes = ip.numTotalPalDiferentes;
    this->numTotalPalSinParada = ip.numTotalPalSinParada;
    }
    return *this;
}

string
InformacionPregunta::toXML(){
    string xml;
    xml = "<InformacionPregunta>\n";
    xml += "<numTotalPal>\n" + to_string(this->numTotalPal);
    xml += "\n</numTotalPal>\n";
    xml += "<numPalSinParada>\n" + to_string(this->numTotalPalSinParada);
    xml += "\n</numPalSinParada>\n";
    xml += "<numTotalPalDiferentes>\n" + to_string(this->numTotalPalDiferentes);
    xml += "\n</numTotalPalDiferentes>\n";
    xml += "</InformacionPregunta>\n";
    return xml;
}



ostream& 
operator<<(ostream& os, const InformacionTermino& it){
    os << "Frecuencia total: " << it.ftc << "\tfd: " << it.l_docs.size();
    for(const auto& elemento : it.l_docs){
        os << "\tId.Doc: " << elemento.first << "\t" <<  elemento.second;
    }
    return os;
}


ostream& 
operator<<(ostream& os, const InfTermDoc& itd){
    os << "ft: " << itd.ft;
    for(const auto& elemento : itd.posTerm){
        os << "\t" << elemento;
    }
    return os;
}


ostream& 
operator<<(ostream& os, const InfDoc& id){
    os << "idDoc: " << id.idDoc << "\tnumPal: " << id.numPal << "\tnumPalSinParada: " << id.numPalSinParada << "\tnumPalDiferentes: " << id.numPalDiferentes << "\ttamBytes: " << id.tamBytes;
    return os;
}


ostream& 
operator<<(ostream& os, const InfColeccionDocs& icd){
    os << "numDocs: " << icd.numDocs << "\tnumTotalPal: " << icd.numTotalPal << "\tnumTotalPalSinParada: " << icd.numTotalPalSinParada << "\tnumTotalPalDiferentes: " << icd.numTotalPalDiferentes << "\ttamBytes: " << icd.tamBytes;
    return os;
}


ostream& 
operator<<(ostream& os, const InformacionTerminoPregunta& itp){
    os << "ft: " << itp.ft;
    for(const auto& elemento : itp.posTerm){
        os << "\t" << elemento;
    }
    return os;
}


ostream& 
operator<<(ostream& os, const InformacionPregunta& ip){
    os << "numTotalPal: " << ip.numTotalPal << "\tnumTotalPalSinParada: " << ip.numTotalPalSinParada << "\tnumTotalPalDiferentes: " << ip.numTotalPalDiferentes;    
    return os;
}



