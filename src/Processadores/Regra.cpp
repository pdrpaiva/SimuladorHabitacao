//
// Created by Utilizador on 27/10/2023.
//

#include "Regra.h"

int Regra::nextIdRegra = 1;

Regra::Regra(Sensor *sensor) : sensorAssoc(sensor){
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
