//
// Created by Utilizador on 27/10/2023.
//

#include "Zona.h"

int Zona::nextIdZona = 1;

Zona::Zona(int linha, int coluna) : linhaZona(linha),colunaZona(coluna){
    idZona = nextIdZona++;
}

Zona::~Zona() {
    for (auto sensor : sensores) {
        delete sensor;
    }
    for (auto processador : processadores) {
        delete processador;
    }
    for (auto aparelho : aparelhos) {
        delete aparelho;
    }
}

int Zona::getIdZona() const {
    return idZona;
}

void Zona::setIdZona(int idZona) {
    Zona::idZona = idZona;
}

int Zona::getLinhaZona() const {
    return linhaZona;
}

int Zona::getColunaZona() const {
    return colunaZona;
}

void Zona::resetNextIdZona() const {
    nextIdZona = 1;
}
