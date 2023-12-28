//
// Created by Utilizador on 27/10/2023.
//

#include "ProcessadorRegras.h"
#include "../Zonas/Zona.h"

int ProcessadorRegras::nextIdProcessador = 1;

ProcessadorRegras::ProcessadorRegras(const int& idZona, const bool &tipo) :  ligado(tipo){
    string idString = to_string(nextIdProcessador++);
    idProcessador = 'p' + idString;
}
