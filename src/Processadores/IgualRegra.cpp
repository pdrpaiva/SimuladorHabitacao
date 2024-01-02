//
// Created by ppedr on 28/12/2023.
//

#include "IgualRegra.h"

IgualRegra::IgualRegra(const string& nome,Sensor* sensor,const int &x) : Regra(nome,sensor), valorX(x){

}

bool IgualRegra::avaliar() {
    if(getSensorAssoc()->getValor() == valorX)
        return true;

    return false;
}

int IgualRegra::getValorX() const {
    return valorX;
}

Regra *IgualRegra::duplica() const {
    return new IgualRegra(*this);
}
