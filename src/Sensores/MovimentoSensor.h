//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_MOVIMENTOSENSOR_H
#define TRABALHO_MOVIMENTOSENSOR_H
#include "Sensor.h"

class MovimentoSensor : public Sensor{
private:
    float vibracao; //hertz
public:
    MovimentoSensor(int id);

    float getVibracao() const;

    void setVibracao(float vibracao);
};


#endif //TRABALHO_MOVIMENTOSENSOR_H
