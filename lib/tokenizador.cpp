#include "../include/tokenizador.h"

const std::unordered_map<unsigned char,unsigned char> acentosMap = {
        // Á, À, Â, Ã, Ä, Å a 'a'
    {0xC0, 'a'}, {0xC1, 'a'}, {0xC2, 'a'}, {0xC3, 'a'}, {0xC4, 'a'}, {0xC5, 'a'},
    {0xE0, 'a'}, {0xE1, 'a'}, {0xE2, 'a'}, {0xE3, 'a'}, {0xE4, 'a'}, {0xE5, 'a'},
    // Ç a 'c'
    {0xC7, 'c'}, {0xE7, 'c'},
    // É, È, Ê, Ë e 'e'
    {0xC8, 'e'}, {0xC9, 'e'}, {0xCA, 'e'}, {0xCB, 'e'},
    {0xE8, 'e'}, {0xE9, 'e'}, {0xEA, 'e'}, {0xEB, 'e'},
    // Í, Ì, Î, Ï e 'i'
    {0xCC, 'i'}, {0xCD, 'i'}, {0xCE, 'i'}, {0xCF, 'i'},
    {0xEC, 'i'}, {0xED, 'i'}, {0xEE, 'i'}, {0xEF, 'i'},
    // Ó, Ò, Ô, Õ, Ö o 'o'
    {0xD2, 'o'}, {0xD3, 'o'}, {0xD4, 'o'}, {0xD5, 'o'}, {0xD6, 'o'},
    {0xF2, 'o'}, {0xF3, 'o'}, {0xF4, 'o'}, {0xF5, 'o'}, {0xF6, 'o'},
    // Ú, Ù, Û, Ü u 'u'
    {0xD9, 'u'}, {0xDA, 'u'}, {0xDB, 'u'}, {0xDC, 'u'},
    {0xF9, 'u'}, {0xFA, 'u'}, {0xFB, 'u'}, {0xFC, 'u'},
    // Ñ a 'ñ'
    {0xD1, 0xF1}
};

Tokenizador::Tokenizador(const string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos): casosEspeciales(kcasosEspeciales),pasarAminuscSinAcentos(minuscSinAcentos){
    this->delimiters = " " + delimitadoresPalabra;
       
}

Tokenizador::Tokenizador(const Tokenizador& token) : delimiters(token.DelimitadoresPalabra()), casosEspeciales(token.CasosEspeciales()), pasarAminuscSinAcentos(token.PasarAminuscSinAcentos()){ 
}

Tokenizador::Tokenizador(){
    this->delimiters = DELIMITERS;
    this->casosEspeciales = CASOS_ESPECIALES;
    this->pasarAminuscSinAcentos = QUITAR_MAYUS_ACENTOS;
}

Tokenizador::~Tokenizador(){
    this->delimiters = "";
    
}

Tokenizador&
Tokenizador::operator=(const Tokenizador& token){
    if(this != &token){
        this->delimiters = token.DelimitadoresPalabra();
        this->casosEspeciales = token.CasosEspeciales();
        this->pasarAminuscSinAcentos = token.PasarAminuscSinAcentos();
    }
    return *this;
}

// Función que convierte un string a minúsculas
string 
Tokenizador::pasarAminuscQuitarAcentos(const string& str) const{
    std::string result;
    
    // Reservamos el mismo tamaño que el string de entrada para optimizar
    result.reserve(str.size());
    for(unsigned char c : str) {
        // Convertimos el carácter a minúscula primero
        c = std::tolower(c);

        // Reemplazamos los caracteres acentuados por sus equivalentes sin acento
        auto it = acentosMap.find(c);
        if(it != acentosMap.end())
            result += it->second;
        else
            result += c;
        
    }
    return result;
}


