//
// Created by Utilizador on 27/10/2023.
//

#include "Aparelho.h"
#include "../Zonas/Zona.h"
int Aparelho::nextIdAparelho = 1;

Aparelho::Aparelho(Zona* zona, const string& tipo) : zona(zona),ligado(false),tipo(tipo){
    string idString = to_string(nextIdAparelho++);
    idAparelho = 'a' + idString;
}

Aparelho::~Aparelho() {

}

bool Aparelho::recebeComando(const string &comando) {
    //return true valido
    //return false ja esta ligado/desligado

    if(comando == "liga"){
        if(ligado) return false;
        setLigado();
        aoLigar();
    }
    else if(comando == "desliga"){
        if(!ligado) return false;
        setDesligado();
        aoDesligar();
    }

    return true;
}

const string &Aparelho::getTipo() const {
    return tipo;
}

void Aparelho::setLigado() {
    Aparelho::ligado = true;
    idAparelho[0] = toupper(Aparelho::idAparelho[0]);
}

void Aparelho::setDesligado() {
    Aparelho::ligado = false;
    idAparelho[0] = tolower(Aparelho::idAparelho[0]);
}

const string &Aparelho::getIdAparelho() const {
    return idAparelho;
}

Zona *Aparelho::getZona() const {
    return zona;
}

