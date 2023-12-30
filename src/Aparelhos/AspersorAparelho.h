//
// Created by Utilizador on 25/12/2023.
//

#ifndef TRABALHO_ASPERSORAPARELHO_H
#define TRABALHO_ASPERSORAPARELHO_H
#include "Aparelho.h"

class Zona;
class AspersorAparelho : public Aparelho{
private:

public:
    AspersorAparelho(Zona* zona);
    ~AspersorAparelho();

    void aoDesligar() override;
    void aoLigar() override;
};


#endif //TRABALHO_ASPERSORAPARELHO_H
