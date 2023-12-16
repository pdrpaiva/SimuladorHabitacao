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
    int idZona;
    static int nextIdZona;
    int linhaZona;
    int colunaZona;
    vector<Sensor*> sensores;
    vector<ProcessadorRegras*> processadores;
    vector<Aparelho*> aparelhos;
public:
    Zona(int linha, int coluna);
    ~Zona();
    int getIdZona() const;
    void setIdZona(int idZona);
    int getLinhaZona() const;
    int getColunaZona() const;
};


#endif //TRABALHO_ZONA_H
