#include "../include/indexadorHash.h"

IndexadorHash::IndexadorHash(const string& fichStopWords, const string& delimitadores, const bool& detectComp, const bool& minuscSinAcentos, const string& dirIndice, const int& tStemmer, const bool& almEnDisco, const bool& almPosTerm): ficheroStopWords(fichStopWords), tok(delimitadores,detectComp,minuscSinAcentos),tipoStemmer(tStemmer),almacenarEnDisco(almEnDisco),almacenarPosTerm(almPosTerm),stopWords(),indice(),indiceDocs(),indicePregunta(),pregunta(){    
    ifstream fich(ficheroStopWords);
    if(!fich.is_open()){
        cerr << "ERROR: No se ha podido abrir el archivo " << ficheroStopWords<< endl;    
    }
    else{
        string stopWord;
        while (fich >> stopWord){
            stopWords.insert(stopWord);
        }
        fich.close();
        
    }
    if(dirIndice == ""){
        
        this->directorioIndice = "./";
    }   
    else
        this->directorioIndice = dirIndice;

}



IndexadorHash::IndexadorHash(const string& dirAIndexar){
    string ficheroTexto;
    if(dirAIndexar == "./" || dirAIndexar == "/" || dirAIndexar == "")
        ficheroTexto = "indexador.indx";    
    else
        ficheroTexto = dirAIndexar + "/indexador.indx";
    
    ifstream fichero(ficheroTexto);
    if(fichero.is_open()){
        string linea;
        bool primerDelimiter = false;
        bool ind, termino, informacionTermino, id, ftc, l_docs, inftermdoc,ft,posterm,indDocs,documento,infdoc,iddoc,numpal,numpalsinparada,numpaldiferentes,tambytes,infcolecciondocs,numdocs,numtotalpal,numtotalpalsinparada,numtotalpaldiferentes,preg,indicepregunta,informacionterminopregunta,infpreg,stopwords,ficherostopwords,tokenizador,delimitadores,casosespeciales,minus,dir,stemmer,disco;
        termino = ind = informacionTermino = id = ftc = l_docs = inftermdoc = ft = posterm = indDocs = documento = infdoc = iddoc = numpal = numpalsinparada = numpaldiferentes = tambytes = infcolecciondocs = numdocs = numtotalpal = numtotalpalsinparada = numtotalpaldiferentes = preg = indicepregunta = informacionterminopregunta = infpreg = stopwords = ficherostopwords = tokenizador = delimitadores = casosespeciales = minus = dir = stemmer = disco = false;
        pair<string, InformacionTermino> t;
        pair<int,InfTermDoc> informacion;
        pair<string,InfDoc> informacionDocumentos;
        pair<string,InformacionTerminoPregunta> informacionPregunta;

        while(fichero >> linea){
            if(linea == "</indice>"){
                ind = false;   
                
            }
            else if(linea == "<indice>"||ind){
                
                    
                ind = true;
                if(linea == "<termino>"){
                    termino = true;       
                }
                else if(termino){
                    t.first = linea;
                    termino = false;
                }
                else if(linea == "</InformacionTermino>"){
                    informacionTermino = false;
                }
                else if(linea == "<InformacionTermino>" || informacionTermino){
                    informacionTermino = true;
                    if(linea == "<ftc>"){
                        ftc = true;
                    }
                    else if(ftc){          
                        t.second.setFtc(stoi(linea));
                        
                        ftc = false;
                    }
                    else if(linea == "</l_docs>"){
                        l_docs = false;
                        this->indice.insert(t);           
                        t.second.LimpiaListaDocumentos();      
                        
                    }
                        
                    else if(linea == "<l_docs>" || l_docs){
                        
                        l_docs = true;
                        if(linea == "<id>"){
                            id = true;
                        }
                        else if(id){
                            informacion.first = stoi(linea);
                            id = false;
                        }
                        else if(linea == "</InfTermDoc>"){
                            inftermdoc =false;
                            //Informacion va bien, recoge toda la información bien
                            t.second.pushDoc(informacion.first,informacion.second);
                            informacion.second.~InfTermDoc();
                        }
                        else if(linea == "<InfTermDoc>" || inftermdoc){
                            inftermdoc = true;
                            if(linea == "<ft>"){
                                ft = true;
                            }
                            else if(ft){
                                informacion.second.setFt(stoi(linea));
                                ft = false;
                            }
                            else if(linea == "</posTerm>"){
                                posterm = false;

                            }
                            else if(linea == "<posTerm>" || posterm){
                                posterm = true;
                                if(posterm && linea != "<posTerm>"){
                                    informacion.second.pushPosTerm(stoi(linea));
                                }
                                
                            }
                            
                        }


                    }


                }                                        
            }

            else if(linea == "</indiceDocs>"){
                indDocs = false;   
            }
            else if(linea == "<indiceDocs>" || indDocs){
                indDocs = true;
                if(linea == "<documento>"){
                    documento = true;
                }
                else if(documento){
                    informacionDocumentos.first = linea;
                    documento = false;
                }
                else if(linea == "</InfDoc>"){
                    infdoc = false;
                    indiceDocs.insert(informacionDocumentos);
                }
                else if(linea == "<InfDoc>" || infdoc){
                    infdoc = true;
                    if(linea == "<idDoc>"){
                        iddoc = true;
                    }
                    else if(iddoc){
                        iddoc = false;
                        informacionDocumentos.second.setIdDoc(stoi(linea));
                    }

                    else if(linea == "<numPal>")
                        numpal = true;
                    else if(numpal){
                        numpal = false;
                        informacionDocumentos.second.setNumPal(stoi(linea));
                    }
                    else if(linea == "<numPalSinParada>")
                        numpalsinparada = true;
                    else if(numpalsinparada){
                        numpalsinparada = false;
                        informacionDocumentos.second.setNumPalSinParada(stoi(linea));
                    }
                    else if(linea == "<numPalDiferentes>")
                        numpaldiferentes = true;
                    else if(numpaldiferentes){
                        numpaldiferentes = false;
                        informacionDocumentos.second.setNumPalDiferentes(stoi(linea));
                    }
                    else if(linea == "<tamBytes>")
                        tambytes = true;
                    else if(tambytes){
                        tambytes = false;
                        informacionDocumentos.second.setTamBytes(stoi(linea));
                    }
                }
            }
            else if(linea == "</InfColeccionDocs>"){
                infcolecciondocs = false;
            }
            else if(linea == "<InfColeccionDocs>" || infcolecciondocs){
                infcolecciondocs = true;
                if(linea == "<numDocs>")
                    numdocs = true;
                else if(numdocs){
                    numdocs = false;
                    informacionColeccionDocs.setNumDoc(stoi(linea));
                }
                else if(linea == "<numTotalPal>")
                    numtotalpal = true;
                else if(numtotalpal){
                    numtotalpal = false;
                    informacionColeccionDocs.setNumTotalPal(stoi(linea));
                }
                else if(linea == "<numTotalPalSinParada>")
                    numtotalpalsinparada = true;
                else if(numtotalpalsinparada){
                    numtotalpalsinparada = false;
                    informacionColeccionDocs.setNumTotalPalSinParada(stoi(linea));
                }
                else if(linea == "<numTotalPalDiferentes>")
                    numtotalpaldiferentes = true;
                else if(numtotalpaldiferentes){
                    numtotalpaldiferentes = false;
                    informacionColeccionDocs.setNumTotalPalDiferentes(stoi(linea));
                }
                else if(linea == "<tamBytes>")
                    tambytes = true;
                else if(tambytes){
                    tambytes = false;
                    informacionColeccionDocs.setTamBytes(stoi(linea));
                }
            }
            else if(linea == "<pregunta>")
                preg = true;
            else if(preg){
                preg = false;
                pregunta = linea;
            }
            else if(linea == "</indicePregunta>"){
                indicepregunta = false;
                indicePregunta.insert(informacionPregunta);
            }
            else if(linea == "<indicePregunta>" || indicepregunta){
                indicepregunta = true;
                if(linea == "<termino>")
                    termino = true;
                else if(termino){
                    termino = false;
                    informacionPregunta.first = linea;
                }
                else if(linea == "</InformacionTerminoPregunta>"){
                    informacionterminopregunta = false;            
                }
                else if(linea == "<InformacionTerminoPregunta>" || informacionterminopregunta){
                    informacionterminopregunta = true;
                    if(linea == "<ft>")
                        ft = true;
                    else if(ft){
                        ft = false;
                        informacionPregunta.second.setFt(stoi(linea));
                    }
                    else if(linea == "</posTerm>"){
                        posterm = false;
                    }
                    else if(linea == "<posTerm>" || posterm){
                        posterm = true;
                        informacion.second.pushPosTerm(stoi(linea));
                    }
                }
            }

            else if(linea == "</InformacionPregunta>")
                infpreg = false;
            else if(linea == "<InformacionPregunta>" || infpreg){
                infpreg = true;
                if(linea == "<numTotalPal>")
                    numtotalpal = true;
                else if(numtotalpal){
                    numtotalpal = false;
                    infPregunta.setNumTotalPal(stoi(linea));
                }
                else if(linea == "<numPalSinParada>")
                    numpalsinparada = true;
                else if(numpalsinparada){
                    numpalsinparada = false;
                    infPregunta.setNumPalSinParada(stoi(linea));
                }
                else if(linea == "<numTotalPalDiferentes>")
                    numtotalpaldiferentes = true;
                else if(numtotalpaldiferentes){
                    numtotalpaldiferentes = false;
                    infPregunta.setNumTotalPalDiferentes(stoi(linea));
                }

            }

            else if(linea == "</stopWords>")
                stopwords = false;
            else if(linea == "<stopWords>" || stopwords){
                stopwords = true;
                if(linea != "<stopWords>")
                    stopWords.insert(linea);
            }
            else if(linea == "<ficheroStopWords>")
                ficherostopwords = true;
            else if(ficherostopwords){
                ficherostopwords = false;
                ficheroStopWords = linea;
            }

            else if(linea == "</Tokenizador>"){
                tokenizador = false;
            }
            else if(linea == "<Tokenizador>" || tokenizador){
                
                tokenizador = true;
                if(linea == "</delimitadores>"){
                    delimitadores = false;
                
                }
                else if(linea == "<delimitadores>"){
                    delimitadores = true;
                
                }
                else if(delimitadores){
                    tok.AnyadirDelimitadoresPalabra(" ");
                    if(primerDelimiter)
                        linea = " " + linea;
                    
                        
                    if(!primerDelimiter)
                        primerDelimiter = true;
                    
                        
                    
                    
                    tok.AnyadirDelimitadoresPalabra(linea);
                }
                else if(linea == "<casosEspeciales>"){
                    casosespeciales = true;
                }
                    
                else if(casosespeciales){
                    
                    casosespeciales = false;
                    tok.CasosEspeciales(stoi(linea));
                    
                }
                else if(linea == "<pasarAminuscSinAcentos>"){
                    minus = true;
                    
                }
                    
                else if(minus){
                    minus = false;
                    
                    tok.PasarAminuscSinAcentos(stoi(linea));
                }
            }

            else if(linea == "<directorioIndice>")
                dir = true;
            else if(dir){
                dir = false;
                directorioIndice = linea;
            }
            
            else if(linea == "<tipoStemmer>")
                stemmer = true;
            else if(stemmer){
                stemmer = false;
                tipoStemmer = stoi(linea);
            }

            else if(linea == "<almacenarEnDisco>")
                disco = true;
            else if(disco){
                disco = false;
                almacenarEnDisco = stoi(linea);
            }

            else if(linea == "<almacenarPosTerm>")
                posterm = true;
            else if(posterm){
                posterm = false;
                almacenarPosTerm = stoi(linea);
            }
           
        }

        fichero.close();
    }
       
}

