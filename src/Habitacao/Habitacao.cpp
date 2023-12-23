//
// Created by Utilizador on 27/10/2023.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "Habitacao.h"
using namespace std;
using namespace term;

Habitacao::Habitacao(int nLinhas, int nColunas) :  habLinhas(nLinhas), habColunas(nColunas),iZonas(0), instancia(0){

}

Habitacao::~Habitacao() {

    getZonas()[0]->resetNextIdZona(); //opcional

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
        iZonas++;
        return 1;
    }
    else {
        return 2;
    }
}

const vector<Zona *> &Habitacao::getZonas() const {
    return zonas;
}

int Habitacao::getiZonas() const {
    return iZonas;
}

int Habitacao::getInstancia() const {
    return instancia;
}

void Habitacao::setInstancia(int instancia) {
    Habitacao::instancia = instancia;
}

int Habitacao::removeZona(int idZona) {
    //return 1 - valido
    //return 2 - a habitacao nao tem zonas inicializadas
    //return 3 - nao existe nenhuma zona com esse id

    bool existe = false;

    if(zonas.empty())
        return 2;

    for (auto zona : zonas) {
        if(idZona == zona->getIdZona())
            existe = true;
    }

    if(existe){
        //zonas.erase(zonas.begin() + idZona);
        return 1;
    }else{
        return 3;
    }
}

int Habitacao::getHabLinhas() const {
    return habLinhas;
}

int Habitacao::getHabColunas() const {
    return habColunas;
}
