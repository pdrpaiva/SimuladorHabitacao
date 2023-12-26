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
    propriedades.push_back(new Temperatura());
    propriedades.push_back(new Humidade());
    propriedades.push_back(new Luz());
    propriedades.push_back(new Fumo());
    propriedades.push_back(new Som());
    propriedades.push_back(new Vibracao());
    propriedades.push_back(new Radiacao());
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
    for (auto propriedade : propriedades) {
        delete propriedade;
    }
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

int Zona::removeComp(char tipo, int idComp) {
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
        if (sensores.empty())
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
    for (auto propriedade : propriedades) {
        if (propriedade->getNome() == nome)
            return propriedade;
    }
    return nullptr;
}

int Zona::alteraPropriedade(const string& nome, int valor) {
    //return 1 - valido
    //return 2 - o valor nao esta no intervalo permitido
    //return 3 - nao encontrou o nome

    for (auto & propriedade : propriedades) {
        if (propriedade->getNome() == nome) {
            if(valor >= propriedade->getMin()){
                if(valor <= propriedade->getMax() || propriedade->getMax() == NULL){
                    propriedade->setValor(valor);
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

const vector<Propriedade *> &Zona::getPropriedades() const {
    return propriedades;
}
