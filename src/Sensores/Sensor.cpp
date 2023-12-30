//
// Created by Utilizador on 27/10/2023.
//

#include "Sensor.h"

int Sensor::nextIdSensor = 1;

Sensor::Sensor(const string& tipo, int _valor) : tipo(tipo), valor(_valor){
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

int Sensor::getValor() const {
    return valor;
}

void Sensor::setValor(int valor) {
    Sensor::valor = valor;
}

void Sensor::setNextIdSensor(int nextIdSensor) {
    Sensor::nextIdSensor = nextIdSensor;
}
