//
// Created by ppedr on 28/12/2023.
//

#ifndef TRABALHO_MENORREGRA_H
#define TRABALHO_MENORREGRA_H
#include "Regra.h"

class MenorRegra : public Regra{
private:
    int valorX;

public:
    MenorRegra(Sensor* sensor,const int& x);
    ~MenorRegra();
};


#endif //TRABALHO_MENORREGRA_H
