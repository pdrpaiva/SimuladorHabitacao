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

    const string &getIdProcessador() const;
    const string &getComando() const;
};


#endif // TRABALHO_PROCESSADORREGRAS_H
