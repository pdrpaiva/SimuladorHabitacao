//
// Created by ppedr on 28/12/2023.
//

#ifndef TRABALHO_ENTREREGRA_H
#define TRABALHO_ENTREREGRA_H
#include "Regra.h"

class EntreRegra : public Regra{
private:
    int valorX;
    int valorY;

public:
    EntreRegra(Sensor* sensor,const int& x,const int& y);
    ~EntreRegra();
};

#endif //TRABALHO_ENTREREGRA_H
