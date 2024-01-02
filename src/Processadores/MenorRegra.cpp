//
// Created by ppedr on 28/12/2023.
//

#include "MenorRegra.h"

MenorRegra::MenorRegra(const string& nome,Sensor* sensor,const int &x) : Regra(nome,sensor), valorX(x){}

bool MenorRegra::avaliar() {
    if(getSensorAssoc()->getValor() < valorX)
        return true;

    return false;
}

int MenorRegra::getValorX() const {
    return valorX;
}

Regra *MenorRegra::duplica() const {
    return new MenorRegra(*this);
}
