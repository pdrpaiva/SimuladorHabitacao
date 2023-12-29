//
// Created by Utilizador on 27/10/2023.
//

#include "Zona.h"


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

bool Zona::adicionaSensor(const string& tipo) {
    if(tipo == "t")
        sensores.push_back(new TemperaturaSensor());
    else if(tipo == "v")
        sensores.push_back(new MovimentoSensor());
    else if(tipo == "m")
        sensores.push_back(new LuminosidadeSensor());
    else if(tipo == "d")
        sensores.push_back(new RadiacaoSensor());
    else if(tipo == "h")
        sensores.push_back(new HumidadeSensor());
    else if(tipo == "o")
        sensores.push_back(new SomSensor());
    else if(tipo == "f")
        sensores.push_back(new FumoSensor());
    else
        return false;

    return true;
}

bool Zona::adicionaAparelho(const string& tipo) {
    if(tipo == "a")
        aparelhos.push_back(new AquecedorAparelho());
    else if(tipo == "s")
        aparelhos.push_back(new AspersorAparelho());
    else if(tipo == "r")
        aparelhos.push_back(new RefrigeradorAparelho());
    else if(tipo == "l")
        aparelhos.push_back(new LampadaAparelho());
    else
        return false;

    return true;
}

bool Zona::adicionaProcessador(const string &comando) {

    processadores.push_back(new ProcessadorRegras(this->idZona,comando));

    return true;
}

int Zona::removeComp(const string& tipo, const string& idComp) {
    //return 1 - válido
    //return 2 - nao ha sensores/aparelhos/processadores
    //return 3 - nao existe nenhum sensor/aparelho/processador com esse id

    //penso q este funcao de para simplificar, mas nao estava a conseguir

    if(tipo == "s"){
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
    else if(tipo == "a"){
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
    else if(tipo == "p"){
        if (processadores.empty())
            return 2;

        for (auto it = processadores.begin(); it != processadores.end(); ++it) {
            if ((*it)->getIdProcessador() == idComp) {
                delete *it;
                processadores.erase(it);
                return 1;
            }
        }

        return 3;
    }

    return 0;
}
/*
string Zona::zcomp() {
    ostringstream oss;

    oss << "Componentes da zona [" << this->idZona << "]:" << endl;
    if (!getSensores().empty()) {
        oss << "Sensores: " << endl;
        for (auto &sensor: getSensores()) {
            oss << "- ID: " << sensor->getIdSensor()
                  << " Tipo: " << sensor->getTipo()  << endl;
        }
    }
    if (!getAparelhos().empty()) {
        oss << "Aparelhos: "  << endl;
        for (auto &aparelho: getAparelhos()) {
            oss << "- ID: " << aparelho->getIdAparelho()
                  << " Tipo: " << aparelho->getTipo()  << endl;
        }
    }
    if (!getProcessadores().empty()) {
        oss << "Processsadores: "  << endl;
        for (auto &processador: getProcessadores()) {
            oss << "- ID: " << processador->getIdProcessador()
                  << " Tipo: " << processador->getComando()  << endl;
        }
    }

    return oss.str();
}
*/

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