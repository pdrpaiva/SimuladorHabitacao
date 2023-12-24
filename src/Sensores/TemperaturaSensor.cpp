//
// Created by Utilizador on 27/10/2023.
//

#include "TemperaturaSensor.h"

TemperaturaSensor::TemperaturaSensor() : Sensor(), temperatura(0.0) {}

double TemperaturaSensor::getTemperatura() const {
    return temperatura;
}

void TemperaturaSensor::setTemperatura(float temperatura) {
    TemperaturaSensor::temperatura = temperatura;
}
