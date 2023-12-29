//
// Created by Utilizador on 27/10/2023.
//

#include "ProcessadorRegras.h"
#include "../Zonas/Zona.h"

int ProcessadorRegras::nextIdProcessador = 1;

ProcessadorRegras::ProcessadorRegras(const int& idZona, const string &comando) : comando(comando){
    string idString = to_string(nextIdProcessador++);
    idProcessador = 'p' + idString;
    if (comando == "desliga")
        ligado = false;
    else
        ligado = true;

}

const string &ProcessadorRegras::getIdProcessador() const {
    return idProcessador;
}

const string &ProcessadorRegras::getComando() const {
    return comando;
}
