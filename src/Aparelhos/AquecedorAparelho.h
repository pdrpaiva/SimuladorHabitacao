//
// Created by Utilizador on 25/12/2023.
//

#ifndef TRABALHO_AQUECEDORAPARELHO_H
#define TRABALHO_AQUECEDORAPARELHO_H
#include "Aparelho.h"

class Zona;
class AquecedorAparelho : public Aparelho{
private:

public:
    AquecedorAparelho(Zona* zona);
    ~AquecedorAparelho();

    void aoDesligar() override;
    void aoLigar() override;
    void atualiza() override;
};


#endif //TRABALHO_AQUECEDORAPARELHO_H
