#include "../include/buscador.h"

ResultadoRI::ResultadoRI(const double& kvSimilitud, const long int& kidDoc,const int& np){
    vSimilitud = kvSimilitud;
    idDoc = kidDoc;
    numPregunta = np;
}

double 
ResultadoRI::VSimilitud() const {
    return vSimilitud;
}

long int
ResultadoRI::IdDoc() const{
    return idDoc;
}

bool
ResultadoRI::operator< (const ResultadoRI& lhs) const{
    if(numPregunta == lhs.numPregunta)
        return (vSimilitud < lhs.vSimilitud);
    else
        return (numPregunta > lhs.numPregunta);
}

ostream&
operator<<(ostream &os, const ResultadoRI &res){
    os << res.vSimilitud << "\t\t" << res.idDoc << "\t" << res.numPregunta << endl;
    return os;
}

double
Buscador::IDF(int N, int nqi){
    double numerador = N - nqi + 0.5;
    double denominador = nqi + 0.5;
    double resultado = log2(numerador/denominador);
    
    return resultado;
}

Buscador::Buscador(const string& directorioIndexacion, const int& f): IndexadorHash(directorioIndexacion),formSimilitud(f), c(2),kl(1.2),b(0.75){
     
}

Buscador::Buscador(const Buscador& b): IndexadorHash(b), formSimilitud(b.formSimilitud), c(b.c), kl(b.kl), b(b.b){

}

Buscador::~Buscador(){
    
    formSimilitud = 0;
    c = 0;
    kl = 0;
    b = 0;
    while(!docsOrdenados.empty())
        docsOrdenados.pop();
}

Buscador& 
Buscador::operator=(const Buscador& buscador){
    if(this != &buscador){
        
        this->~Buscador();        
        formSimilitud = buscador.formSimilitud;
        c = buscador.c;
        kl = buscador.kl;
        b = buscador.b;
        while(!docsOrdenados.empty())
            docsOrdenados.pop();
        if(!docsOrdenados.empty())
            docsOrdenados = buscador.docsOrdenados;
        

    }
    return *this;
}

int Buscador::mi_reduce(const unordered_map<string,InfDoc>& docs){
    int total = 0;
    for(pair<string,InfDoc> par : docs){
        total += par.second.getNumPalSinParada();
    }
    return total;
}

double 
Buscador::DFR(const pair<string,InfDoc> &documento,const unordered_map<string,InfDoc> &documentos,unordered_map<string,InformacionTermino> &indice, const unordered_map<string,InformacionTerminoPregunta> &indicePregunta){
    double score = 0.0;
    
        
    
    int N = getInfColeccionDocs().getNumDocs();
    //cout << "N= " << N << endl;
    double avrld = double(mi_reduce(documentos)) / double(N);
    //cout << "avrld=" << avrld << endl;
    int ld = documento.second.getNumPalSinParada();
    //cout << "Documento: " << documento.first << endl;
    
    for(pair<string,InformacionTerminoPregunta> qi : indicePregunta){
        //cout << qi.first << endl;
        int k = getInfoQuery().getNumTotalPalSinParada();
        //cout << "k= " << k << endl;
        int ftq = qi.second.getFt();                    
        ////cout << "ftq= " << ftq << endl;                    
        unordered_map<string,InformacionTermino>::iterator itIndice = indice.find(qi.first);
        if(itIndice != indice.end()){
            int nt = itIndice->second.getTotalDocs();
            //cout << "nt= " << nt << endl;
            int ft = itIndice->second.getFtc();
            //cout << "ft= " << ft << endl;
            unordered_map<int,InfTermDoc>::iterator itDocs = itIndice->second.getDoc().find(documento.second.getIdDoc());
            if(itDocs != itIndice->second.getDoc().end()){
                int ftd = itDocs->second.getFt();
                double wtq = double(ftq) / double(k);
                //cout << "wtq = " << wtq << endl;
                double lambdat = double(ft) / double(N);
                double ftdAst = ftd * log2(1 + (this->c * avrld)/ld);
                double multiplicador1 = log2(1+lambdat) + ftdAst * log2((1+lambdat)/lambdat);
                //cout << "Multiplicador1 = " << multiplicador1 << endl;
                double multiplicador2 = (ft+1) / (nt * (ftdAst + 1));
                //cout << "Multiplicador2 = " << multiplicador2 << endl;
                double wtd = multiplicador1 * multiplicador2;
                //cout << "wtd = " << wtd << endl;
                score += wtq * wtd;
            }
        }

    }

    return score;
}

