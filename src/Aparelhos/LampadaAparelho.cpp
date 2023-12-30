//
// Created by Utilizador on 25/12/2023.
//

#include "LampadaAparelho.h"
#include "../Zonas/Zona.h"

LampadaAparelho::LampadaAparelho(Zona* zona) : Aparelho(zona,"Lampada"){}

LampadaAparelho::~LampadaAparelho() {}

void LampadaAparelho::aoDesligar() {
    getZona()->getPropriedade("Luz")->subValor(900);
}

void LampadaAparelho::aoLigar() {
    //ainda temos q pensar
}
