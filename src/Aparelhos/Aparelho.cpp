//
// Created by Utilizador on 27/10/2023.
//

#include "Aparelho.h"

int Aparelho::nextIdAparelho = 1;

Aparelho::Aparelho(const string& tipo) : idAparelho(nextIdAparelho++),ligado(false),tipo(tipo){

}

Aparelho::~Aparelho() {

}

const string &Aparelho::getTipo() const {
    return tipo;
}

bool Aparelho::isLigado() const {
    return ligado;
}

void Aparelho::setLigado(bool ligado) {
    Aparelho::ligado = ligado;
}

int Aparelho::getIdAparelho() const {
    return idAparelho;
}
