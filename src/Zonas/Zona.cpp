//
// Created by Utilizador on 27/10/2023.
//

#include "Zona.h"
#include "../Sensores/Sensor.h"
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


using namespace std;

int Zona::nextIdZona = 1;

Zona::Zona(int linha, int coluna) : linhaZona(linha),colunaZona(coluna){
    idZona = nextIdZona++;
    //nextPosAp = 1;
    //NextPosS = 1;
    propriedades[new Temperatura] = 0;
    propriedades[new Humidade] = 0;
    propriedades[new Luz] = 0;
    propriedades[new Fumo] = 0;
    propriedades[new Som] = 0;
    propriedades[new Vibracao] = 0;
    propriedades[new Radiacao] = 0;
}

Zona::~Zona() {
    for (auto sensor : sensores) {
        delete sensor;
    }
    for (auto processador : processadores) {
        delete processador;
    }
    for (auto aparelho : aparelhos) {
        delete aparelho;
    }

    for (auto& propriedade : propriedades) {
        delete propriedade.first;
    }

    propriedades.clear();
}

bool Zona::adicionaSensor(char tipo) {
    switch (tipo) {
        case 't':
            sensores.push_back(new TemperaturaSensor());
            break;
        case 'v':
            sensores.push_back(new MovimentoSensor());
            break;
        case 'm':
            sensores.push_back(new LuminosidadeSensor());
            break;
        case 'd':
            sensores.push_back(new RadiacaoSensor());
            break;
        case 'h':
            sensores.push_back(new HumidadeSensor());
            break;
        case 'o':
            sensores.push_back(new SomSensor());
            break;
        case 'f':
            sensores.push_back(new FumoSensor());
            break;
        default:
            // Tipo desconhecido
            return false;
    }
    return true;
}

bool Zona::adicionaAparelho(char tipo) {
    switch (tipo) {
        case 'a':
            aparelhos.push_back(new AquecedorAparelho());
            break;
        case 's':
            aparelhos.push_back(new AspersorAparelho());
            break;
        case 'r':
            aparelhos.push_back(new RefrigeradorAparelho());
            break;
        case 'l':
            aparelhos.push_back(new LampadaAparelho());
            break;
        default:
            // Tipo desconhecido
            return false;
    }
    return true;
}

int Zona::removeComp(char tipo, string idComp) {
    //return 1 - válido
    //return 2 - nao ha sensores/aparelhos/processadores
    //return 3 - nao existe nenhum sensor/aparelho/processador com esse id

    //penso q este funcao de para simplificar, mas nao estava a conseguir

    if(tipo == 's'){
        if (sensores.empty())
            return 2;

        for (auto it = sensores.begin(); it != sensores.end(); ++it) {
            if ((*it)->getIdSensor() == idComp) {
                delete *it;
                sensores.erase(it);
                return 1;
            }
        }

        return 3;
    }
    else if(tipo == 'a'){
        if (aparelhos.empty())
            return 2;

        for (auto it = aparelhos.begin(); it != aparelhos.end(); ++it) {
            if ((*it)->getIdAparelho() == idComp) {
                delete *it;
                aparelhos.erase(it);
                return 1;
            }
        }

        return 3;
    }
}

Propriedade *Zona::getPropriedade(std::string nome) {
    for (auto & propriedade : propriedades) {
        if (propriedade.first->getNome() == nome)
            return propriedade.first;
    }
    return nullptr;
}

int Zona::alteraPropriedade(const string& nome, int valor) {
    //return 1 - valido
    //return 2 - o valor nao esta no intervalo permitido
    //return 3 - nao encontrou o nome

    for (auto & propriedade : propriedades) {
        if (propriedade.first->getNome() == nome) {
            if(valor >= propriedade.first->getMin()){
                if(valor <= propriedade.first->getMax() || propriedade.first->getMax() == NULL){
                    propriedade.second = valor;
                    return 1;
                }
                else {
                    return 2;
                }
            }
            else {
                return 2;
            }
        }
    }
    return 3;
}

//Getters e Setters

int Zona::getIdZona() const {
    return idZona;
}

int Zona::getLinhaZona() const {
    return linhaZona;
}

int Zona::getColunaZona() const {
    return colunaZona;
}

int Zona::getNumSensores() const {
    return sensores.size();
}

int Zona::getNumProcessadores() const {
    return processadores.size();
}

int Zona::getNumAparelhos() const {
    return aparelhos.size();
}

const vector<Sensor *> &Zona::getSensores() const {
    return sensores;
}

const vector<ProcessadorRegras *> &Zona::getProcessadores() const {
    return processadores;
}

const vector<Aparelho *> &Zona::getAparelhos() const {
    return aparelhos;
}

const map<Propriedade *, int> &Zona::getPropriedades() const {
    return propriedades;
}

void Zona::setPosZona(int pos) {
    posZona = pos;
}

int Zona::getPosZona() const {
    return posZona;
}
/*
int Zona::getNextPosAp() {
    ++nextPosAp;
    return nextPosAp++;
}

int Zona::getNextPosS() {
    ++NextPosS;
    return NextPosS++;
}
*/