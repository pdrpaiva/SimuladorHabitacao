//
// Created by ppedr on 28/12/2023.
//

#ifndef TRABALHO_IGUALREGRA_H
#define TRABALHO_IGUALREGRA_H
#include "Regra.h"

class IgualRegra : public Regra{
private:
    int valorX;

public:
    IgualRegra(const string& nome, Sensor* sensor,const int& x);
    ~IgualRegra() = default;
    bool avaliar() override;
    int getValorX() const override;
    Regra * duplica() const override;
};


#endif //TRABALHO_IGUALREGRA_H
