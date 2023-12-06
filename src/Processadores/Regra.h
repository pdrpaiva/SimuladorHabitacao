//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_REGRA_H
#define TRABALHO_REGRA_H

#include "../Sensores/Sensor.h"


class Regra {
public:
    Regra(float x, float y);

private:
    int id;
    static int cont;
    float x, y;
    Sensor *sensorcontrol;
};


#endif //TRABALHO_REGRA_H
