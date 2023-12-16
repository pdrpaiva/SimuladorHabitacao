//
// Created by Utilizador on 27/10/2023.
//

#include "Zona.h"

int Zona::nextIdZona = 1;

Zona::Zona(int linha, int coluna) : linhaZona(linha),colunaZona(coluna){
    idZona = nextIdZona++;
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
