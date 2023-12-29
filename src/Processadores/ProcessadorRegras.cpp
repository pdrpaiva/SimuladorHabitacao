//
// Created by Utilizador on 27/10/2023.
//

#include "ProcessadorRegras.h"
#include "../Zonas/Zona.h"
#include "IgualRegra.h"
#include "MenorRegra.h"
#include "MaiorRegra.h"
#include "ForaRegra.h"
#include "EntreRegra.h"

int ProcessadorRegras::nextIdProcessador = 1;

ProcessadorRegras::ProcessadorRegras(Zona* zona, const string &comando) : zona(zona){
    string idString = to_string(nextIdProcessador++);
    idProcessador = 'p' + idString;
    if (comando == "desliga"){
        this->comando = "Desliga";
    }
    else{
        this->comando = "Liga";
    }
}

bool ProcessadorRegras::adicionaRegra(const string &regra, Sensor* sensor, const int &x) {
    if (regra == "igual_a")
        regras.push_back(new IgualRegra(regra,sensor,x));
    else if (regra == "menor_que")
        regras.push_back(new MenorRegra(regra,sensor,x));
    else if (regra == "maior_que")
        regras.push_back(new MaiorRegra(regra,sensor,x));
    else
        return false;

    lePropriedade(sensor);

    return true;
}

bool ProcessadorRegras::adicionaRegra(const string &regra, Sensor* sensor, const int &x, const int &y) {
    if (regra == "entre")
        regras.push_back(new EntreRegra(regra,sensor,x,y));
    else if (regra == "fora")
        regras.push_back(new ForaRegra(regra,sensor,x,y));
    else
        return false;

    lePropriedade(sensor);

    return true;
}

void ProcessadorRegras::lePropriedade(Sensor *sensor) {
    for (auto & propriedade : zona->getPropriedades()) {
        if (sensor->getTipo() == propriedade.first->getNome()){
            sensor->setValor(propriedade.second);
            return;
        }
    }
}


const string &ProcessadorRegras::getIdProcessador() const {
    return idProcessador;
}

const string &ProcessadorRegras::getComando() const {
    return comando;
}

const vector<Regra *> &ProcessadorRegras::getRegras() const {
    return regras;
}

int ProcessadorRegras::getNumRegras() const {
    return regras.size();
}

void ProcessadorRegras::setComando(const string &comando) {
    if (comando == "desliga"){
        this->comando = "Desliga";
    }
    else{
        this->comando = "Liga";
    }
}

int ProcessadorRegras::RemoveRegra(const string &idRegra) {
    //return 1 - válido
    //return 2 - nao ha regras
    //return 3 - nao existe nenhuma regra com esse id

    if (regras.empty())
        return 2;

    for (auto it = regras.begin(); it != regras.end(); ++it) {
        if ((*it)->getIdRegra() == idRegra) {
            delete *it;
            regras.erase(it);
            return 1;
        }
    }

    return 3;
}