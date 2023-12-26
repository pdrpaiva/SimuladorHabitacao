//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_PROPRIEDADE_H
#define TRABALHO_PROPRIEDADE_H

#include "string"
using namespace std;

class Propriedade {
private:
    string nome;
    string unidade;
    int min;
    int max;

public:
    Propriedade(string nome, string unidade,int min, int max);
    string getNome() const;
    string getUnidade() const;
    int getMin() const;
    int getMax() const;
    int getValor() const;
    void setValor(int valor);
};


#endif //TRABALHO_PROPRIEDADE_H
