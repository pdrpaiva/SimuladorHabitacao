//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_RADIACAOSENSOR_H
#define TRABALHO_RADIACAOSENSOR_H
#include "Sensor.h"

class RadiacaoSensor : public Sensor{
private:
    float radiacao; //Becquerel
public:
    RadiacaoSensor(int id);

    float getRadiacao() const;

    void setRadiacao(float radiacao);
};


#endif //TRABALHO_RADIACAOSENSOR_H
