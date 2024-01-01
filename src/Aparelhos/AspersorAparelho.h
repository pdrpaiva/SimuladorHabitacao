//
// Created by Utilizador on 25/12/2023.
//

#ifndef TRABALHO_ASPERSORAPARELHO_H
#define TRABALHO_ASPERSORAPARELHO_H
#include "Aparelho.h"

class Zona;
class AspersorAparelho : public Aparelho{
private:
    int counterdesligado;
public:
    AspersorAparelho(Zona* zona);
    ~AspersorAparelho();

    void aoDesligar() override;
    void aoLigar() override;
    void atualiza() override;
    bool recebeComando(const string& comando) override;
    void incrementaCounterDesligado();
    int getCounterDesligado() const;
    void resetCounterDesligado();
};


#endif //TRABALHO_ASPERSORAPARELHO_H
