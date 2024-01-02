//
// Created by Utilizador on 27/10/2023.
//

#include "Zona.h"


int Zona::nextIdZona = 1;

Zona::Zona(int linha, int coluna) : linhaZona(linha),colunaZona(coluna){
    idZona = nextIdZona++;
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

bool Zona::adicionaSensor(const string& tipo) {
    if(tipo == "t")
        sensores.push_back(new TemperaturaSensor(Zona::getValorProp("Temperatura")));
    else if(tipo == "v")
        sensores.push_back(new MovimentoSensor(Zona::getValorProp("Vibracao")));
    else if(tipo == "m")
        sensores.push_back(new LuminosidadeSensor(Zona::getValorProp("Luz")));
    else if(tipo == "d")
        sensores.push_back(new RadiacaoSensor(Zona::getValorProp("Radiacao")));
    else if(tipo == "h")
        sensores.push_back(new HumidadeSensor(Zona::getValorProp("Humidade")));
    else if(tipo == "o")
        sensores.push_back(new SomSensor(Zona::getValorProp("Som")));
    else if(tipo == "f")
        sensores.push_back(new FumoSensor(Zona::getValorProp("Fumo")));
    else
        return false;

    return true;
}

bool Zona::adicionaAparelho(const string& tipo) {
    if(tipo == "a")
        aparelhos.push_back(new AquecedorAparelho(this));
    else if(tipo == "s")
       aparelhos.push_back(new AspersorAparelho(this));
    else if(tipo == "r")
        aparelhos.push_back(new RefrigeradorAparelho(this));
    else if(tipo == "l")
        aparelhos.push_back(new LampadaAparelho(this));
    else
        return false;

    return true;
}

bool Zona::adicionaProcessador(const string &comando) {

    processadores.push_back(new ProcessadorRegras(this,comando));

    return true;
}

bool Zona::restauraProcessador(ProcessadorRegras *proc) {
    bool encontrou = false;
    for(auto p : getProcessadores()){
        if(p->getIdProcessador() == proc->getIdProcessador())
            encontrou = true;
    }
    if(encontrou)
        return false;
    else{
        processadores.push_back(new ProcessadorRegras(*proc));
        return true;
    }
}

string Zona::removeComp(const string& tipo, const string& idComp) {
    ostringstream oss;
    string nome;

    if(tipo == "s"){
        for (auto it = sensores.begin(); it != sensores.end(); ++it) {
            if ((*it)->getIdSensor() == idComp) {
                delete *it;
                sensores.erase(it);
                nome = "sensor";
                oss << "O " << nome << " " << idComp << " foi removido da zona " << getIdZona() << ".";
                return oss.str();
            }
        }
    }
    else if(tipo == "a"){
        for (auto it = aparelhos.begin(); it != aparelhos.end(); ++it) {
            if ((*it)->getIdAparelho() == idComp) {
                delete *it;
                aparelhos.erase(it);
                nome = "aparelho";
                oss << "O " << nome << " " << idComp << " foi removido da zona " << getIdZona() << ".";
                return oss.str();
            }
        }
    }
    else if(tipo == "p"){
        for (auto it = processadores.begin(); it != processadores.end(); ++it) {
            if ((*it)->getIdProcessador() == idComp) {
                delete *it;
                processadores.erase(it);
                nome = "processador";
                oss << "O " << nome << " " << idComp << " foi removido da zona " << getIdZona() << ".";
                return oss.str();
            }
        }
    }
    return "Nao foi possivel remover o componente.";
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
                if(valor <= propriedade.first->getMax() || propriedade.first->getMax() == 0){
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

int Zona::getValorProp(string nome) const {
    for (auto & propriedade : propriedades) {
        if (propriedade.first->getNome() == nome)
            return propriedade.second;
    }
    return 0;
}

Sensor *Zona::getSensor(const string &idSensor) {
    for (auto & sensor : sensores) {
        if (sensor->getIdSensor() == idSensor)
            return sensor;
    }
    return nullptr;
}

Sensor *Zona::getSensorByProp(const std::string &prop) {
    for (auto & sensor : sensores) {
        if (sensor->getTipo() == prop)
            return sensor;
    }
    return nullptr;
}

ProcessadorRegras *Zona::getProcessador(const string &idProc) {
    for (auto & processador : processadores) {
        if (processador->getIdProcessador() == idProc)
            return processador;
    }
    return nullptr;
}

Aparelho *Zona::getAparelho(const string &idAparelho) {
    for (auto & aparelho : aparelhos) {
        if (aparelho->getIdAparelho() == idAparelho)
            return aparelho;
    }
    return nullptr;
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

void Zona::setNextIdZona(int nextIdZona) {
    Zona::nextIdZona = nextIdZona;
}