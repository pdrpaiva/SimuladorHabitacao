//
// Created by Utilizador on 27/10/2023.
//

#include "Zona.h"

int Zona::nextIdZona = 1;

Zona::Zona(int linha, int coluna) : linhaZona(linha),colunaZona(coluna){
    idZona = nextIdZona++;
    propriedades.push_back(new Temperatura());
    propriedades.push_back(new Humidade());
    propriedades.push_back(new Luz());
    propriedades.push_back(new Fumo());
    propriedades.push_back(new Som());
    propriedades.push_back(new Vibracao());
    propriedades.push_back(new Radiacao());
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
    for (auto propriedade : propriedades) {
        delete propriedade;
    }
}

int Zona::getIdZona() const {
    return idZona;
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

int Zona::getNumSensores() const {
    return sensores.size();
}

int Zona::getNumProcessadores() const {
    return processadores.size();
}

int Zona::getNumAparelhos() const {
    return aparelhos.size();
}
