//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_HUMIDADESENSOR_H
#define TRABALHO_HUMIDADESENSOR_H
#include "Sensor.h"

class HumidadeSensor : public Sensor {
private:
    float humidade; // %
public:
    HumidadeSensor();
    float getHumidade() const;
    void setHumidade(float humidade);
};


#endif //TRABALHO_HUMIDADESENSOR_H
