//
// Created by Utilizador on 27/10/2023.
//

#include "SomSensor.h"

SomSensor::SomSensor(int id) : Sensor(id){}

float SomSensor::getSom() const {
    return som;
}

void SomSensor::setSom(float som) {
    SomSensor::som = som;
}
