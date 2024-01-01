//
// Created by Utilizador on 25/12/2023.
//

#include "RefrigeradorAparelho.h"
#include "../Zonas/Zona.h"

RefrigeradorAparelho::RefrigeradorAparelho(Zona* zona) : Aparelho(zona,"Refrigerador"){}

RefrigeradorAparelho::~RefrigeradorAparelho() {}

void RefrigeradorAparelho::aoDesligar() {
    getZona()->alteraPropriedade("Som",getZona()->getValorProp("Som")-20);
}

void RefrigeradorAparelho::aoLigar() {
    
}

void RefrigeradorAparelho::atualiza() {
    incrementaCounterLigado();
    if (getCounterLigado() == 1)
        getZona()->alteraPropriedade("Som",getZona()->getValorProp("Som")+20);
    if(getCounterLigado() % 3 == 0){
        getZona()->alteraPropriedade("Temperatura",getZona()->getValorProp("Temperatura")-1);
    }
}
