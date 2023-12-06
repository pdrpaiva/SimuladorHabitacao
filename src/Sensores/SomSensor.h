//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_SOMSENSOR_H
#define TRABALHO_SOMSENSOR_H
#include "Sensor.h"

class SomSensor : public Sensor{
private:
    float som; //decibeis
public:
    SomSensor(int id);

    float getSom() const;

    void setSom(float som);
};


#endif //TRABALHO_SOMSENSOR_H
