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
    int habLinhas;
    int habColunas;

    int instancia = 0;
    int iZonas = 0; //ajuda a conseguir o id de cada zona

public:
    Habitacao(int nLinhas, int nColunas);
    ~Habitacao();
    int adicionaZona(int linha, int coluna);
    const vector<Zona *> &getZonas() const;
    int getiZonas() const;
    int getInstancia() const;
    void setInstancia(int instancia);
};


#endif //TRABALHO_HABITACAO_H
