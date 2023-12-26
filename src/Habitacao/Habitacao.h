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
public:
    Habitacao(int nLinhas, int nColunas);
    ~Habitacao();

    int adicionaZona(int linha, int coluna);
    int removeZona(int idZona);

    const vector<Zona *> &getZonas() const;
    Zona* getZona(int idZona);

    //getters e setteers
    int getInstancia() const;
    void setInstancia(int instancia);
    int getHabLinhas() const;
    int getHabColunas() const;
};


#endif //TRABALHO_HABITACAO_H
