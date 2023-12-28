//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_REGRA_H
#define TRABALHO_REGRA_H

#include "../Sensores/Sensor.h"

class Regra {
private:
    string idRegra;
    static int nextIdRegra;
    Sensor* sensorAssoc;

public:
    Regra(Sensor* sensor);
    virtual ~Regra();
    const string &getIdRegra() const;
    Sensor *getSensorAssoc() const;
};


#endif //TRABALHO_REGRA_H
