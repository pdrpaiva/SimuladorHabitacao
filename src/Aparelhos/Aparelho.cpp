//
// Created by Utilizador on 27/10/2023.
//

#include "Aparelho.h"
#include "../Zonas/Zona.h"
int Aparelho::nextIdAparelho = 1;

Aparelho::Aparelho(Zona* zona, const string& tipo) : zona(zona),ligado(false),tipo(tipo),comando("NULL"), counterLigado(0){
    string idString = to_string(nextIdAparelho++);
    idAparelho = 'a' + idString;
}

Aparelho::~Aparelho() {

}

bool Aparelho::recebeComando(const string &comando) {
    //return true valido
    //return false ja esta ligado/desligado

    if(comando == "liga"){
        if(ligado)return false;
        aoLigar();
        setLigado();
    }
    else if(comando == "desliga"){
        if(!ligado) return false;
        aoDesligar();
        setDesligado();
        counterLigado = 0;
    }

    this->comando = comando;

    return true;
}

const string &Aparelho::getTipo() const {
    return tipo;
}

bool Aparelho::isLigado() const {
    return ligado;
}

void Aparelho::setLigado() {
    Aparelho::ligado = true;
    idAparelho[0] = toupper(Aparelho::idAparelho[0]);
}

void Aparelho::setDesligado() {
    Aparelho::ligado = false;
    idAparelho[0] = tolower(Aparelho::idAparelho[0]);
}

int Aparelho::getCounterLigado() const {
    return counterLigado;
}

void Aparelho::incrementaCounterLigado() {
    Aparelho::counterLigado++;
}

void Aparelho::resetCounterLigado() {
    Aparelho::counterLigado = 0;
}

const string &Aparelho::getIdAparelho() const {
    return idAparelho;
}

Zona *Aparelho::getZona() const {
    return zona;
}

const string &Aparelho::getComando() const {
    return comando;
}

void Aparelho::setComando(const string &comando) {
    Aparelho::comando = comando;
}

void Aparelho::setNextIdAparelho(int nextIdAparelho) {
    Aparelho::nextIdAparelho = nextIdAparelho;
}

