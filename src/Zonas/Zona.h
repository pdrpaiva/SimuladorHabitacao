//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_ZONA_H
#define TRABALHO_ZONA_H
#include <vector>
#include <map>
#include <sstream>
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

    bool adicionaSensor(const string& tipo);
    bool adicionaAparelho(const string& tipo);
    bool adicionaProcessador(const string& comando);
    bool restauraProcessador(ProcessadorRegras* proc);

    string removeComp(const string& tipo, const string& idComp);

    const vector<Sensor *> &getSensores() const;
    const vector<ProcessadorRegras *> &getProcessadores() const;
    const vector<Aparelho *> &getAparelhos() const;
    const map<Propriedade *, int> &getPropriedades() const;

    Propriedade* getPropriedade(string nome);
    int alteraPropriedade(const string& nome,int valor);
    int getValorProp(string nome) const;

    ProcessadorRegras* getProcessador(const string& idProc);
    Sensor* getSensor(const string& idSensor);
    Sensor* getSensorByProp(const string& prop);

    Aparelho* getAparelho(const string& idAparelho);

    //Getters e Setters
    int getIdZona() const;
    int getLinhaZona() const;
    int getColunaZona() const;
    int getNumSensores() const;
    int getNumProcessadores() const;
    int getNumAparelhos() const;
    void setPosZona(int pos);
    int getPosZona() const;
    static void setNextIdZona(int nextIdZona);
};


#endif //TRABALHO_ZONA_H
