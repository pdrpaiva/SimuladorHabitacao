//
// Created by Utilizador on 27/10/2023.
//

#include "MovimentoSensor.h"

MovimentoSensor::MovimentoSensor(int id) : Sensor(id){}

float MovimentoSensor::getVibracao() const {
    return vibracao;
}

void MovimentoSensor::setVibracao(float vibracao) {
    MovimentoSensor::vibracao = vibracao;
}
