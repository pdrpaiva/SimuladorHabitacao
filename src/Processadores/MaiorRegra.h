//
// Created by ppedr on 28/12/2023.
//

#ifndef TRABALHO_MAIORREGRA_H
#define TRABALHO_MAIORREGRA_H
#include "Regra.h"

class MaiorRegra : public Regra{
private:
    int valorX;

public:
    MaiorRegra(const string& nome, Sensor* sensor,const int& x);
    ~MaiorRegra() = default;
};



#endif //TRABALHO_MAIORREGRA_H
