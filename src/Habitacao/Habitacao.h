//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_HABITACAO_H
#define TRABALHO_HABITACAO_H
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../../lib/Terminal.h"
#include "../Zonas/Zona.h"
using namespace std;
using namespace term;

class Habitacao {
private:
    vector<Zona*> zonas;
    int habLinhas;
    int habColunas;

    int instancia = 1;

    map<string, ProcessadorRegras*> procGuardados;
public:
    Habitacao(int nLinhas, int nColunas);
    ~Habitacao();

    int adicionaZona(int linha, int coluna);
    int removeZona(int idZona);
    bool guardaProc(const string& nomeSave, ProcessadorRegras* proc);
    int apagaCopiaProc(const string& nomeSave);
    ProcessadorRegras* getProcGuardado(const string& nome);

    const vector<Zona *> &getZonas() const;
    Zona* getZona(int idZona);

    //getters e setteers
    int getInstancia() const;
    void setInstancia(int instancia);
    int getHabLinhas() const;
    int getHabColunas() const;
    const map<string, ProcessadorRegras *> &getProcGuardados() const;
};


#endif //TRABALHO_HABITACAO_H
