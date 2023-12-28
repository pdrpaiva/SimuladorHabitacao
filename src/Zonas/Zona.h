//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_ZONA_H
#define TRABALHO_ZONA_H
#include <vector>
#include <map>
#include "../Sensores/Sensor.h"
#include "../Propriedades/Propriedade.h"
#include "../Propriedades/Temperatura.h"
#include "../Propriedades/Humidade.h"
#include "../Propriedades/Luz.h"
#include "../Propriedades/Fumo.h"
#include "../Propriedades/Som.h"
#include "../Propriedades/Vibracao.h"
#include "../Propriedades/Radiacao.h"
#include "../Sensores/TemperaturaSensor.h"
#include "../Sensores/MovimentoSensor.h"
#include "../Sensores/LuminosidadeSensor.h"
#include "../Sensores/RadiacaoSensor.h"
#include "../Sensores/HumidadeSensor.h"
#include "../Sensores/SomSensor.h"
#include "../Sensores/FumoSensor.h"
#include "../Aparelhos/AspersorAparelho.h"
#include "../Aparelhos/AquecedorAparelho.h"
#include "../Aparelhos/RefrigeradorAparelho.h"
#include "../Aparelhos/LampadaAparelho.h"
#include "../Processadores/ProcessadorRegras.h"

using namespace std;

class Zona {
private:
    int idZona;
    static int nextIdZona;
    //int nextPosAp;
    //int NextPosS;
    int linhaZona;
    int colunaZona;
    int posZona;
    vector<Sensor*> sensores;
    vector<ProcessadorRegras*> processadores;
    vector<Aparelho*> aparelhos;
    map<Propriedade*,int> propriedades;
public:
    Zona(int linha, int coluna);
    ~Zona();

    bool adicionaSensor(char tipo);
    bool adicionaAparelho(char tipo);

    int removeComp(char tipo, string idComp);

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
    void setPosZona(int pos);
    int getPosZona() const;
    //int getNextPosAp();
    //int getNextPosS();
};


#endif //TRABALHO_ZONA_H
