//
// Created by Utilizador on 27/10/2023.
//

#include "Sensor.h"

int Sensor::nextIdSensor = 1;

Sensor::Sensor(const string& tipo) : idSensor(nextIdSensor++), tipo(tipo){
}

int Sensor::getIdSensor() const {
    return idSensor;
}

const string &Sensor::getTipo() const {
    return tipo;
}
