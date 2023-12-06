//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_ZONA_H
#define TRABALHO_ZONA_H
#include <vector>
#include "../Sensores/Sensor.h"
#include "../Aparelhos/Aparelho.h"
#include "../Processadores/ProcessadorRegras.h"

using namespace std;

class Zona {
private:
    vector<Sensor*> sensores;
    vector<ProcessadorRegras*> processadores;
    vector<Aparelho*> aparelhos;
    int id;
public:
    Zona(int id);

    int getID() const;
};


#endif //TRABALHO_ZONA_H
