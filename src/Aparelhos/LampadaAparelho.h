//
// Created by Utilizador on 25/12/2023.
//

#ifndef TRABALHO_LAMPADAAPARELHO_H
#define TRABALHO_LAMPADAAPARELHO_H
#include "Aparelho.h"

class Zona;
class LampadaAparelho : public Aparelho{
private:

public:
    LampadaAparelho(Zona* zona);
    ~LampadaAparelho();

    void aoDesligar() override;
    void aoLigar() override;
    void atualiza() override;
};


#endif //TRABALHO_LAMPADAAPARELHO_H
