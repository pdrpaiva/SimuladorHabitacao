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
