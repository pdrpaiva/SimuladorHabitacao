//
// Created by Utilizador on 27/10/2023.
//

#include "Sensor.h"

int Sensor::nextIdSensor = 1;

Sensor::Sensor(const string& tipo) : tipo(tipo), valor(0.0){
    string idString = to_string(nextIdSensor++);
    idSensor = 's' + idString;
}

Sensor::~Sensor() {}



const string &Sensor::getTipo() const {
    return tipo;
}

const string &Sensor::getIdSensor() const {
    return idSensor;
}

double Sensor::getValor() const {
    return valor;
}