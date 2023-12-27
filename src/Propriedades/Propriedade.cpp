//
// Created by Utilizador on 27/10/2023.
//

#include "Propriedade.h"
using namespace std;

Propriedade::Propriedade(string _nome, string _unidade, int _min, int _max)
:nome(_nome), unidade(_unidade), min(_min), max(_max){}

string Propriedade::getNome() const {return nome;}

string Propriedade::getUnidade() const {return unidade;}

int Propriedade::getMin() const {return min;}

int Propriedade::getMax() const {return max;}

Propriedade::~Propriedade() = default;
