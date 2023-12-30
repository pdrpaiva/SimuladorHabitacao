//
// Created by Utilizador on 25/12/2023.
//

#include "AquecedorAparelho.h"
#include "../Zonas/Zona.h"

AquecedorAparelho::AquecedorAparelho(Zona* zona) : Aparelho(zona,"Aquecedor"){}

AquecedorAparelho::~AquecedorAparelho() {}

void AquecedorAparelho::aoDesligar() {
    getZona()->alteraPropriedade("Som",getZona()->getValorProp("Som")-5);
}

void AquecedorAparelho::aoLigar() {
    //ainda temos q pensar
}




