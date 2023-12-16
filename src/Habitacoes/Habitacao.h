//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_HABITACAO_H
#define TRABALHO_HABITACAO_H
#include <vector>
#include <iostream>
#include "../../lib/Terminal.h"
#include "../Zonas/Zona.h"

class Habitacao {
private:
    vector<Zona*> zonas;
    int nZonas = 0;
    int habLinhas;
    int habColunas;
public:
    Habitacao(int nLinhas, int nColunas);
    ~Habitacao();
    int adicionaZona(int linha, int coluna);
    const vector<Zona *> &getZonas() const;
    int getNZonas() const;
};


#endif //TRABALHO_HABITACAO_H
