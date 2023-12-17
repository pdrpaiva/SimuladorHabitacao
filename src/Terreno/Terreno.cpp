//
// Created by Utilizador on 16/12/2023.
//

#include "Terreno.h"

Terreno::Terreno() {
    habitacao = nullptr;
}

void Terreno::criaHabitacao(const int &nLinhas, const int &nColunas) {
    habitacao = new Habitacao(nLinhas, nColunas);
}

Terreno::~Terreno() {
    delete habitacao;
}

Habitacao *Terreno::getHabitacao() const {
    return habitacao;
}
