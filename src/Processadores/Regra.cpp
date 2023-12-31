//
// Created by Utilizador on 27/10/2023.
//

#include "Regra.h"

int Regra::nextIdRegra = 1;

Regra::Regra(const string& nome, Sensor *sensor) : nome(nome), sensorAssoc(sensor){
    string idString = to_string(nextIdRegra++);
    idRegra = 'r' + idString;
}

const string &Regra::getIdRegra() const {
    return idRegra;
}

Sensor *Regra::getSensorAssoc() const {
    return sensorAssoc;
}

Regra::~Regra() {

}

const string &Regra::getNome() const {
    return nome;
}

void Regra::setNextIdRegra(int nextIdRegra) {
    Regra::nextIdRegra = nextIdRegra;
}

int Regra::getValorX() const {
    return 0;
}

int Regra::getValorY() const {
    return 0;
}
