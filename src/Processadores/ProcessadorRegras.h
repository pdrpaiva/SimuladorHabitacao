//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_PROCESSADORREGRAS_H
#define TRABALHO_PROCESSADORREGRAS_H

#include <vector>
#include <string>
#include "../Processadores/Regra.h"
#include "../Aparelhos/Aparelho.h"

using namespace std;
class Zona;

class ProcessadorRegras {
private:
    string idProcessador;
    static int nextIdProcessador;
    string comando;
    bool ligado;
    //Zona* zona;
    vector<Regra*> regras;
    vector<Aparelho*> aparelhosAssoc;
public:
    ProcessadorRegras(const int& idZona, const string& comando);

    bool adicionaRegra(const string& regra, Sensor* sensor, const int& x);
    bool adicionaRegra(const string& regra, Sensor* sensor, const int& x, const int& y);

    const string &getIdProcessador() const;
    const string &getComando() const;
    const vector<Regra *> &getRegras() const;
    int getNumRegras() const;
    void setComando(const string &comando);
};


#endif // TRABALHO_PROCESSADORREGRAS_H