void 
Tokenizador::Tokenizar(const string& str, list<string>& tokens,bool vaciarToken) const{
    
    if (vaciarToken && !tokens.empty())
        tokens.clear();
    
    if(casosEspeciales){
        string::size_type lastPos = str.find_first_not_of(delimiters,0);
        string::size_type pos = str.find_first_of(delimiters,lastPos);
        string::size_type newLastPos = lastPos;
        string::size_type posEmailGuion,posEmailBarraBaja,posEmailPunto;
        string subcadena = "";
        bool posibleURL = false;
        bool casoNumeroEspecial = false;
        bool url = true;
        bool numeroDecimal = true;
        bool posibleEmail = false;
        bool posibleGuion = false;
        bool posibleNumero = false;
        bool email = true;
        bool acronimo = true;
        bool guion = true;
        bool posibleAcronimo = false;
        while(string::npos != pos || string::npos != lastPos){            
            
            if(!posibleURL && pos-lastPos >= 3){
                subcadena = str.substr(lastPos,pos-lastPos);            
                if(pasarAminuscSinAcentos){
                    subcadena = pasarAminuscQuitarAcentos(subcadena);
                }                                    
            }
            
                
            // URL
            if(str[pos] == ':' && url){
                subcadena = str.substr(lastPos,pos-lastPos);
                if(pasarAminuscSinAcentos){
                    subcadena = pasarAminuscQuitarAcentos(subcadena);
                }                                    
                
                if (subcadena == "http" || subcadena == "https" || subcadena == "ftp"){
                    newLastPos = pos + 1;
                    pos = str.find_first_of(delimiters,newLastPos);
                    
                    if(string::npos == pos && str[newLastPos-1] == ':'){
                        pos=newLastPos-1;
                       
                        url = false;
                    }
                    else if(!posibleURL)
                        posibleURL = true;  
                }
                else
                    url = false;
                subcadena = "";
                
            }   
            else if((subcadena.find("http:",0) != string::npos && subcadena.find("http:",0) == 0) || (subcadena.find("https:",0) != string::npos && subcadena.find("https:",0) == 0) || (subcadena.find("ftp:",0) != string::npos && subcadena.find("ftp:",0) == 0)){
                subcadena = "";
                if(!posibleURL)
                    posibleURL = true;                
            }
            else if(posibleURL && (str[pos] == '_' || str[pos] == ':' || str[pos] == '/' || str[pos] == '.' || str[pos] == '?' || str[pos] == '&' || str[pos] == '-' || str[pos] == '=' || str[pos] == '#' || str[pos] == '@')){
                newLastPos = pos + 1;                
                pos = str.find_first_of(delimiters,newLastPos);                                
            }
            


            // NUMERO DECIMAL 
            else if((str[pos] == '.' || str[pos] == ',') && numeroDecimal){
                if(isdigit(str[pos+1]) || (isdigit(str[pos+1]) && isdigit(str[pos-1]))){
                    newLastPos = pos+1;
                    pos = str.find_first_of(delimiters,newLastPos);
                    subcadena = str.substr(newLastPos,pos-newLastPos);
                    if(subcadena.find("E+") != -1){
                        pos = newLastPos-1;
                        numeroDecimal = false;
                        
                    }
                    else if(str[pos-1] == '%' || str[pos-1] == '$'){
                        
                        if(str[pos] == ' ')
                            pos--;
                        else{
                            pos = newLastPos - 1;
                            numeroDecimal = false;
                        }
                        
                            
                        
                    }
                }
                else
                    numeroDecimal = false;
            }          
            else if(lastPos > 0 && (str[lastPos-1] == '.' || str[lastPos-1] == ',') && isdigit(str[lastPos]) && numeroDecimal){
                subcadena = str.substr(newLastPos,pos-newLastPos);
                if (subcadena.find("E+") == -1 && subcadena.find("%") == -1 && subcadena.find("$") == -1){
                    casoNumeroEspecial = true;
                    lastPos--;
                    
                }
                else
                    numeroDecimal = false;
                
            }
            // EMAIL
            else if(str[pos] == '@' && pos+1 < str.length() && str[pos+1] != ' ' && email && !posibleGuion && !posibleAcronimo && !posibleNumero){
                newLastPos = pos + 1;  
                pos = str.find(" ",newLastPos);
                subcadena = str.substr(newLastPos,pos-newLastPos);
                posEmailBarraBaja = subcadena.find("_");
                posEmailGuion = subcadena.find("-");
                posEmailPunto = subcadena.find(".");                
                
                if (subcadena.find("@") == -1 && (posEmailPunto != -1 || posEmailBarraBaja != -1 || posEmailGuion != -1)){
                    posibleEmail = true;                      
                    if(subcadena.length() == 1){
                        pos = pos - 2;
                        email = false;
                    }                 
                    else if(posEmailBarraBaja == 0 || posEmailGuion == 0 || posEmailPunto == 0){
                        pos = newLastPos - 1;
                        email = false; 
                    }   
                    else if (posEmailBarraBaja == subcadena.length()-1 || posEmailGuion == subcadena.length()-1 || posEmailPunto == subcadena.length()-1){
                        pos--;
                        email = false;
                    }                                         
                    else if(((subcadena.find_first_of(".",0) == subcadena.find_last_of(".",0)) && (subcadena.find_first_of(".",0) != string::npos)) || ((subcadena.find_first_of("_",0) == subcadena.find_last_of("_",0)) && (subcadena.find_first_of("_",0) != string::npos)) || ((subcadena.find_first_of("-",0) == subcadena.find_last_of("-",0)) && (string::npos != subcadena.find_last_of("-",0)))){
                        continue;
                    }   
                    
                    else{
                        if(subcadena.find_first_of(".",0) != string::npos)
                            pos = str.find_first_of(".",newLastPos);
                        if(subcadena.find_first_of("_",0) != string::npos)
                            pos = str.find_first_of("_",newLastPos);
                        if(subcadena.find_first_of("-",0) != string::npos)
                            pos = str.find_first_of("-",newLastPos);
                        email = false;
                    }
                    
                }
                else if(subcadena.find("@") == -1){
                    continue;   
                }       
                else{
                    pos = newLastPos - 1;
                    email = false;                         
                }
            }

            
            // ACRONIMO
            else if(str[pos] == '.' && acronimo){
                if(isalpha(str[pos+1]) || isalnum(str[pos+1])){
                    newLastPos = pos+1;
                    pos = str.find_first_of(delimiters,newLastPos);
                    posibleAcronimo = true;
                    if(casoNumeroEspecial){
                        casoNumeroEspecial = false;
                        numeroDecimal = false;
                        lastPos++;
                    }
                }
                else
                    acronimo = false;

            }

            // GUION
            else if(str[pos] == '-' && guion){
                if((isalpha(str[pos+1]) && isalpha(str[pos-1])) || (isalnum(str[pos+1] && isalnum(str[pos-1]))) || (isalnum(str[pos+1]) && isalpha(str[pos-1])) || (isalnum(str[pos-1]) && isalpha(str[pos+1]))){
                    newLastPos = pos+1;
                    pos = str.find_first_of(delimiters,newLastPos);
                    posibleGuion = true;
                }
                else
                    guion = false;

            }
            
            else{    
                if (!casoNumeroEspecial){
                    subcadena = str.substr(lastPos,pos-lastPos);
                    
                }
                else
                    subcadena = "0" + str.substr(lastPos,pos-lastPos);
                if(pasarAminuscSinAcentos)
                    subcadena = pasarAminuscQuitarAcentos(subcadena);
                tokens.push_back(subcadena);
                lastPos = str.find_first_not_of(delimiters, pos);
                pos = str.find_first_of(delimiters, lastPos);                       
                posibleURL = false;
                url = true;
                numeroDecimal = true;
                casoNumeroEspecial = false;
                posibleEmail = false;
                email = true;
                acronimo = true;
                guion = true;
                posibleGuion = false;
                posibleAcronimo = false;
                posibleNumero = false;
            }
        }
    }
    else{
        
        string delimitersSinCasos = delimiters;
        size_t posicion = delimitersSinCasos.find(' ');
        if (posicion != std::string::npos) { 
            delimitersSinCasos.erase(posicion, 1);
        }
        string::size_type lastPos = str.find_first_not_of(delimitersSinCasos,0);
        string::size_type pos = str.find_first_of(delimitersSinCasos,lastPos);
        string token;        
        while(string::npos!=pos || string::npos != lastPos){
            token = str.substr(lastPos,pos-lastPos);
            
            if(pasarAminuscSinAcentos)
                token = pasarAminuscQuitarAcentos(token);
            tokens.push_back(token);
            lastPos = str.find_first_not_of(delimitersSinCasos, pos);
            pos = str.find_first_of(delimitersSinCasos, lastPos); 
        }       
    }                   
}

