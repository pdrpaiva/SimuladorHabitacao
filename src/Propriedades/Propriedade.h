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
    virtual ~Propriedade();

    string getNome() const;
    string getUnidade() const;
    int getMin() const;
    int getMax() const;
};


#endif //TRABALHO_PROPRIEDADE_H

