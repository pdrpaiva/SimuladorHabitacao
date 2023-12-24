//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_TEMPERATURASENSOR_H
#define TRABALHO_TEMPERATURASENSOR_H
#include "Sensor.h"

class TemperaturaSensor : public Sensor{
private:
    float temperatura; //celsius
public:
    TemperaturaSensor();
    double getTemperatura() const;
    void setTemperatura(float temperatura);
};


#endif //TRABALHO_TEMPERATURASENSOR_H
