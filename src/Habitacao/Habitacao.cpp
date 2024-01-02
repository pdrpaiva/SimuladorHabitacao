//
// Created by Utilizador on 27/10/2023.
//

#include "Habitacao.h"

Habitacao::Habitacao(int nLinhas, int nColunas) :  habLinhas(nLinhas), habColunas(nColunas), instancia(0){
    zonas[0]->setNextIdZona(1);
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
        return 1;
    }
    else {
        return 2;
    }
}

int Habitacao::removeZona(int idZona) {
    //return 1 - válido
    //return 2 - a habitacao nao tem zonas inicializadas
    //return 3 - nao existe nenhuma zona com esse id

    if (zonas.empty())
        return 2;

    for (auto it = zonas.begin(); it != zonas.end(); ++it) {
        if ((*it)->getIdZona() == idZona) {
            delete *it;
            zonas.erase(it);
            return 1;
        }
    }

    return 3;
}

bool Habitacao::guardaProc(const string &nomeSave, ProcessadorRegras* proc) {
    procGuardados.insert(make_pair(nomeSave,new ProcessadorRegras(*proc)));
    return true;
}

int Habitacao::apagaCopiaProc(const string &nomeSave) {
    //return 1 - apagado
    //return 2 - nao ha processadores guardados
    //return 3 - nao existe nenhum processador guardado com esse nome

    if(getProcGuardados().empty())
        return 2;

    if(getProcGuardado(nomeSave) == nullptr)
        return 3;

    auto it = procGuardados.find(nomeSave);
    if (it != procGuardados.end()) {
        delete it->second;
        procGuardados.erase(it);
        return 1;
    }

    return 3;
}


ProcessadorRegras *Habitacao::getProcGuardado(const string &nome) {
    for (auto & proc : procGuardados) {
        if (proc.first == nome)
            return proc.second;
    }
    return nullptr;
}


const vector<Zona *> &Habitacao::getZonas() const {
    return zonas;
}

int Habitacao::getInstancia() const {
    return instancia;
}

void Habitacao::setInstancia(int instancia) {
    Habitacao::instancia = instancia;
}

int Habitacao::getHabLinhas() const {
    return habLinhas;
}

int Habitacao::getHabColunas() const {
    return habColunas;
}

Zona* Habitacao::getZona(int idZona) {
    for (auto zona : zonas) {
        if (zona->getIdZona() == idZona)
            return zona;
    }
    return nullptr;
}

const map<string, ProcessadorRegras *> &Habitacao::getProcGuardados() const {
    return procGuardados;
}