//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_ZONA_H
#define TRABALHO_ZONA_H
#include <vector>
#include <map>
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
    map<Propriedade*,int> propriedades;
public:
    Zona(int linha, int coluna);
    ~Zona();

    bool adicionaSensor(char tipo);
    bool adicionaAparelho(char tipo);

    int removeComp(char tipo, int idComp);

    const vector<Sensor *> &getSensores() const;
    const vector<ProcessadorRegras *> &getProcessadores() const;
    const vector<Aparelho *> &getAparelhos() const;
    const map<Propriedade *, int> &getPropriedades() const;

    //Sensor* getSensor(int idSens);
    Propriedade* getPropriedade(string nome);
    int alteraPropriedade(const string& nome,int valor);

    //Getters e Setters
    int getIdZona() const;
    int getLinhaZona() const;
    int getColunaZona() const;
    int getNumSensores() const;
    int getNumProcessadores() const;
    int getNumAparelhos() const;
};


#endif //TRABALHO_ZONA_H
