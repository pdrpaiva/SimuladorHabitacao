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
    EntreRegra(const string& nome, Sensor* sensor,const int& x,const int& y);
    ~EntreRegra() = default;
    bool avaliar() override;
};

#endif //TRABALHO_ENTREREGRA_H