bool 
Tokenizador::Tokenizar(const string& i, const string& f,bool verbose) const{
    ifstream fichLectura;
    ofstream fichSalida;
    list<string> tokens;
    fichLectura.open(i.c_str());
    if(!fichLectura) {
        if(verbose)
            cerr << "ERROR: No existe el archivo: " << i << endl;
        return false;
    }
    else{
        string cadena;
        
        while(!fichLectura.eof()){
            cadena="";
            getline(fichLectura, cadena);
            if(cadena.length()!=0){
                Tokenizar(cadena, tokens,false);
            }
        }
    }
    
    fichLectura.close();
    fichSalida.open(f.c_str());
    list<string>::iterator itS;
    for(itS= tokens.begin();itS!= tokens.end();itS++){
        fichSalida << (*itS) + "\n";
    }

    fichSalida.close();
    
    return true;
}

bool
Tokenizador::Tokenizar(const string& i,bool verbose) const{
    return Tokenizar(i,i + ".tk",verbose);
}

bool 
Tokenizador::TokenizarListaFicheros(const string& i) const{
    ifstream fichLectura;
    fichLectura.open(i.c_str());
    if(!fichLectura.is_open()){
        cerr << "ERROR: no se ha podido abrir el fichero " << i << endl;
        return false;
    }
    else{
        string ficheroEntrada = "";
        while(!fichLectura.eof()){
            getline(fichLectura,ficheroEntrada);
            if(ficheroEntrada.length() != 0){
                if(!Tokenizar(ficheroEntrada)){
                    cerr << "ERROR: no se ha podido tokenizar el fichero " << ficheroEntrada << endl;
                    return false;
                }
//                else
  //                  cout << "Fichero " << ficheroEntrada << " tokenizado correctamente" << endl;
            }
        }
        fichLectura.close();
        return true;
    }
}

