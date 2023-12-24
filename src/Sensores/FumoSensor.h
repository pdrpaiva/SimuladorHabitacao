//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_FUMOSENSOR_H
#define TRABALHO_FUMOSENSOR_H
#include "Sensor.h"

class FumoSensor : public Sensor{
private:
    float fumo; //%
public:
    FumoSensor();
    float getFumo() const;
    void setFumo(float fumo);
};


#endif //TRABALHO_FUMOSENSOR_H
