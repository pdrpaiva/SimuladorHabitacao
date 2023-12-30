//
// Created by Utilizador on 25/12/2023.
//

#include "RefrigeradorAparelho.h"
#include "../Zonas/Zona.h"

RefrigeradorAparelho::RefrigeradorAparelho(Zona* zona) : Aparelho(zona,"Refrigerador"){}

RefrigeradorAparelho::~RefrigeradorAparelho() {}

void RefrigeradorAparelho::aoDesligar() {
    getZona()->getPropriedade("Som")->subValor(20);
}

void RefrigeradorAparelho::aoLigar() {
    //ainda temos q pensar
}