double 
Buscador::DFR(const pair<string,InfDoc> &documento,const unordered_map<string,InfDoc> &documentos,const string &queryNoTokenizada,unordered_map<string,InformacionTermino> &indice,const unordered_map<string,InformacionTerminoPregunta> &indicePregunta){
    double score = 0.0;
    IndexarPregunta(queryNoTokenizada);
    int N = getInfColeccionDocs().getNumDocs();
    //cout << "N= " << N << endl;
    double avrld = double(mi_reduce(documentos)) / double(N);
    //cout << "avrld=" << avrld << endl;
    int ld = documento.second.getNumPalSinParada();
    //cout << "Documento: " << documento.first << endl;
    
    for(pair<string,InformacionTerminoPregunta> qi : indicePregunta){
        //cout << qi.first << endl;
        int k = getInfoQuery().getNumTotalPalSinParada();
        //cout << "k= " << k << endl;
        int ftq = qi.second.getFt();                    
        ////cout << "ftq= " << ftq << endl;                    
        unordered_map<string,InformacionTermino>::iterator itIndice = indice.find(qi.first);
        if(itIndice != indice.end()){
            int nt = itIndice->second.getTotalDocs();
            //cout << "nt= " << nt << endl;
            int ft = itIndice->second.getFtc();
            //cout << "ft= " << ft << endl;
            unordered_map<int,InfTermDoc>::iterator itDocs = itIndice->second.getDoc().find(documento.second.getIdDoc());
            if(itDocs != itIndice->second.getDoc().end()){
                int ftd = itDocs->second.getFt();
                double wtq = double(ftq) / double(k);
                //cout << "wtq = " << wtq << endl;
                double lambdat = double(ft) / double(N);
                double ftdAst = ftd * log2(1 + (this->c * avrld)/ld);
                double multiplicador1 = log2(1+lambdat) + ftdAst * log2((1+lambdat)/lambdat);
                //cout << "Multiplicador1 = " << multiplicador1 << endl;
                double multiplicador2 = (ft+1) / (nt * (ftdAst + 1));
                //cout << "Multiplicador2 = " << multiplicador2 << endl;
                double wtd = multiplicador1 * multiplicador2;
                //cout << "wtd = " << wtd << endl;
                score += wtq * wtd;
            }
        }

    }
    return score;
}
    

double 
Buscador::BM25(const pair<string,InfDoc> &documento,const unordered_map<string,InfDoc> &documentos,unordered_map<string,InformacionTermino> &indice,const unordered_map<string,InformacionTerminoPregunta> &indicePregunta){
    double score = 0.0;
    
    InformacionPregunta infoQuery = getInfoQuery();
    int n = infoQuery.getNumTotalPalSinParada();
    //cout << "n= " << n << endl;
    int N = getInfColeccionDocs().getNumDocs();            
    //cout << "N=" << N << endl;
    
    int res = mi_reduce(documentos);
    //cout << "res = " << res << endl;
    double avgdl = double(res)/double(N);
    //cout << "avgdl= "<< avgdl<<endl;
    
    int fQiD;
    int nQi;
    double numerador, denominador;
    int id_Documento = documento.second.getIdDoc();
    int D = documento.second.getNumPalSinParada();                
                
    
    
    for(pair<string,InformacionTerminoPregunta> qi : indicePregunta){
        unordered_map<string,InformacionTermino>::iterator it = indice.find(qi.first);
                
        if(it != indice.end()){
            unordered_map<int,InfTermDoc> qiD = it->second.getDoc();
            unordered_map<int,InfTermDoc>::iterator it2 = qiD.find(id_Documento);
            if(it2 != qiD.end()){
                fQiD = qiD.find(id_Documento)->second.getFt();
                nQi = qiD.size();
                numerador = fQiD * (this->kl + 1);
                denominador = fQiD + this->kl * (1 - b + b * (D/avgdl));
                        
                double res = (numerador/denominador); 
                score += IDF(N,nQi) * res;
                        
            }
        }
                
                
    }
    return score;
}

