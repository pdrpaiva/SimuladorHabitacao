//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_PROCESSADORREGRAS_H
#define TRABALHO_PROCESSADORREGRAS_H

#include <vector>
#include <string>
#include "../Processadores/Regra.h"
#include "../Aparelhos/Aparelho.h"

using namespace std;
class Zona;

class ProcessadorRegras {
private:
    string idProcessador;
    static int nextIdProcessador;
    string comando;
    Zona* zona;
    vector<Regra*> regras;
    vector<Aparelho*> aparelhosAssoc;
public:
    ProcessadorRegras(Zona* zona, const string& comando);
    ~ProcessadorRegras();
    ProcessadorRegras(ProcessadorRegras& original);
    ProcessadorRegras& operator=(const ProcessadorRegras& original);

    bool adicionaRegra(const string& regra, Sensor* sensor, const int& x);
    bool adicionaRegra(const string& regra, Sensor* sensor, const int& x, const int& y);
    bool adicionaAparelho(Aparelho* aparelho);
    bool removeAparelho(const Aparelho* aparelho);
    void lePropriedade(Sensor* sensor);

    const string &getIdProcessador() const;
    const string &getComando() const;
    const Regra* getRegra(const string& idRegra) const;
    const vector<Regra *> &getRegras() const;
    int getNumRegras() const;
    void setComando(const string &comando);
    int RemoveRegra(const string& idRegra);
    void AtivaComando();
    static void setNextIdProcessador(int nextIdProcessador);
    const vector<Aparelho *> &getAparelhosAssoc() const;
    Zona *getZona() const;
};


#endif // TRABALHO_PROCESSADORREGRAS_H
