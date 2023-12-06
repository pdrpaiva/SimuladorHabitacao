//
// Created by Utilizador on 27/10/2023.
//

#include "TemperaturaSensor.h"

TemperaturaSensor::TemperaturaSensor(int id) : Sensor(id){}

double TemperaturaSensor::getTemperatura() const {
    return temperatura;
}

void TemperaturaSensor::setTemperatura(float temperatura) {
    TemperaturaSensor::temperatura = temperatura;
}