IndexadorHash::IndexadorHash(const IndexadorHash& ih): ficheroStopWords(ih.ficheroStopWords),tok(ih.tok),directorioIndice(ih.directorioIndice),tipoStemmer(ih.tipoStemmer),almacenarEnDisco(ih.almacenarEnDisco),almacenarPosTerm(ih.almacenarPosTerm),indice(ih.indice),indiceDocs(ih.indiceDocs),informacionColeccionDocs(ih.informacionColeccionDocs),indicePregunta(ih.indicePregunta),infPregunta(ih.infPregunta){

}
    
IndexadorHash::~IndexadorHash(){
    this->ficheroStopWords = "";
    this->directorioIndice = "";
    this->tipoStemmer = 0;
    this->almacenarEnDisco = 0;
    this->almacenarPosTerm = 0;
    this->indice.clear();
    indiceDocs.clear();
    indicePregunta.clear();
    stopWords.clear();
    
}

IndexadorHash&
IndexadorHash::operator= (const IndexadorHash& ih){
    if(this != &ih){
        this->~IndexadorHash();
        this->ficheroStopWords = ih.ficheroStopWords;
        this->tok = ih.tok;
        this->directorioIndice = ih.directorioIndice;
        this->tipoStemmer = ih.tipoStemmer;
        this->almacenarEnDisco = ih.almacenarEnDisco;
        this->almacenarPosTerm = ih.almacenarPosTerm;

    }
    return *this;
}

