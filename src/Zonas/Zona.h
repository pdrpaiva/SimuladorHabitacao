//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_ZONA_H
#define TRABALHO_ZONA_H
#include <vector>
#include "../Sensores/Sensor.h"
#include "../Aparelhos/Aparelho.h"
#include "../Processadores/ProcessadorRegras.h"
#include "../Propriedades/Propriedade.h"
#include "../Propriedades/Temperatura.h"
#include "../Propriedades/Humidade.h"
#include "../Propriedades/Luz.h"
#include "../Propriedades/Fumo.h"
#include "../Propriedades/Som.h"
#include "../Propriedades/Vibracao.h"
#include "../Propriedades/Radiacao.h"

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
    vector<Propriedade*> propriedades;
public:
    Zona(int linha, int coluna);
    ~Zona();
    int getIdZona() const;
    int getLinhaZona() const;
    int getColunaZona() const;
    void resetNextIdZona() const;
    int getNumSensores() const;
    int getNumProcessadores() const;
    int getNumAparelhos() const;
};


#endif //TRABALHO_ZONA_H
