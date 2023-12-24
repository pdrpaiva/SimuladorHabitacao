//
// Created by Utilizador on 27/10/2023.
//

#include "Sensor.h"

int Sensor::nextIdSensor = 1;

Sensor::Sensor(){
    idSensor = nextIdSensor;
}

int Sensor::getIdSensor() const {
    return idSensor;
}