bool
IndexadorHash::Indexar(const string& ficheroDocumentos){
    if(!tok.TokenizarListaFicheros(ficheroDocumentos)){
        //cout << "ERROR: No se ha podido tokenizar el fichero: " << ficheroDocumentos << endl;
        return false;
    }
    else{
        ifstream documento(ficheroDocumentos);
        
        if(!documento.is_open()){
            //cerr << "ERROR: No se ha podido abrir el fichero " << ficheroDocumentos << endl;
            return false;
        }
        else{
            string ficheroAIndexar;
            stemmerPorter sp;
            struct stat stat_buf;
            bool documentoIndexado = false;
            int indexadosMemoria = 0;
            
            ofstream ficheroIndices("indice.indx");
            ofstream ficheroIndiceDocs("indiceDocs.indx");
            
            
            while(documento >> ficheroAIndexar){
                
                if(this->indiceDocs.empty() || this->indiceDocs.find(ficheroAIndexar) == this->indiceDocs.end())
                    this->indiceDocs.insert(std::make_pair(ficheroAIndexar,InfDoc()));                    
                else
                    documentoIndexado = true;
                
                InfDoc *doc = (&this->indiceDocs.find(ficheroAIndexar)->second);
                if(!documentoIndexado){
                    (*doc).setIdDoc(this->indiceDocs.size());
                    this->informacionColeccionDocs.setNumDoc(this->indiceDocs.size());
                }
                
                
                ifstream documentoIndexar(ficheroAIndexar);
                
                if(!documentoIndexar.is_open()){
                    //cerr << "ERROR: No se ha podido abrir el fichero " << ficheroAIndexar << endl;
                    return false;
                }                   
                else{
                    int palabras = 0;
                    int palabrasSinParada = 0;
                    int palabrasDiferentes = 0;
                    int palabrasDiferentesDocumentos = 0;
                    string palabra;
                    list<string> tokens;
                    int pos = 0;
                    while(getline(documentoIndexar,palabra)){
                        tok.Tokenizar(palabra,tokens,true);
                                                
                        if(!tokens.empty()){
                            for(string token : tokens){
                                
                                palabras++;      
                                std::unordered_set<string>::iterator it = stopWords.find(token);
                                if(it == stopWords.end()){
                                    palabrasSinParada++;          
                                    if(this->tipoStemmer > 0)
                                        sp.stemmer(token,this->tipoStemmer);    
                                    
                                    
                                    if(indice.empty() ||indice.find(token) == indice.end()){
                                        indice.insert(make_pair(token,InformacionTermino()));                                                                     
                                        palabrasDiferentes++;
                                        
                                    }
                                    else if(indice.find(token) != indice.end()){
                                        
                                        InformacionTermino *termino = (&this->indice.find(token)->second);                                    
                                        if(termino->getDoc().find(doc->getIdDoc()) == termino->getDoc().end()){
                                            
                                            palabrasDiferentes++;
                                            palabrasDiferentesDocumentos++;
                                        }   
                                            
                                    }

                                    InformacionTermino *termino = (&this->indice.find(token)->second);                                    
                                    termino->plusFtc();

                                    unordered_map<int,InfTermDoc> *l_docs = (&termino->getDoc());
                                    if(l_docs->find(doc->getIdDoc()) == l_docs->end()){
                                        termino->pushDoc(doc->getIdDoc(),InfTermDoc());
                                        
                                    }                                                                
                                    l_docs->find(doc->getIdDoc())->second.plusFt();
                                    if(almacenarPosTerm)
                                        l_docs->find(doc->getIdDoc())->second.pushPosTerm(pos);
                                
                                    
                                    
                                }                        


                                pos++;
                            }
                            
                        }

                        
                    }
                    documentoIndexar.close();
                    
                    (*doc).setNumPal(palabras);
                    (*doc).setNumPalDiferentes(palabrasDiferentes);
                    (*doc).setNumPalSinParada(palabrasSinParada);   
                    stat(ficheroAIndexar.c_str(), &stat_buf);
                    (*doc).setTamBytes(stat_buf.st_size);                
                    if(!documentoIndexado){
                        this->informacionColeccionDocs.setNumTotalPal(palabras);
                        this->informacionColeccionDocs.setNumTotalPalDiferentes(palabrasDiferentes-palabrasDiferentesDocumentos);
                        this->informacionColeccionDocs.setNumTotalPalSinParada(palabrasSinParada);
                        this->informacionColeccionDocs.setTamBytes(stat_buf.st_size);
                    }
                    documentoIndexado = false;
                    pos = 0;
                    if(almacenarEnDisco){
                        indexadosMemoria++;
                        if(indexadosMemoria == 10){
                            ficheroIndices << indiceToXML() + "\n";
                            ficheroIndiceDocs << indiceDocsToXML() + "\n";
                            indice.clear();
                            indiceDocs.clear();
                            indexadosMemoria = 0;
                        }
                    }
                    
                }

            }
            documento.close();
            ficheroIndiceDocs.close();
            ficheroIndices.close();
            
            return true;
        }
    }
    
}

