//
// Created by ppedr on 28/12/2023.
//

#include "MaiorRegra.h"

MaiorRegra::MaiorRegra(const string& nome,Sensor* sensor,const int &x) : Regra(nome,sensor), valorX(x){}

bool MaiorRegra::avaliar() {
    if(getSensorAssoc()->getValor() > valorX)
        return true;

    return false;
}

int MaiorRegra::getValorX() const {
    return valorX;
}

Regra *MaiorRegra::duplica() const {
    return new MaiorRegra(*this);
}

