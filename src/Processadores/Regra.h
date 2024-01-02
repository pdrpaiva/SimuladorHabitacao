//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_REGRA_H
#define TRABALHO_REGRA_H

#include "../Sensores/Sensor.h"

class Regra {
private:
    string idRegra;
    static int nextIdRegra;
    string nome;
    Sensor* sensorAssoc;

public:
    Regra(const string& nome, Sensor* sensor);
    virtual ~Regra();

    virtual bool avaliar() = 0;
    virtual Regra * duplica()const = 0;


    const string &getIdRegra() const;
    const string &getNome() const;
    Sensor *getSensorAssoc() const;
    static void setNextIdRegra(int nextIdRegra);
    virtual int getValorX() const;
    virtual int getValorY() const;
};


#endif //TRABALHO_REGRA_H