bool
IndexadorHash::IndexarDirectorio(const string& dirAIndexar){
    struct stat dir;
    // Compruebo la existencia del directorio
    int err=stat(dirAIndexar.c_str(), &dir);
    if(err==-1 || !S_ISDIR(dir.st_mode))
        return false;
    system(("find " + dirAIndexar + " -type f > /tmp/ficherosIndexar.txt").c_str());
    return Indexar("/tmp/ficherosIndexar.txt");

}
    
bool
IndexadorHash::GuardarIndexacion() {
    string dir = directorioIndice;
    if(dir.empty())
        dir = "./";
    
    system(("mkdir -p " + dir).c_str());
    
    string ficheroIndexacionDisco = dir + "/indexador.indx";
    ofstream fichero(ficheroIndexacionDisco);

    if(!fichero.is_open())
        return false;
    fichero << this->toXML() + "\n";
    fichero.close();
    return true;
}   

bool
IndexadorHash::RecuperarIndexacion (const string& directorioIndexacion){
    try{
        this->~IndexadorHash();
        IndexadorHash indexador(directorioIndexacion);
        *this = indexador;
        return true;
    }
    catch(const exception e){        
        return false;
    }
}

void 
IndexadorHash::ImprimirIndexacion() const{
    cout << "Terminos indexados: " << endl;
    for(const auto& par: indice){
        cout << par.first << '\t' << par.second << endl;
    }
    cout << "Documentos indexados: " << endl;
    for(const auto& par: indiceDocs){
        cout << par.first << '\t' << par.second << endl;
    }
}

