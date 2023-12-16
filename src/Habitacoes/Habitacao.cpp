//
// Created by Utilizador on 27/10/2023.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "../../lib/Terminal.h"
#include "../Interface/Interface.h"
#include "Habitacao.h"
using namespace std;
using namespace term;

Habitacao::Habitacao(int nLinhas, int nColunas) :  habLinhas(nLinhas), habColunas(nColunas){

}

Habitacao::~Habitacao() {
    for (auto zona : zonas) {
        delete zona;
    }
}

int Habitacao::adicionaZona(int linha, int coluna) {
    //return 1 - valido
    //return 2 - zona fora da habitacao
    //return 3 - ja existe uma zona nessa posicao

    if(linha <= habLinhas && coluna <= habColunas){
        for(int i = 0; i < zonas.size(); i++){
            if(zonas[i]->getLinhaZona() == linha && zonas[i]->getColunaZona() == coluna){
                return 3;
            }
        }
        zonas.push_back(new Zona(linha,coluna));
        nZonas++;
        return 1;
    }
    else {
        return 2;
    }
}

const vector<Zona *> &Habitacao::getZonas() const {
    return zonas;
}

int Habitacao::getNZonas() const {
    return nZonas;
}
