//
// Created by ppedr on 28/12/2023.
//

#ifndef TRABALHO_FORAREGRA_H
#define TRABALHO_FORAREGRA_H
#include "Regra.h"

class ForaRegra : public Regra{
private:
    int valorX;
    int valorY;

public:
    ForaRegra(const string& nome, Sensor* sensor,const int& x,const int& y);
    ~ForaRegra() = default;
    bool avaliar() override;
    int getValorX() const override;
    int getValorY() const override;
    Regra * duplica() const override;
};


#endif //TRABALHO_FORAREGRA_H