bool
IndexadorHash::IndexarPregunta(const string& preg){
    pregunta = preg;
    try{
        
        indicePregunta.clear();
        infPregunta.~InformacionPregunta();
        list<string> pregTokenizada;
        tok.Tokenizar(pregunta,pregTokenizada);
        stemmerPorter sp;
        int pos = 0;

        for(list<string>::iterator it = pregTokenizada.begin(); it != pregTokenizada.end();++it){
            string token = *it;
            
            sp.stemmer(token,this->tipoStemmer);
            
            if(stopWords.find(token) == stopWords.end()){
                if(indicePregunta.find(token) == indicePregunta.end()){
                    indicePregunta.insert(make_pair(token,InformacionTerminoPregunta()));
                    infPregunta.plusNumTotalPalDiferentes();
                }
                InformacionTerminoPregunta *termino = (&this->indicePregunta.find(token)->second);                                    
                termino->plusFt();
                if(almacenarPosTerm)
                    termino->pushPosTerm(pos);
                
                infPregunta.plusNumTotalPalSinParada();
            }
            pos++;
            infPregunta.plusNumTotalPal();
        }
    }catch (const std::exception& e){
        return false;
    }
    return true;
}

bool
IndexadorHash::DevuelvePregunta(string& preg) const{
    if(indicePregunta.size() > 0){
        preg = pregunta;
        return true;
    }
    return false;
}

