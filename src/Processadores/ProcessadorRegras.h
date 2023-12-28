//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_PROCESSADORREGRAS_H
#define TRABALHO_PROCESSADORREGRAS_H

#include <vector>
#include <string>
#include "../Processadores/Regra.h"
#include "../Aparelhos/Aparelho.h"
#include "../Zonas/Zona.h"

using namespace std;

class ProcessadorRegras {
private:
    string idProcessador;
    static int nextIdProcessador;
    bool ligado;
    Zona* zona;
    vector<Regra*> regras;
    vector<Aparelho*> aparelhosAssoc;
public:
    ProcessadorRegras(const int& idZona, const bool& tipo);
};


#endif //TRABALHO_PROCESSADORREGRAS_H
