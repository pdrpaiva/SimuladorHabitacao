//
// Created by Utilizador on 27/10/2023.
//

#include "LuminosidadeSensor.h"

LuminosidadeSensor::LuminosidadeSensor(int id) : Sensor(id){}

float LuminosidadeSensor::getLuz() const {
    return luz;
}

void LuminosidadeSensor::setLuz(float luz) {
    LuminosidadeSensor::luz = luz;
}