bool
IndexadorHash::DevuelvePregunta(const string& word, InformacionTerminoPregunta& inf) const{
    stemmerPorter sp;
    string palabra;
    
    if(tok.PasarAminuscSinAcentos())
        palabra = tok.pasarAminuscQuitarAcentos(word);
    else
        palabra = word;
    
    if(indicePregunta.size() > 0 && indicePregunta.find(palabra) != indicePregunta.end()){
        inf = indicePregunta.find(palabra)->second;
        return true;
    }
    return false;

}

bool
IndexadorHash::DevuelvePregunta(InformacionPregunta& inf) const{
    if(indicePregunta.size() > 0){
        inf = infPregunta;
        return true;
    }
    return false;

}

void
IndexadorHash::ImprimirIndexacionPregunta(){
    cout << "Pregunta indexada: " << pregunta << endl;
    cout << "Terminos indexados en la pregunta: " << endl;
    for(auto par: indicePregunta){
        cout << par.first << "\t" << par.second << endl;
    }
    cout << "Informacion de la pregunta: " << infPregunta << endl;
}

void
IndexadorHash::ImprimirPregunta(){
    cout << "Pregunta indexada: "<< pregunta << endl;
    cout << "Informacion de la pregunta: " << infPregunta << endl;
}

bool
IndexadorHash::Devuelve(const string& word, InformacionTermino& inf) const{
    InformacionTermino res;
    if(indice.find(word) == indice.end()){
        inf = res;
        return false;
    }
        
    inf = indice.find(word)->second;
    
    return true;
}

