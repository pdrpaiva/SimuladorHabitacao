//
// Created by Utilizador on 27/10/2023.
//

#include "LuminosidadeSensor.h"

LuminosidadeSensor::LuminosidadeSensor() : Sensor("Luminosidade"){}

float LuminosidadeSensor::getLuz() const {
    return luz;
}

void LuminosidadeSensor::setLuz(float luz) {
    LuminosidadeSensor::luz = luz;
}
