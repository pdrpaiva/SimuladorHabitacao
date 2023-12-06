//
// Created by Utilizador on 27/10/2023.
//

#include "RadiacaoSensor.h"

RadiacaoSensor::RadiacaoSensor(int id) : Sensor(id){}

float RadiacaoSensor::getRadiacao() const {
    return radiacao;
}

void RadiacaoSensor::setRadiacao(float radiacao) {
    RadiacaoSensor::radiacao = radiacao;
}
