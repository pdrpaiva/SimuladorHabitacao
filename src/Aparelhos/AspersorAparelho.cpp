//
// Created by Utilizador on 25/12/2023.
//

#include "AspersorAparelho.h"
#include "../Zonas/Zona.h"

AspersorAparelho::AspersorAparelho(Zona* zona) : Aparelho(zona,"Aspersor"){}

AspersorAparelho::~AspersorAparelho() = default;

void AspersorAparelho::aoDesligar() {
    getZona()->getPropriedade("Vibracao")->subValor(100);
}

void AspersorAparelho::aoLigar() {
    //ainda temos q pensar
}
