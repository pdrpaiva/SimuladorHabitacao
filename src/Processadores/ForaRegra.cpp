//
// Created by ppedr on 28/12/2023.
//

#include "ForaRegra.h"

ForaRegra::ForaRegra(const string& nome, Sensor* sensor,const int &x, const int &y) : Regra(nome,sensor), valorY(y), valorX(x){}

bool ForaRegra::avaliar() {
    if(getSensorAssoc()->getValor() < valorX || getSensorAssoc()->getValor() > valorY)
        return true;

    return false;
}

int ForaRegra::getValorX() const {
    return valorX;
}

int ForaRegra::getValorY() const {
    return valorY;
}

Regra *ForaRegra::duplica() const {
    return new ForaRegra(*this);
}
