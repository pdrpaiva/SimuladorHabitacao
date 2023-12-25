//
// Created by Utilizador on 27/10/2023.
//

#include "FumoSensor.h"

FumoSensor::FumoSensor() : Sensor("Fumo"), fumo(0.0){
}

float FumoSensor::getFumo() const {
    return fumo;
}

void FumoSensor::setFumo(float fumo) {
    FumoSensor::fumo = fumo;
}