bool 
Tokenizador::Tokenizador::TokenizarDirectorio(const string& i) const{
    struct stat dir;
    // Compruebo la existencia del directorio
    int err=stat(i.c_str(), &dir);
    if(err==-1 || !S_ISDIR(dir.st_mode))
        return false;
    else {
        list<string> tokens;
        // Hago una lista en un fichero con find>fich
        string cmd="find "+i+" -follow |sort > .lista_fich";
        system(cmd.c_str());
        return TokenizarListaFicheros(".lista_fich");
    }
}


void 
Tokenizador::DelimitadoresPalabra(const string& nuevoDelimiters){
    this->delimiters = " ";
    for(const char s: nuevoDelimiters)
        AnyadirDelimitadoresPalabra(string(1, s));
}   

void 
Tokenizador::AnyadirDelimitadoresPalabra(const string& nuevoDelimiters){
    if(this->delimiters == "\",;:.-/+*\\ \\\"{}[]()<>¡!¿?&#=\\t\\n\\r@")
        delimiters = "";
    
    if(nuevoDelimiters.length() == 1){
        if ((this->delimiters.find(nuevoDelimiters)) == -1)
            this->delimiters += nuevoDelimiters;
    }
    else{
        for(const char s:nuevoDelimiters){
            string delimiter = string(1,s);
            if ((this->delimiters.find(delimiter)) == -1 || s == ' ')
                this->delimiters += delimiter;       
        }
    }
}

string 
Tokenizador::DelimitadoresPalabra() const{
    return this->delimiters;
}

void 
Tokenizador::CasosEspeciales(const bool& nuevoCasosEspeciales){
    this->casosEspeciales = nuevoCasosEspeciales;
}

bool 
Tokenizador::CasosEspeciales() const{
    return this->casosEspeciales;
}


void 
Tokenizador::PasarAminuscSinAcentos(const bool& nuevoPasarAminuscSinAcentos){
    this->pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

bool 
Tokenizador::PasarAminuscSinAcentos() const{
    return this->pasarAminuscSinAcentos;
}

ostream& 
operator<<(ostream& os, const Tokenizador& token){
    os << "DELIMITADORES:" << token.DelimitadoresPalabra() << " TRATA CASOS ESPECIALES: " << token.CasosEspeciales() << " PASAR A MINUSCULAS Y SIN ACENTOS: " << token.PasarAminuscSinAcentos();
    return os;
}

string
Tokenizador::toXML(){
    string xml;
    xml = "<Tokenizador>\n";
    xml += "<delimitadores>\n" + delimiters.substr(1,delimiters.length()-1) + "\n</delimitadores>\n";
    xml += "<casosEspeciales>\n" + to_string(casosEspeciales) + "\n</casosEspeciales>\n";
    xml += "<pasarAminuscSinAcentos>\n" + to_string(pasarAminuscSinAcentos) + "\n</pasarAminuscSinAcentos>\n";
    xml += "</Tokenizador>\n";

    
    return xml;
}