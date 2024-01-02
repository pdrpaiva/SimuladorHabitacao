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

ProcessadorRegras::ProcessadorRegras(Zona* zona, const string &comando) : zona(zona),comando(comando){
    string idString = to_string(nextIdProcessador++);
    idProcessador = 'p' + idString;
}

ProcessadorRegras::~ProcessadorRegras() {
    for(Regra* regra : regras){
        delete regra;
    }
}

ProcessadorRegras::ProcessadorRegras(ProcessadorRegras &original) : idProcessador(original.idProcessador), comando(original.comando) , zona(original.zona){
    *this = original;
}

ProcessadorRegras &ProcessadorRegras::operator=(const ProcessadorRegras &original) {
    if(this == &original){
        return *this;
    }

    for( int i = 0 ; i < regras.size() ; i++){
        delete regras[i];
    }
    regras.clear();

    for( int i = 0 ; i < original.regras.size() ; i++){
        regras.push_back(original.regras[i]->duplica());
    }

    return *this;
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

bool ProcessadorRegras::adicionaAparelho(Aparelho *aparelho) {
    for (auto & aparelhoAssoc : aparelhosAssoc) {
        if (aparelhoAssoc->getIdAparelho() == aparelho->getIdAparelho())
            return false;
    }
    aparelhosAssoc.push_back(aparelho);
    return true;
}

bool ProcessadorRegras::removeAparelho(const Aparelho* Aparelho) {
    for (auto it = aparelhosAssoc.begin(); it != aparelhosAssoc.end(); ++it) {
        if ((*it)->getIdAparelho() == Aparelho->getIdAparelho()) {
            aparelhosAssoc.erase(it);
            return true;
        }
    }
    return false;
}


const string &ProcessadorRegras::getIdProcessador() const {
    return idProcessador;
}

const string &ProcessadorRegras::getComando() const {
    return comando;
}

const Regra *ProcessadorRegras::getRegra(const string &idRegra) const {
    for (auto & regra : regras) {
        if (regra->getIdRegra() == idRegra)
            return regra;
    }
    return nullptr;
}

const vector<Regra *> &ProcessadorRegras::getRegras() const {
    return regras;
}

int ProcessadorRegras::getNumRegras() const {
    return regras.size();
}

void ProcessadorRegras::setComando(const string &comando) {
    /*if (comando == "desliga"){
        this->comando = "Desliga";
    }
    else{
        this->comando = "Liga";
    }*/
    this->comando = comando;
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

void ProcessadorRegras::AtivaComando() {
    if (comando == "liga"){
        for (auto & aparelho : aparelhosAssoc) {
            aparelho->recebeComando("liga");
        }
    }
    else{
        for (auto & aparelho : aparelhosAssoc) {
            aparelho->recebeComando("desliga");
        }
    }
}

void ProcessadorRegras::setNextIdProcessador(int nextIdProcessador) {
    ProcessadorRegras::nextIdProcessador = nextIdProcessador;
}

const vector<Aparelho *> &ProcessadorRegras::getAparelhosAssoc() const {
    return aparelhosAssoc;
}

Zona *ProcessadorRegras::getZona() const {
    return zona;
}