double Buscador::getcputime(void){
        struct timeval tim;
        struct rusage ru;
        getrusage(RUSAGE_SELF,&ru);
        tim = ru.ru_utime;
        double t = (double)tim.tv_sec + (double)tim.tv_usec/1000000.0;
        tim = ru.ru_stime;
        t += (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
        return t;
}


double 
Buscador::BM25(const pair<string,InfDoc> &documento,const unordered_map<string,InfDoc> &documentos,const string &queryNoTokenizada,unordered_map<string,InformacionTermino> &indice,const unordered_map<string,InformacionTerminoPregunta> &indicePregunta){
    double score = 0.0;
    IndexarPregunta(queryNoTokenizada);
    InformacionPregunta infoQuery = getInfoQuery();
    int n = infoQuery.getNumTotalPalSinParada();
    //cout << "n= " << n << endl;
    int N = getInfColeccionDocs().getNumDocs();            
    //cout << "N=" << N << endl;
    
    int res = mi_reduce(documentos);
    //cout << "res = " << res << endl;
    double avgdl = double(res)/double(N);
    //cout << "avgdl= "<< avgdl<<endl;
    
    int fQiD;
    int nQi;
    double numerador, denominador;
    int id_Documento = documento.second.getIdDoc();
    int D = documento.second.getNumPalSinParada();                
                
   
    for(pair<string,InformacionTerminoPregunta> qi : indicePregunta){
        unordered_map<string,InformacionTermino>::iterator it = indice.find(qi.first);
                
        if(it != indice.end()){
            unordered_map<int,InfTermDoc> qiD = it->second.getDoc();
            unordered_map<int,InfTermDoc>::iterator it2 = qiD.find(id_Documento);
            if(it2 != qiD.end()){
                fQiD = qiD.find(id_Documento)->second.getFt();
                nQi = qiD.size();
                numerador = fQiD * (this->kl + 1);
                denominador = fQiD + this->kl * (1 - b + b * (D/avgdl));
                        
                double res = (numerador/denominador); 
                score += IDF(N,nQi) * res;
                        
            }
        }
                
                
    }
    return score;
}


bool
Buscador::Buscar(const int& numDocumentos){
    string pregunta = getPregunta();
    int numDocumentosAlmacenados = 0;
    if(!docsOrdenados.empty()){

        
        while(!docsOrdenados.empty())
            docsOrdenados.pop();
        

    }
        
    if (pregunta != ""){
        double score;
        
        unordered_map<string,InfDoc> documentos = getIndiceDocs();
        unordered_map<string,InformacionTermino> indice = getIndice();
        unordered_map<string,InformacionTerminoPregunta> indicePregunta = getIndicePregunta();  
        for(pair<string,InfDoc> documento : documentos){
            
            if(formSimilitud)
                score = BM25(documento,documentos,indice,indicePregunta);
            else
                score = DFR(documento,documentos,indice,indicePregunta);
            
            if(score != 0.0){

                ResultadoRI resultado(score,documento.second.getIdDoc(),0);
                if(numDocumentosAlmacenados < numDocumentos){
                    docsOrdenados.push(resultado);
                    numDocumentosAlmacenados++;
                }                                    
                if(numDocumentosAlmacenados == numDocumentos)
                    break;                    
            }                    
        }   

        return true;
    }
    
    return false;
}

bool
Buscador::Buscar(const string& dirPreguntas, const int& numDocumentos, const int& numPregInicio, const int& numPregFin){
    
    struct stat dir;
    // Compruebo la existencia del directorio
    int err=stat(dirPreguntas.c_str(), &dir);
    
    if(err==-1 || !S_ISDIR(dir.st_mode))
        return false;
    system(("find " + dirPreguntas + " -type f > /tmp/ficherosPreguntas.txt").c_str());
    
    int numPreguntas = 0;
    int numDocumentosAlmacenados;
    ifstream ficheroPreguntas("/tmp/ficherosPreguntas.txt");
    string pregunta;
    vector<string> preguntas(numPregFin-numPregInicio+1);
    if(ficheroPreguntas.is_open()){
        int i = 0;
        while(ficheroPreguntas >> pregunta){
            numPreguntas++;
            if(numPreguntas >= numPregInicio && numPreguntas <= numPregFin){
                preguntas[i] = pregunta;
                i++;
            }
            
        }
        ficheroPreguntas.close();
        
        double score = 0.0;
        if(!docsOrdenados.empty()){   
            while(!docsOrdenados.empty())
                docsOrdenados.pop();
        }
        
        unordered_map<string,InfDoc> documentos = getIndiceDocs();       
        
        unordered_map<string,InformacionTermino> indice = getIndice();
        unordered_map<string,InformacionTerminoPregunta> indicePregunta = getIndicePregunta();                 
        string query;
        int numPreguntas = 0;
        for(string nomFicheroPreguntas : preguntas){
            numPreguntas++; 
            numDocumentosAlmacenados = 0;
            ifstream ficheroPreguntas(nomFicheroPreguntas);

            if(ficheroPreguntas.is_open()){
                while(getline(ficheroPreguntas,query)){
                                             
                    for(pair<string,InfDoc> documento : documentos){
                        
                        if(formSimilitud)
                            score = BM25(documento,documentos,query,indice,indicePregunta);
                        else
                            score = DFR(documento,documentos,query,indice,indicePregunta);
                        if(score != 0.0){
                            ResultadoRI resultado(score,documento.second.getIdDoc(),numPreguntas);
                            if(numDocumentosAlmacenados < numDocumentos){
                                docsOrdenados.push(resultado);
                                numDocumentosAlmacenados++;
                                
                            }  
                            if(numDocumentosAlmacenados == numDocumentos)
                                break;
                            

                            
                        }
                    }   
                }
                ficheroPreguntas.close();    
                          
            }
            else
                return false;
            
        }        

    }   
    else 
        return false;
    
    return true;
}

string 
Buscador::obtenerNombreArchivo(const std::string& ruta) const{
    

    size_t pos = ruta.find_last_of('/');

    std::string nombreArchivo;
    if (pos == std::string::npos) {
        nombreArchivo = ruta;
    } else {
        nombreArchivo = ruta.substr(pos + 1);
    }

    size_t posPunto = nombreArchivo.find_last_of('.');
    if (posPunto != std::string::npos) {
        if (posPunto > 0) {
            nombreArchivo = nombreArchivo.substr(0, posPunto);
        }
    }

    return nombreArchivo;
}
void 
Buscador::ImprimirResultadoBusqueda(const int& numDocumentos) const{        
    priority_queue<ResultadoRI> copia = docsOrdenados;
    int docs = 0;
    while(!copia.empty()){
        ResultadoRI res = copia.top();
        copia.pop();
        
        if(docs < numDocumentos){
            cout << res.NumPregunta() << " ";
            if(formSimilitud == 0)
                cout << "DFR ";
            else
                cout << "BM25 ";
            for(pair<string,InfDoc> par : getIndiceDocs()){
                if(par.second.getIdDoc() == res.IdDoc()){
                    cout << obtenerNombreArchivo(par.first) << " ";  
                    break;
                }

            }

            
            cout << docs << " ";
            docs++;
            cout << res.VSimilitud() << " ";
            if(res.NumPregunta() == 0)
                cout << getPregunta() << endl;
            else
                cout << "ConjuntoDePreguntas" << endl;
        }        
        if(docs == numDocumentos && !copia.empty())
            docs = 0;
    }    

}

bool 
Buscador::ImprimirResultadoBusqueda(const int& numDocumentos, const string& nombreFichero) const{
    ofstream fichero(nombreFichero);
    
    if(!fichero.is_open()){
        return false;
    }
        
    int docs = 0;
    priority_queue<ResultadoRI> copia = docsOrdenados;
    while(!copia.empty()){
        ResultadoRI res = copia.top();
        copia.pop();
        
        if(docs < numDocumentos){
            fichero << res.NumPregunta() << " ";
            if(formSimilitud == 0)
                fichero << "DFR ";
            else
                fichero << "BM25 ";
            for(pair<string,InfDoc> par : getIndiceDocs()){
                if(par.second.getIdDoc() == res.IdDoc()){
                    fichero << obtenerNombreArchivo(par.first) << " ";  
                    break;
                }

            }

            
            fichero << docs << " ";
            docs++;
            fichero << res.VSimilitud() << " ";
            if(res.NumPregunta() == 0)
                fichero << getPregunta() + "\n";
                
            else
                fichero << "ConjuntoDePreguntas" + string("\n");
            
                
        }    
        
        if(docs == numDocumentos && !copia.empty())
            docs = 0;    
        
    }   
    fichero.close(); 
    return true;
}

int 
Buscador::DevolverFormulaSimilitud() const{
    return formSimilitud;
}

bool 
Buscador::CambiarFormulaSimilitud(const int& f){
    if(f == 0 || f == 1){
        formSimilitud = f;
        return true;
    }
    return false;
}

void 
Buscador::CambiarParametrosDFR(const double& kc){
    c = kc;
}

double 
Buscador::DevolverParametrosDFR() const{
    return c;
}

void 
Buscador::CambiarParametrosBM25(const double& kkl, const double& kb){
    kl = kkl;
    b = kb;
}

void 
Buscador::DevolverParametrosBM25(double& kkl, double& kb) const{
    kkl = kl;
    kb = b;
}

Buscador::Buscador() : IndexadorHash(), docsOrdenados(), formSimilitud(), c(2), kl(1.2), b(0.75) {
    
}

ostream& operator<<(ostream& s, const Buscador& p) {
    string preg;
    s << "Buscador: " << endl;      
    if(p.DevuelvePregunta(preg))
        s << "\tPregunta indexada: " << preg << endl;
    else
        s << "\tNo hay ninguna pregunta indexada" << endl;
    s << "\tDatos del indexador: " << endl << (IndexadorHash) p;
        
    return s;
}

