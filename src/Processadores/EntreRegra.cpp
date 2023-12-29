//
// Created by ppedr on 28/12/2023.
//

#include "EntreRegra.h"

EntreRegra::EntreRegra(const string& nome,Sensor* sensor,const int &x, const int &y) : Regra(nome,sensor), valorX(x),valorY(y){

}

bool EntreRegra::avaliar() {
    if(getSensorAssoc()->getValor() >= valorX && getSensorAssoc()->getValor() <= valorY)
        return true;

    return false;
}
