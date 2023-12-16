//
// Created by Utilizador on 16/12/2023.
//

#include "GestorHabitacao.h"

GestorHabitacao::GestorHabitacao() {
    habitacao = nullptr;
}

void GestorHabitacao::criaHabitacao(const int &nLinhas, const int &nColunas) {
    habitacao = new Habitacao(nLinhas, nColunas);
}

GestorHabitacao::~GestorHabitacao() {
    delete habitacao;
}

Habitacao *GestorHabitacao::getHabitacao() const {
    return habitacao;
}
