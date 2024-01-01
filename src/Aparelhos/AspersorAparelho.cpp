//
// Created by Utilizador on 25/12/2023.
//

#include "AspersorAparelho.h"
#include "../Zonas/Zona.h"

AspersorAparelho::AspersorAparelho(Zona* zona) : Aparelho(zona,"Aspersor"){}

AspersorAparelho::~AspersorAparelho() = default;

void AspersorAparelho::aoDesligar() {
    getZona()->alteraPropriedade("Vibracao",getZona()->getValorProp("Vibracao")-100);
}

void AspersorAparelho::aoLigar() {
    resetCounterDesligado();
}

bool AspersorAparelho::recebeComando(const string &comando) {
    //return true valido
    //return false ja esta ligado/desligado

    if(comando == "liga"){
        if(isLigado()) return false;
        aoLigar();
        setLigado();
    }
    else if(comando == "desliga"){
        if(!isLigado()) return false;

        setDesligado();
        resetCounterLigado();
    }

    setComando(comando);

    return true;
}

void AspersorAparelho::atualiza() {
    if (isLigado()) {
        incrementaCounterLigado();
        if (getCounterLigado() == 1) {
            getZona()->alteraPropriedade("Humidade", getZona()->getValorProp("Humidade") + 50);
            if (getZona()->getValorProp("Humidade") > 75)
                getZona()->alteraPropriedade("Humidade", 75);
            getZona()->alteraPropriedade("Vibracao", getZona()->getValorProp("Vibracao") + 100);
        }
        if (getCounterLigado() == 2) {
            getZona()->alteraPropriedade("Fumo", 0);
        }
    }
    else
    {
        incrementaCounterDesligado();
        if (getCounterDesligado() == 6) {
            aoDesligar();
        }
    }
}

void AspersorAparelho::incrementaCounterDesligado() {
    counterdesligado++;
}

int AspersorAparelho::getCounterDesligado() const {
    return counterdesligado;
}

void AspersorAparelho::resetCounterDesligado() {
    counterdesligado = 0;
}
