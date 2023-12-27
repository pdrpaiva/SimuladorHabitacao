//
// Created by Utilizador on 27/10/2023.
//

#include "Aparelho.h"

int Aparelho::nextIdAparelho = 1;

Aparelho::Aparelho(const string& tipo) : ligado(false),tipo(tipo){
    string idString = to_string(nextIdAparelho++);
    idAparelho = 'a' + idString;
}

Aparelho::~Aparelho() {

}

const string &Aparelho::getTipo() const {
    return tipo;
}

bool Aparelho::isLigado() const {
    return ligado;
}

void Aparelho::setLigado() {
    Aparelho::ligado = true;
    Aparelho::idAparelho[0] = toupper(Aparelho::idAparelho[0]);
}

void Aparelho::setDesligado() {
    Aparelho::ligado = false;
    Aparelho::idAparelho[0] = tolower(Aparelho::idAparelho[0]);
}

const string &Aparelho::getIdAparelho() const {
    return idAparelho;
}

