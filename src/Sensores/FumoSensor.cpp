//
// Created by Utilizador on 27/10/2023.
//

#include "FumoSensor.h"

FumoSensor::FumoSensor(int id) : Sensor(id){}

float FumoSensor::getFumo() const {
    return fumo;
}

void FumoSensor::setFumo(float fumo) {
    FumoSensor::fumo = fumo;
}
