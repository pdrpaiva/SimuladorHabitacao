//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_TEMPERATURASENSOR_H
#define TRABALHO_TEMPERATURASENSOR_H
#include "Sensor.h"

class TemperaturaSensor : public Sensor{
public:
    TemperaturaSensor(int valor);
    ~TemperaturaSensor();
};


#endif //TRABALHO_TEMPERATURASENSOR_H
