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

ProcessadorRegras::ProcessadorRegras(const int& idZona, const string &comando){
    string idString = to_string(nextIdProcessador++);
    idProcessador = 'p' + idString;
    if (comando == "desliga"){
        ligado = false;
        this->comando = "Desliga";
    }
    else{
        ligado = true;
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

    return true;
}

bool ProcessadorRegras::adicionaRegra(const string &regra, Sensor* sensor, const int &x, const int &y) {
    if (regra == "entre")
        regras.push_back(new EntreRegra(regra,sensor,x,y));
    else if (regra == "fora")
        regras.push_back(new ForaRegra(regra,sensor,x,y));
    else
        return false;

    return true;
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
