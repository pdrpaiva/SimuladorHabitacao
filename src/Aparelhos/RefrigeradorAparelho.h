//
// Created by Utilizador on 25/12/2023.
//

#ifndef TRABALHO_REFRIGERADORAPARELHO_H
#define TRABALHO_REFRIGERADORAPARELHO_H
#include "Aparelho.h"

class Zona;
class RefrigeradorAparelho : public Aparelho{
private:

public:
    RefrigeradorAparelho(Zona* zona);
    ~RefrigeradorAparelho();

    void aoDesligar() override;
    void aoLigar() override;
    void atualiza() override;
};


#endif //TRABALHO_REFRIGERADORAPARELHO_H
