//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_LUMINOSIDADESENSOR_H
#define TRABALHO_LUMINOSIDADESENSOR_H
#include "Sensor.h"

class LuminosidadeSensor : public Sensor{
private:
    float luz; //lumens
public:
    LuminosidadeSensor();

    float getLuz() const;

    void setLuz(float luz);
};


#endif //TRABALHO_LUMINOSIDADESENSOR_H
