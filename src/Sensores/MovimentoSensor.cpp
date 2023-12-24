//
// Created by Utilizador on 27/10/2023.
//

#include "MovimentoSensor.h"

MovimentoSensor::MovimentoSensor() : Sensor(){}

float MovimentoSensor::getVibracao() const {
    return vibracao;
}

void MovimentoSensor::setVibracao(float vibracao) {
    MovimentoSensor::vibracao = vibracao;
}