bool
IndexadorHash::Devuelve(const string& word, const string& nomDoc, InfTermDoc& InfDoc) const{
    auto it = indice.find(word);
    if(it == indice.end())
        return false;
    tok.Tokenizar(nomDoc,false);
    ifstream documento(nomDoc + ".tk");
    if(!documento.is_open())
        return false;
    string palabra;
    bool existe = false;
    int pos = 0;
    while(documento >> palabra){
        
        if(palabra == word){
            existe = true;
            InfDoc.plusFt();
            InfDoc.pushPosTerm(pos);    
        }            
        pos++;
    }
    documento.close();
    return existe;
}

bool
IndexadorHash::Existe(const string& word) const{
    return indice.find(word) != indice.end();
}

bool
IndexadorHash::BorraDoc(const string& nomDoc){
    if(indiceDocs.find(nomDoc) == indiceDocs.end())
        return false;
    vector<string> terminosAEliminar;
    InfDoc infoDoc = indiceDocs[nomDoc];
    
    for(auto& par : indice){
        InformacionTermino *termino = &par.second;    
        termino->minusFtc(termino->getFtById(infoDoc.getIdDoc()));
        
        termino->eraseDocById(infoDoc.getIdDoc());
        if(termino->getDoc().empty())
            terminosAEliminar.push_back(par.first);
        
    }
    
    for(const auto& termino: terminosAEliminar)
        indice.erase(termino);
    informacionColeccionDocs.minusNumDoc();
    informacionColeccionDocs.minusNumTotalPal(infoDoc.getNumPal());
    informacionColeccionDocs.minusNumTotalPalSinParada(infoDoc.getNumPalSinParada());    
    informacionColeccionDocs.minusNumTotalPalDiferentes(terminosAEliminar.size());
    informacionColeccionDocs.minusTamBytes(infoDoc.getTamBytes());
    indiceDocs.erase(nomDoc);
    return true;
}

void
IndexadorHash::VaciarIndiceDocs(){
    indice.clear();
    indiceDocs.clear();
}

void
IndexadorHash::VaciarIndicePreg(){
    indicePregunta.clear();
}

int
IndexadorHash::NumPalIndexadas() const{
    return indice.size();
}

int 
IndexadorHash::NumDocIndexados() const{
    return indiceDocs.size();
}

string
IndexadorHash::DevolverFichPalParada () const{
    return ficheroStopWords;
}

void
IndexadorHash::ListarPalParada() const{
    for(auto stopWord: stopWords){
        cout << stopWord << endl;
    }
}

int
IndexadorHash::NumPalParada() const{
    return stopWords.size();
}

string
IndexadorHash::DevolverDelimitadores () const{
    if((*this).tok.DelimitadoresPalabra().find(" ") == 0)
        return (*this).tok.DelimitadoresPalabra().substr(1,tok.DelimitadoresPalabra().length()-1);
    else
        return (*this).tok.DelimitadoresPalabra();
}

bool
IndexadorHash::DevolverCasosEspeciales () const{
    return (*this).tok.CasosEspeciales();
}

bool
IndexadorHash::DevolverPasarAminuscSinAcentos () const{
    return (*this).tok.PasarAminuscSinAcentos();
}

bool
IndexadorHash::DevolverAlmacenarPosTerm () const{
    return (*this).almacenarPosTerm;
}

string
IndexadorHash::DevolverDirIndice () const{
    return (*this).directorioIndice;
}

int
IndexadorHash::DevolverTipoStemming () const{
    return (*this).tipoStemmer;
}

bool
IndexadorHash::DevolverAlmEnDisco () const{
    return (*this).almacenarEnDisco;
}

void
IndexadorHash::ListarInfColeccDocs() const{
    cout << (*this).informacionColeccionDocs << endl;
}

void
IndexadorHash::ListarTerminos() const{
    for(auto elemento : this->indice){
        cout << elemento.first << "\t" << elemento.second << endl;
    }
}
    
bool IndexadorHash::ListarTerminos(const string& nomDoc) const {

}

