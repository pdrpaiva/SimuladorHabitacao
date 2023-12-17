//
// Created by Utilizador on 16/12/2023.
//

#ifndef TRABALHO_TERRENO_H
#define TRABALHO_TERRENO_H
#include "../Habitacao/Habitacao.h"

class Terreno {
private:
    Habitacao* habitacao;
public:
    Terreno();
    ~Terreno();
    void criaHabitacao(const int& nLinhas, const int& nColunas);
    Habitacao *getHabitacao() const;
};

#endif //TRABALHO_TERRENO_H
