//
// Created by Utilizador on 27/10/2023.
//

#include "HumidadeSensor.h"

HumidadeSensor::HumidadeSensor(int id) : Sensor(id){}

float HumidadeSensor::getHumidade() const {
    return humidade;
}

void HumidadeSensor::setHumidade(float humidade) {
    HumidadeSensor::humidade = humidade;
}