void
IndexadorHash::ListarDocs() const{
    for(auto elemento: this->indiceDocs){
        cout << elemento.first << "\t" << elemento.second << endl;
    }
}

bool
IndexadorHash::ListarDocs(const string& nomDoc) const{
    
    for(auto elemento: this->indiceDocs){
        if(elemento.first == nomDoc){
            cout << elemento.first << "\t" << elemento.second << endl;            
            return true;
        }
            
    }
    return false;
}

ostream& 
operator<<(ostream& os, const IndexadorHash& ih){
    os << "Fichero con el listado de palabras de parada: " << ih.ficheroStopWords << endl;
    os << "Tokenizador: " << ih.tok << endl;
    os << "Directorio donde se almacenara el indice generado: " << ih.directorioIndice << endl;
    os << "Stemmer utilizado: " << ih.tipoStemmer << endl;
    os << "Informacion de la coleccion indexada: " << ih.informacionColeccionDocs << endl;
    os << "Se almacenara parte del indice en disco duro: " << ih.almacenarEnDisco << endl;
    os << "Se almacenaran las posiciones de los terminos: " << ih.almacenarPosTerm<<endl;

    return os;
}

IndexadorHash::IndexadorHash():indice(),indiceDocs(),informacionColeccionDocs(),indicePregunta(),infPregunta(),stopWords(),ficheroStopWords(),tok(),directorioIndice(),tipoStemmer(){

}

string
IndexadorHash::indiceToXML(){
    string xml;
    xml = "<indice>\n";
    for(pair<string,InformacionTermino> par : indice){
        xml += "<termino>\n" + par.first + "\n</termino>\n";
        xml += par.second.toXML();
    }
    xml += "</indice>\n";
    return xml;
}

string
IndexadorHash::indiceDocsToXML(){
    string xml;
    xml = "<indiceDocs>\n";
    for(pair<string,InfDoc> par : indiceDocs){
        xml += "<documento>\n" + par.first + "\n</documento>\n";
        xml += par.second.toXML();
    }
    xml += "</indiceDocs>\n";
    return xml;
}

string
IndexadorHash::indicePreguntaToXML(){
    string xml;
    xml = "<indicePregunta>\n";
    for(pair<string,InformacionTerminoPregunta> par : indicePregunta){
        xml += "<termino>\n" + par.first + "\n</termino>\n";
        xml += par.second.toXML();
    }
    xml += "</indicePregunta>\n";
    return xml;
}

string 
IndexadorHash::stopWordsToXML(){
    string xml;
    xml = "<stopWords>\n";
    for(string stopWord: stopWords){
        xml += stopWord + "\n";
    }
    xml += "</stopWords>\n";
    return xml;
}

string 
IndexadorHash::toXML(){
    string xml;
    xml = "<IndexadorHash>\n";
    if(!indice.empty())
        xml += indiceToXML();
    if(!indiceDocs.empty())
        xml += indiceDocsToXML();
    xml += informacionColeccionDocs.toXML();
    xml += "<pregunta>\n" + pregunta + "\n</pregunta>\n";
    if(!indicePregunta.empty())
        xml += indicePreguntaToXML();
    xml += infPregunta.toXML();
    if(!stopWords.empty())
        xml += stopWordsToXML();
    xml += "<ficheroStopWords>\n" + ficheroStopWords + "\n</ficheroStopWords>\n";
    xml += tok.toXML();
    xml += "<directorioIndice>\n" + directorioIndice + "\n</directorioIndice>\n";
    xml += "<tipoStemmer>\n" + to_string(tipoStemmer) + "\n</tipoStemmer>\n";
    xml += "<almacenarEnDisco>\n" + to_string(almacenarEnDisco) + "\n</almacenarEnDisco>\n";
    xml += "<almacenarPosTerm>\n" + to_string(almacenarPosTerm) + "\n</almacenarPosTerm>\n";
   
    xml += "</IndexadorHash>\n";

    return xml;
}