//
// Created by Utilizador on 25/12/2023.
//

#include "AquecedorAparelho.h"
#include "../Zonas/Zona.h"

AquecedorAparelho::AquecedorAparelho(Zona* zona) : Aparelho(zona,"Aquecedor"){}

AquecedorAparelho::~AquecedorAparelho() {}

void AquecedorAparelho::aoDesligar() {
    //ostringstream oss;
    getZona()->alteraPropriedade("Som",getZona()->getValorProp("Som")-5);

    //oss << "O aquecedor " << getIdAparelho() << " foi desligado. -5 db";
    //return oss.str();
}

void AquecedorAparelho::aoLigar() {
    getZona()->alteraPropriedade("Som",getZona()->getValorProp("Som")+5);
}

void AquecedorAparelho::atualiza() {
    incrementaCounterLigado();
    if(getZona()->getValorProp("Temperatura") <= 50) {
        if(getCounterLigado() % 3 == 0){
            getZona()->alteraPropriedade("Temperatura",getZona()->getValorProp("Temperatura")+1);
        }
    }
}





