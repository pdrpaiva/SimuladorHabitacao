//
// Created by Utilizador on 16/12/2023.
//

#ifndef TRABALHO_GESTORHABITACAO_H
#define TRABALHO_GESTORHABITACAO_H


#include "Habitacao.h"

class GestorHabitacao {
private:
    Habitacao* habitacao;
public:
    GestorHabitacao();
    ~GestorHabitacao();
    void criaHabitacao(const int& nLinhas, const int& nColunas);
    Habitacao *getHabitacao() const;
};

#endif //TRABALHO_GESTORHABITACAO_H
