#include "Interface.h"


Interface::Interface(Terminal &terminal, Terreno* terreno) : terminal(terminal), terreno(terreno), wComandos(3, 0, 114, 6), wInfo(120, 0, 45, 43), wHabitacao(0, 6, 120, 38, false){
    for(int i=1; i<20; i++) {
        terminal.init_color(i, i, 0);
    }
    wInfo << move_to(0, 0) << set_color(3) << "Logs:";
}

Interface::~Interface() {
    delete terreno;
}

void Interface::processaComandos() {
    wComandos.clear();
    wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
    wComandos << move_to(0, 2) << set_color(0) << ">> ";

    if(existeHab)
        wHabitacao << move_to(4, 0) << set_color(0) << "Instante: " << terreno->getHabitacao()->getInstancia() << "                     ";

    string comando;
    saida = false;
    wComandos >> comando;

    if (comando == "sair") {
        wComandos << move_to(0, 2) << set_color(0) << "A encerrar . . .";
        sleep(2);
        wComandos.clear();
        terminal.clear();
        saida = true;
    }
    if (!saida)
        executaComandos(comando);
}

void Interface::executaComandos(const std::string &comando) {
    istringstream iss(comando);
    string cmd;
    iss >> cmd;

    if(iInfo >= 39){
        limpaLogs();
    }

    string naoExisteHab = "Nao existe nenhuma habitacao neste momento. 'hnova' para criar uma.";
    iInfo++;
    if(cmd == "prox") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            string extra;
            string s = "Uso correto: prox";
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                avanca(1);
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Avancou 1 instante.";
                terreno->getHabitacao()->setInstancia(terreno->getHabitacao()->getInstancia() + 1);
                return;
            }
        }
    }
    else if (cmd == "avanca") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int n;
            string s = "Uso correto: avanca <n>";
            if (iss >> n) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    processa();
                    avanca(n);
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    wInfo << move_to(0, iInfo++) << set_color(10) << "Avancou " << n << " instantes.";
                    terreno->getHabitacao()->setInstancia(terreno->getHabitacao()->getInstancia() + n);
                    return;
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "hnova") {
        int numLinhas, numColunas;
        string s = "Uso correto: hnova <num linhas> <num colunas> ";
        string limite = ", com 2 <= num linhas <= 4 e 2 <= num colunas <= 4";
        if (iss >> numLinhas >> numColunas) {
            string extra;
            if (iss >> extra || numLinhas < 2 || numLinhas > 4 || numColunas < 2 || numColunas > 4) {
                sintaxe(s,limite);
            } else {
                processa();
                limpaLogs();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                if(existeHab){
                    delete terreno->getHabitacao();
                    wHabitacao.clear();
                    for (auto& w : wZonas) {
                        w.clear();
                    }
                    wZonas.clear();
                    wInfo << move_to(0, iInfo++) << set_color(4) << "Habitacao atual foi apagada.";
                }

                existeHab = true;

                constroiHabitacao(numLinhas,numColunas);

                wInfo << move_to(0, iInfo++) << set_color(10) << "Criada nova habitacao.";

                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if(cmd == "hrem") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            string extra;
            string s = "Uso correto: hrem";
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                limpaLogs();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Habitacao eliminada.";
                delete terreno->getHabitacao();
                wHabitacao.clear();
                for (auto &w: wZonas) {
                    w.clear();
                }
                wZonas.clear();
                existeHab = false;
                return;
            }
        }
    }
    else if (cmd == "znova") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int linha, coluna;
            string s = "Uso correto: znova <linha> <coluna>";
            string limite = ", com 1 <= linha <= 4 e 1 <= coluna <= 4";
            if (iss >> linha >> coluna) {
                string extra;
                if (iss >> extra || linha < 1 || linha > 4 || coluna < 1 || coluna > 4) {
                    sintaxe(s, limite);
                } else {
                    processa();
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    constroiZona(linha, coluna);
                    return;
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "zrem"){
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string s = "Uso correto: zrem <ID zona>";
            if (iss >> idZona) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    processa();
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                    switch (terreno->getHabitacao()->removeZona(idZona)) {
                        case 1: //valido
                            limpaZona(idZona);
                            wInfo << move_to(0, iInfo++) << set_color(10) << "Zona [" << idZona << "] eliminada.";
                            break;
                        case 2: // nao existe nenhuma zona
                            wInfo << move_to(0, iInfo++) << set_color(4) << "A habitacao ainda nao tem nenhuma zona";
                            wInfo << move_to(0, iInfo++) << set_color(4) << "inicilizada. 'znova' para criar uma.";
                            break;
                        case 3: // nao existe nenhuma zona com esse id
                            wInfo << move_to(0, iInfo++) << set_color(4) << "Nao existe nenhuma zona com esse ID.";
                            break;
                    }
                    return;
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if(cmd == "zlista"){
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            string extra;
            string s = "Uso correto: zlista";
            if (iss >> extra) {
                sintaxe(s);
            } else {
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                if(existeZSPA()) {
                    processa();
                    limpaLogs();
                    wInfo << move_to(0, iInfo++) << set_color(11) << "Zonas da habitacao:";
                    for (auto &z: terreno->getHabitacao()->getZonas()) {
                        iInfo++;
                        wInfo << move_to(0, iInfo++) << set_color(11) << "Zona [" << z->getIdZona() << "]";
                        wInfo << move_to(0, iInfo++) << set_color(11) << "Numero de Sensores: " << z->getNumSensores();
                        wInfo << move_to(0, iInfo++) << set_color(11) << "Numero de Processadores: "
                              << z->getNumProcessadores();
                        wInfo << move_to(0, iInfo++) << set_color(11) << "Numero de Aparelhos: "
                              << z->getNumAparelhos();
                    }
                }
                return;
            }
        }
    }
    else if (cmd == "zcomp") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string s = "Uso correto: zcomp <ID zona>";
            if (iss >> idZona) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                    if(existeZSPA(idZona)){
                        if (terreno->getHabitacao()->getZona(idZona)->getNumAparelhos() != 0 || terreno->getHabitacao()->getZona(idZona)->getNumProcessadores() != 0 || terreno->getHabitacao()->getZona(idZona)->getNumSensores() != 0) {
                            processa();
                            limpaLogs();
                            wInfo << move_to(0, iInfo++) << set_color(14) << "Componentes da zona [" << idZona << "]:";
                            if (!terreno->getHabitacao()->getZona(idZona)->getSensores().empty()) {
                                wInfo << move_to(0, iInfo++) << set_color(14) << "Sensores: ";
                                for (auto &sensor: terreno->getHabitacao()->getZona(idZona)->getSensores()) {
                                    wInfo << move_to(0, iInfo++) << set_color(11) << "- " <<sensor->getIdSensor() << " | " << sensor->getValor() << " | " << sensor->getTipo();
                                }
                            }
                            if (!terreno->getHabitacao()->getZona(idZona)->getAparelhos().empty()) {
                                wInfo << move_to(0, iInfo++) << set_color(14) << "Aparelhos: ";
                                for (auto &aparelho: terreno->getHabitacao()->getZona(idZona)->getAparelhos()) {
                                    wInfo << move_to(0, iInfo++) << set_color(11) << "- " <<aparelho->getIdAparelho() << " | Ult.Comando: " << aparelho->getComando() << " | " << aparelho->getTipo();
                                }
                            }
                            if (!terreno->getHabitacao()->getZona(idZona)->getProcessadores().empty()) {
                                wInfo << move_to(0, iInfo++) << set_color(14) << "Processsadores: ";
                                for (auto &processador: terreno->getHabitacao()->getZona(idZona)->getProcessadores()) {
                                    wInfo << move_to(0, iInfo++) << set_color(11) << "- " <<processador->getIdProcessador() << " | Regras: " << processador->getNumRegras() << " | " << processador->getComando();
                                }
                            }
                            iInfo++;
                        } else {
                            wInfo << move_to(0, iInfo++) << set_color(4) << "A zona [" << idZona
                                  << "] ainda nao tem nenhum componente.";
                            wInfo << move_to(0, iInfo++) << set_color(4) << "'cnovo' para adicionar um.";
                        }
                    }
                    return;
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "zprops") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string s = "Uso correto: zprops <ID zona>";
            if (iss >> idZona) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                    if(existeZSPA(idZona)){
                        processa();
                        limpaLogs();
                        wInfo << move_to(0, iInfo++) << set_color(11) << "Propriedades da zona [" << idZona << "]:";
                        for (auto &propriedade: terreno->getHabitacao()->getZona(idZona)->getPropriedades()) {
                            iInfo++;
                            wInfo << move_to(0, iInfo++) << set_color(11) << "- Nome: " << propriedade.first->getNome();
                            wInfo << move_to(0, iInfo++) << set_color(11) << "- Valor: " << propriedade.second
                                  << " "
                                  << propriedade.first->getUnidade();
                        }
                        return;
                    }
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "pmod") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string nome;
            int valor;
            string s = "Uso correto: pmod <ID zona> <nome> <valor>";
            if (iss >> idZona >> nome >> valor) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                    if(existeZSPA(idZona)){
                        processa();
                        switch (terreno->getHabitacao()->getZona(idZona)->alteraPropriedade(nome,valor)) {
                            case 1:
                                wInfo << move_to(0, iInfo++) << set_color(10) << "O valor da propriedade " << nome << " foi atualizado.";
                                if (terreno->getHabitacao()->getZona(idZona)->getSensorByProp(nome) != nullptr) {
                                    terreno->getHabitacao()->getZona(idZona)->getSensorByProp(nome)->setValor(valor);
                                }
                                break;
                            case 2:
                                if (terreno->getHabitacao()->getZona(idZona)->getPropriedade(nome)->getMax() != 0)
                                {
                                    wInfo << move_to(0, iInfo++) << set_color(4) << "Erro. O valor nao esta no intervalo";
                                    wInfo << move_to(0, iInfo++) << set_color(4) << "permitido ["
                                          << terreno->getHabitacao()->getZona(idZona)->getPropriedade(nome)->getMin() << ","
                                          << terreno->getHabitacao()->getZona(idZona)->getPropriedade(nome)->getMax() << "].";
                                    break;
                                }
                                else
                                {
                                    wInfo << move_to(0, iInfo++) << set_color(4) << "Erro. Valor inferior ao minimo permitido   ["
                                          << terreno->getHabitacao()->getZona(idZona)->getPropriedade(nome)->getMin() << "].";
                                    break;
                                }
                            case 3:
                                wInfo << move_to(0, iInfo++) << set_color(4) << "A propriedade '" << nome << "' nao existe.";
                                break;
                        }
                        return;
                    }
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "cnovo") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            char spa;
            string tipoComando;
            string s = "Uso correto: cnovo <ID zona> <s | p | a> <tipo | comando>";
            if (iss >> idZona >> spa >> tipoComando) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                    if(existeZSPA(idZona)){
                        if (spa != 's' && spa != 'p' && spa != 'a') {
                            sintaxe(s);
                            wInfo << move_to(0, iInfo++) << set_color(4) << "Erro de sintaxe.";
                        } else {
                            if (spa == 'p') {
                                processa();
                                if (tipoComando == "liga" || tipoComando == "desliga") {
                                    if(terreno->getHabitacao()->getZona(idZona)->adicionaProcessador(tipoComando)) {
                                        wInfo << move_to(0, iInfo++) << set_color(10)
                                              << "Foi adicionado um processador na zona " << idZona << ".";
                                        atualizaZona(idZona);
                                    }
                                } else {
                                    wInfo << move_to(0, iInfo++) << set_color(4) << "Esse comando nao existe. liga/desliga";
                                }
                                return;
                            } else if (spa == 'a') {
                                processa();
                                if (tipoComando == "a" || tipoComando == "s" || tipoComando == "r" ||
                                    tipoComando == "l") {
                                    if (terreno->getHabitacao()->getZona(idZona)->adicionaAparelho(tipoComando)) {
                                        wInfo << move_to(0, iInfo++) << set_color(10) << "Foi adicionado um "
                                        << terreno->getHabitacao()->getZona(idZona)->getAparelhos().back()->getTipo() << " na zona " << idZona << ".";
                                        atualizaZona(idZona);
                                    } else {
                                        wInfo << move_to(0, iInfo++) << set_color(4)
                                              << "Nao foi possivel adicionar o aparelho.";
                                    }
                                } else {
                                    wInfo << move_to(0, iInfo++) << set_color(4) << "Esse aparelho nao existe.";
                                }
                                return;
                            } else if (spa == 's') {
                                processa();
                                if (tipoComando == "t" || tipoComando == "v" || tipoComando == "m" ||
                                    tipoComando == "d" || tipoComando == "h" || tipoComando == "o" ||
                                    tipoComando == "f") {
                                    if (terreno->getHabitacao()->getZona(idZona)->adicionaSensor(tipoComando)) {
                                        wInfo << move_to(0, iInfo++) << set_color(10) << "Foi adicionado um sensor de "
                                        << terreno->getHabitacao()->getZona(idZona)->getSensores().back()->getTipo();
                                        wInfo << move_to(0, iInfo++) << set_color(10) << "na zona " << idZona << ".";
                                        atualizaZona(idZona);
                                    } else {
                                        wInfo << move_to(0, iInfo++) << set_color(4)
                                              << "Nao foi possivel adicionar o sensor.";
                                    }
                                } else {
                                    wInfo << move_to(0, iInfo++) << set_color(4) << "Esse sensor nao existe.";
                                }
                                return;
                            }
                        }
                    }
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "crem") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string id;
            string spa;
            string s = "Uso correto: crem <ID zona> <s | p | a> <ID>";
            if (iss >> idZona >> spa >> id) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    if (spa != "s" && spa != "p" && spa != "a") {
                        sintaxe(s);
                    } else {
                        processa();
                        wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                        if(existeZSPA(idZona,id)) {
                            wInfo << move_to(0, iInfo++) << set_color(10)
                                  << terreno->getHabitacao()->getZona(idZona)->removeComp(spa, id);
                            atualizaZona(idZona);
                        }
                    }
                }
            } else {
                sintaxe(s);
            }
        }
        return;
    }
    else if (cmd == "rnova") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona, x, y;
            string regra, idProcRegras, idSensor, extra;
            bool encontrouRegra = false; //bool para saber se encontrou uma das regras
            bool sensorExiste = false; //bool para saber se o sensor existe

            string arrayRegras[] = {"igual_a", "menor_que", "maior_que", "entre", "fora"};
            string s = "Uso correto: rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]";

            if (iss >> idZona >> idProcRegras >> regra >> idSensor) {
                for (const auto &valor: arrayRegras) {
                    if (regra == valor) {
                        encontrouRegra = true;
                        break;
                    }
                }
                if (!encontrouRegra) {
                    char resposta;
                    if (!fichAberto) {
                        do {
                            wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
                            wComandos << move_to(0, 2) << set_color(4) << "Sintaxe invalida. Essa regra nao existe. ";
                            wComandos << move_to(0, 3) << set_color(0) << "Pretende ver as regras dos processadores? (S/N)";
                            resposta = wComandos.getchar();
                            if (resposta == 'S' || resposta == 's') {
                                wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
                                wComandos << move_to(0, 2) << set_color(0) << "Regras atuais: igual_a (x) , menor_que (x) , maior_que (x), entre (x,y) , fora (x,y)";
                                wComandos << move_to(0, 3) << set_color(0) << "Pressione qualquer tecla para continuar . . .    ";
                                wComandos.getchar();
                                wComandos.clear();
                                return;
                            } else if (resposta == 'N' || resposta == 'n') {
                                wComandos.clear();
                                return;
                            }
                        } while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');
                    }
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                    if (terreno->getHabitacao()->getZona(idZona) == nullptr) {
                        wInfo << move_to(0, iInfo++) << set_color(4) << "Essa zona nao existe.";
                        return;
                    }

                    for (const auto &sensor: terreno->getHabitacao()->getZona(idZona)->getSensores()) {
                        if (idSensor == sensor->getIdSensor()) {
                            sensorExiste = true;
                            break;
                        }
                    }
                    if(!sensorExiste){
                        wInfo << move_to(0, iInfo++) << set_color(4) << "O sensor " << idSensor << " nao existe.";
                    }
                    else {
                        if (terreno->getHabitacao()->getZonas().empty()) {
                            wInfo << move_to(0, iInfo++) << set_color(4) << "A habitacao ainda nao tem nenhuma zona";
                            wInfo << move_to(0, iInfo++) << set_color(4) << "inicilizada. 'znova' para criar uma.";
                        } else {
                            if (terreno->getHabitacao()->getZona(idZona)->getProcessador(idProcRegras) == nullptr) {
                                wInfo << move_to(0, iInfo++) << set_color(4) << "Esse processador nao existe.";
                                return;
                            }else {
                                if (regra == "entre" || regra == "fora") {
                                    if (iss >> x >> y) {
                                        if (iss >> extra) {
                                            sintaxe(s);
                                        } else {
                                            processa();
                                            if (terreno->getHabitacao()->getZona(idZona)->getProcessador(idProcRegras)
                                            ->adicionaRegra(regra,terreno->getHabitacao()->getZona(idZona)->getSensor(idSensor), x, y)) {
                                                wInfo << move_to(0, iInfo++) << set_color(10) << "Foi adicionada uma nova regra a " << idProcRegras << ".";
                                                atualizaZona(idZona);
                                            } else {
                                                wInfo << move_to(0, iInfo++) << set_color(4) << "Nao foi possivel adicionar a regra ao processador.";
                                            }
                                            return;
                                        }
                                    } else {
                                        sintaxe(s);
                                    }
                                } else {
                                    if (iss >> x) {
                                        if (iss >> extra) {
                                            sintaxe(s);
                                        } else {
                                            processa();
                                            if (terreno->getHabitacao()->getZona(idZona)->getProcessador(idProcRegras)
                                                    ->adicionaRegra(regra,terreno->getHabitacao()->getZona(idZona)->getSensor(idSensor), x)) {
                                                wInfo << move_to(0, iInfo++) << set_color(10) << "Foi adicionada uma nova regra a " << idProcRegras << ".";
                                                atualizaZona(idZona);
                                            } else {
                                                wInfo << move_to(0, iInfo++) << set_color(4) << "Nao foi possivel adicionar a regra ao processador.";
                                            }
                                            return;
                                        }
                                    } else {
                                        sintaxe(s);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "pmuda") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
                int idZona;
                string idProcRegras, pcomando;
                string s = "Uso correto: pmuda <ID zona> <ID proc. regras> <novo comando>";

                if(iss >> idZona >> idProcRegras >> pcomando) {
                    string extra;
                    if (iss >> extra) {
                        sintaxe(s);
                    } else {
                        wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                        if(existeZSPA(idZona,idProcRegras)){
                            if(pcomando != "liga" && pcomando != "desliga") {
                                wInfo << move_to(0, iInfo++) << set_color(4) << "Esse comando nao existe. liga/desliga";
                            }
                            else {
                                processa();
                                terreno->getHabitacao()->getZona(idZona)->getProcessador(idProcRegras)->setComando(pcomando);
                                wInfo << move_to(0, iInfo++) << set_color(10) << "O comando de " << idProcRegras
                                      << " foi alterado para " << pcomando << ".";
                            }
                        }
                        return;
                    }
                } else {
                    sintaxe(s);
                }
        }
    }
    else if (cmd == "rlista") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string idProcRegras;
            string s = "Uso correto: rlista <ID zona> <ID proc. regras>";
            if (iss >> idZona >> idProcRegras) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    processa();
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    if (existeZSPA(idZona, idProcRegras)) {
                        limpaLogs();
                        wInfo << move_to(0, iInfo++) << set_color(14) << "Regras do processador "
                              << idProcRegras << " da zona " << idZona << ":";
                        if (!terreno->getHabitacao()->getZona(idZona)->getSensores().empty()) {
                            for (auto &regra: terreno->getHabitacao()->getZona(idZona)->getProcessador(
                                    idProcRegras)->getRegras()) {
                                if (regra->getNome() == "entre" || regra->getNome() == "fora") {
                                    wInfo << move_to(0, iInfo++) << set_color(11) << "- " << regra->getIdRegra()
                                          << " | " << regra->getSensorAssoc()->getIdSensor() << " "
                                          << regra->getSensorAssoc()->getTipo()
                                          << " | " << regra->getNome() << " (" << regra->getValorX() << " e "
                                          << regra->getValorY() << ")";
                                } else {
                                    wInfo << move_to(0, iInfo++) << set_color(11) << "- " << regra->getIdRegra()
                                          << " | " << regra->getSensorAssoc()->getIdSensor() << " "
                                          << regra->getSensorAssoc()->getTipo()
                                          << " | " << regra->getNome() << " (" << regra->getValorX() << ")";
                                }
                            }
                        } else {
                            wInfo << move_to(0, iInfo++) << set_color(4)
                                  << "O processador ainda nao tem nenhuma regra.";
                            wInfo << move_to(0, iInfo++) << set_color(4) << "'rnova' para adicionar uma.";
                        }
                        iInfo++;
                    }
                return;
            }
        }else {
                sintaxe(s);
            }
        }
    }

    else if (cmd == "rrem") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            string idProcRegras, idRegra;
            int idZona;
            string s = "Uso correto: rrem <ID zona> <ID proc. regras> <ID regra>";
            if (iss >> idZona >> idProcRegras >> idRegra) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    if (existeZSPA(idZona, idProcRegras)){
                         if (terreno->getHabitacao()->getZona(idZona)->getProcessador(idProcRegras)->getRegra(idRegra) == nullptr){
                            wInfo << move_to(0, iInfo++) << set_color(4) << "Essa regra nao existe.";
                        }
                        else {
                             switch (terreno->getHabitacao()->getZona(idZona)->getProcessador(
                                     idProcRegras)->RemoveRegra(
                                     idRegra)) {
                                 case 1:
                                     processa();
                                     wInfo << move_to(0, iInfo++) << set_color(10) << "A regra " << idRegra <<
                                           " foi removida do processador " << idProcRegras << ".";
                                     break;
                                 case 2:
                                     wInfo << move_to(0, iInfo++) << set_color(4) << "O processador " << idProcRegras <<
                                           " ainda nao tem nenhuma regra.";
                                     wInfo << move_to(0, iInfo++) << set_color(4) << "'rnova' para adicionar uma.";
                                     break;
                                 case 3:
                                     wInfo << move_to(0, iInfo++) << set_color(4) << "O processador " << idProcRegras <<
                                           " nao tem nenhuma regra com esse ID.";
                                     break;
                             }
                         }
                            return;
                        }
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "asoc") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string idProcRegras, idAparelho;
            string s = "Uso correto: asoc <ID zona> <ID proc. regras> <ID aparelho>";
            if (iss >> idZona >> idProcRegras >> idAparelho) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                   if (existeZSPA(idZona,idProcRegras)){
                         if (terreno->getHabitacao()->getZona(idZona)->getAparelho(idAparelho) == nullptr){
                            wInfo << move_to(0, iInfo++) << set_color(4) << "Esse aparelho nao existe.";
                        }
                        else{
                            if (terreno->getHabitacao()->getZona(idZona)->getProcessador(idProcRegras)->adicionaAparelho(
                                    terreno->getHabitacao()->getZona(idZona)->getAparelho(idAparelho))) {
                                processa();
                                wInfo << move_to(0, iInfo++) << set_color(10) << "O aparelho " << idAparelho <<
                                      " foi associado ao";
                                wInfo << move_to(0, iInfo++) << set_color(10) << "processador " << idProcRegras << ".";
                            } else {
                                wInfo << move_to(0, iInfo++) << set_color(4) << "O aparelho " << idAparelho <<
                                      " ja esta associado ";
                                wInfo << move_to(0, iInfo++) << set_color(4) << "ao processador " << idProcRegras << ".";
                            }
                            return;
                        }
                    }
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "ades") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string idProcRegras, idAparelho;
            string s = "Uso correto: ades <ID zona> <ID proc. regras> <ID aparelho>";
            if (iss >> idZona >> idProcRegras >> idAparelho) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    if (existeZSPA(idZona,idProcRegras)){
                     if (terreno->getHabitacao()->getZona(idZona)->getAparelho(idAparelho) == nullptr){
                            wInfo << move_to(0, iInfo++) << set_color(4) << "Esse aparelho nao existe.";
                        }
                        else{
                            if (terreno->getHabitacao()->getZona(idZona)->getProcessador(idProcRegras)->removeAparelho(
                                    terreno->getHabitacao()->getZona(idZona)->getAparelho(idAparelho))) {
                                processa();
                                wInfo << move_to(0, iInfo++) << set_color(10) << "O aparelho [" << idAparelho <<
                                      "] foi desassociado do";
                                wInfo << move_to(0, iInfo++) << set_color(10) << "processador [" << idProcRegras << "].";
                            } else {
                                wInfo << move_to(0, iInfo++) << set_color(4) << "O aparelho [" << idAparelho <<
                                      "] nao esta associado ";
                                wInfo << move_to(0, iInfo++) << set_color(4) << "ao processador [" << idProcRegras << "].";
                            }
                            return;
                        }
                    }
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "acom") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string idAparelho, acomando;
            string s = "Uso correto: acom <ID zona> <ID aparelho> <comando>";

            if (iss >> idZona >> idAparelho >> acomando) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    if(existeZSPA(idZona,idAparelho)){
                        if(acomando == "liga" || acomando == "desliga"){
                            processa();
                            if(terreno->getHabitacao()->getZona(idZona)->getAparelho(idAparelho)->recebeComando(acomando)){
                                wInfo << move_to(0, iInfo++) << set_color(10) << "Comando " << acomando
                                      << " enviado ao aparelho " << idAparelho << ".";
                                atualizaZona(idZona);
                            }
                            else {
                                wInfo << move_to(0, iInfo++) << set_color(4) << "O aparelho " << idAparelho
                                      << " ja se encontra " << acomando << "do.";
                            }
                        }
                        else {
                            wInfo << move_to(0, iInfo++) << set_color(4) << "Comando invalido. liga/desliga";
                        }
                    }
                    return;
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "psalva") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            int idZona;
            string idProcRegras, nomeSave;
            string s = "Uso correto: psalva <ID zona> <ID proc. regras> <nome>";

            if (iss >> idZona >> idProcRegras >> nomeSave) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    bool encontrou = false;
                    for(auto &ps : terreno->getHabitacao()->getProcGuardados()){
                        if(ps.first == nomeSave)
                            encontrou = true;
                    }
                    if(encontrou){
                        wInfo << move_to(0, iInfo++) << set_color(4) << "Ja existe um processador guardado com esse nome";
                    }
                    else {
                        if(existeZSPA(idZona,idProcRegras)){
                            processa();
                            terreno->getHabitacao()->guardaProc(nomeSave,terreno->getHabitacao()->getZona(idZona)->getProcessador(idProcRegras));
                            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                            wInfo << move_to(0, iInfo++) << set_color(10) << "O processador " << idProcRegras
                                  << " da zona " << idZona;
                            wInfo << move_to(0, iInfo++) << set_color(10) << " foi guardado na memoria.";
                            return;
                        }
                    }
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if (cmd == "prepoe") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            string nome;
            string s = "Uso correto: prepoe <nome>";

            if (iss >> nome) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                    if(terreno->getHabitacao()->getProcGuardado(nome) == nullptr){
                        wInfo << move_to(0, iInfo++) << set_color(4) << "Nao existe nenhum processador guardado com esse nome";
                    }
                    else {
                        processa();
                        int idZonaProc = terreno->getHabitacao()->getProcGuardado(nome)->getZona()->getIdZona();
                        bool existeZona = false;
                        if(existeZSPA(idZonaProc)){
                            if(terreno->getHabitacao()->getZona(idZonaProc)->restauraProcessador(terreno->getHabitacao()->getProcGuardado(nome))){
                                wInfo << move_to(0, iInfo++) << set_color(10) << "Processador " << nome << " reposto com sucesso.";
                                atualizaZona(idZonaProc);
                            }
                            else {
                                wInfo << move_to(0, iInfo++) << set_color(4) << "Nao foi possivel adicionar o save " << nome << ".";
                                wInfo << move_to(0, iInfo++) << set_color(4) << "O original ainda existe.";
                            }
                        }
                    }
                }
            } else {
                sintaxe(s);
            }
        }
        return;
    }
    else if (cmd == "prem") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            string nome;
            string s = "Uso correto: prem <nome>";

            if (iss >> nome) {
                string extra;
                if (iss >> extra) {
                    sintaxe(s);
                } else {
                    processa();
                    switch (terreno->getHabitacao()->apagaCopiaProc(nome)) {
                        case 1:
                            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                            wInfo << move_to(0, iInfo++) << set_color(10) << "A copia " << nome << " foi eliminada da memoria.";
                            break;
                        case 2:
                            wInfo << move_to(0, iInfo++) << set_color(4) << "Nao existe nenhum processor guardado em memoria.";
                            break;

                        case 3:
                            wInfo << move_to(0, iInfo++) << set_color(4) << "Nao existe nenhum processor guardado com esse nome";
                            break;
                    }
                    return;
                }
            } else {
                sintaxe(s);
            }
        }
    }
    else if(cmd == "plista") {
        if (!existeHab) {
            sintaxe(naoExisteHab);
        } else {
            string extra;
            string s = "Uso correto: plista";

            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                if(terreno->getHabitacao()->getProcGuardados().empty())
                    wInfo << move_to(0, iInfo++) << set_color(4) << "Nao existem processadores guardados.";
                else{
                    limpaLogs();
                    wInfo << move_to(0, iInfo++) << set_color(11) << "Processadores guardados em memoria:";
                    for (auto &p: terreno->getHabitacao()->getProcGuardados()) {
                        iInfo++;
                        wInfo << move_to(0, iInfo++) << set_color(11) << "Nome da Copia: " << p.first;
                        wInfo << move_to(0, iInfo++) << set_color(11) << "Id do Processador: " << p.second->getIdProcessador();
                        if(terreno->getHabitacao()->getZona(p.second->getZona()->getIdZona()) == nullptr)
                            wInfo << move_to(0, iInfo++) << set_color(11) << "Id da Zona: A zona deixou de existir.";
                        else
                            wInfo << move_to(0, iInfo++) << set_color(11) << "Id da Zona: " << p.second->getZona()->getIdZona();
                    }
                }
            }
        }
        return;
    }
    else if (cmd == "exec") {
        string nomeFich;
        string s = "Uso correto: exec <nome de ficheiro>";
        if(iss >> nomeFich) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                carregaComandos(nomeFich);
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "clear") {
        string extra;
        string s = "Uso correto: clear";
        if(iss >> extra){
            sintaxe(s);
        }
        else{
            processa();
            limpaLogs();
            if (!fichAberto)
                processaComandos();
            else
                return;
        }
    }
    else {
        wComandos << move_to(0, 2) << set_color(4) << "Comando desconhecido: " << comando;
        wComandos << move_to(0, 3) << set_color(0) << "Pressione qualquer tecla para continuar . . .";
        wComandos.getchar();
        wComandos.clear();
        processaComandos();
    }
}

void Interface::carregaComandos(const std::string &nomeFich) {
    ifstream fich(nomeFich);
    string linha;

    if (fich.is_open()) {
        while (getline(fich, linha)) {
            fichAberto = true;
            if (linha == "sair"){
                wComandos << move_to(0, 2) << set_color(0) << "A encerrar . . .";
                sleep(2);
                wComandos.clear();
                terminal.clear();
                fich.close();
                exit(0);
            }
            executaComandos(linha);
        }
        fichAberto = false;
        fich.close();
        return;
    } else {
        wComandos << move_to(0, 2) << set_color(4) << "Erro ao abrir o arquivo: " << nomeFich;
    }
}

void Interface::sintaxe(const std::string &s) {
    wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
    wComandos << move_to(0, 2) << set_color(4) << "Sintaxe invalida. " << s;
    wComandos << move_to(0, 3) << set_color(0) << "Pressione qualquer tecla para continuar . . .";
    if(!fichAberto)
        wComandos.getchar();
    wComandos.clear();
}

void Interface::sintaxe(const string &s, const string &s2) {
    wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
    wComandos << move_to(0, 2) << set_color(4) << "Sintaxe invalida. " << s << s2;
    wComandos << move_to(0, 3) << set_color(0) << "Pressione qualquer tecla para continuar . . .";
    if(!fichAberto)
        wComandos.getchar();
    wComandos.clear();
}

void Interface::processa() {
    wComandos.clear();
    wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
    wComandos << move_to(0, 2) << set_color(10) << "A processar . . .";
    sleep(1);
    wComandos.clear();
}

bool Interface::Sair() const{
    if (!saida)
        return false;
    else
        return true;
}

void Interface::constroiHabitacao(int nLinhas, int nColunas) {
    int x, y = 7, w = 27, h = 9;
    idZonas.resize(nLinhas*nColunas,-1);

    for (int i = 0; i < nLinhas; i++) {
        x = 3;
        for (int j = 0; j < nColunas; j++) {
            wZonas.emplace_back(x, y, w, h,true);
            x += 29;
        }
        y += 9;
    }

    terreno->criaHabitacao(nLinhas,nColunas);
}

void Interface::avanca(int it) {
    for (int i = 0; i < it; i++) {
        for (auto &z: terreno->getHabitacao()->getZonas()) {
            bool aparelhoAssoc = false;
            for(auto &a : z->getAparelhos()){
                for (auto &p: z->getProcessadores()) {
                    bool ativar = true;
                    for (auto &r: p->getRegras()) {
                        if (!r->avaliar())
                            ativar = false;
                    }
                    if (ativar)
                        p->AtivaComando();
                }
                if (a->isLigado())
                    a->atualiza();
                else if (a->getTipo() == "Aspersor")
                    a->atualiza();
            }
            for (auto &s: z->getSensores()) {
                s->setValor(z->getValorProp(s->getTipo()));
            }
            atualizaZona(z->getIdZona());
        }
    }
}


void Interface::constroiZona(int linha, int coluna) {
    int x = 0, y = 0;
    int id = 0;
    int numColunas = terreno->getHabitacao()->getHabColunas();
    int posZona = 0;

    switch(terreno->getHabitacao()->adicionaZona(linha,coluna)) {
        case 1: //valido
            posZona = (linha - 1) * numColunas + (coluna - 1);

            if(!terreno->getHabitacao()->getZonas().empty()){
                id = terreno->getHabitacao()->getZonas().back()->getIdZona();
                terreno->getHabitacao()->getZonas().back()->setPosZona(posZona);
            }

            idZonas[posZona] = id;

            wInfo << move_to(0, iInfo++) << set_color(10) << "Criada uma nova zona. Linha " << linha << " Coluna " << coluna << "";
            wZonas[posZona] << move_to(x, y) << set_color(0) << "ID: " << terreno->getHabitacao()->getZonas().back()->getIdZona();
            wZonas[posZona] << move_to(x, y+1) << set_color(0) << "S: -";
            wZonas[posZona] << move_to(x, y+2) << set_color(0) << "A: -";
            wZonas[posZona] << move_to(x, y+3) << set_color(0) << "P: -";

            break;
        case 2: //zona fora da habitacao
            wInfo << move_to(0, iInfo++) << set_color(4) << "Impossivel adicionar uma zona fora da";
            wInfo << move_to(0, iInfo++) << set_color(4) << "habitacao.";
            break;

        case 3: //ja existe uma zona nessa posicao
            wInfo << move_to(0, iInfo++) << set_color(4) << "Ja existe uma zona nessa posicao.";
            break;
    }
}

void Interface::atualizaZona(int idZona) {
    int x = 0 , y = 0 ;
    int posZona = terreno->getHabitacao()->getZona(idZona)->getPosZona();

    wZonas[posZona].clear();

    wZonas[posZona] << move_to(x, y) << set_color(0) << "ID: " << terreno->getHabitacao()->getZona(idZona)->getIdZona();

    wZonas[posZona] << move_to(x, y+1) << set_color(0) << "S:";
    if(terreno->getHabitacao()->getZona(idZona)->getSensores().empty()){
        wZonas[posZona] << move_to(x+3, y+1) << set_color(0) << "- ";
    }
    else {
        for (auto& s : terreno->getHabitacao()->getZona(idZona)->getSensores()) {
            x += 3;
            if(x == 24){
                wZonas[posZona] << move_to(x, y+1) << set_color(0) << "*";
                break;
            }
            wZonas[posZona] << move_to(x, y+1) << set_color(0) << s->getIdSensor() << " ";
        }
        x = 0;
    }

    wZonas[posZona] << move_to(x, y+2) << set_color(0) << "A:";
    if(terreno->getHabitacao()->getZona(idZona)->getAparelhos().empty()){
        wZonas[posZona] << move_to(x+3, y+2) << set_color(0) << "- ";
    }
    else {
        for (auto &a: terreno->getHabitacao()->getZona(idZona)->getAparelhos()) {
            x += 3;
            if(x == 24){
                wZonas[posZona] << move_to(x, y+2) << set_color(0) << "*";
                break;
            }
            wZonas[posZona] << move_to(x, y + 2) << set_color(0) << a->getIdAparelho() << " ";
        }
        x = 0;
    }

    wZonas[posZona] << move_to(x, y+3) << set_color(0) << "P:";
    if(terreno->getHabitacao()->getZona(idZona)->getProcessadores().empty()){
        wZonas[posZona] << move_to(x+3, y+3) << set_color(0) << "- ";
    }
    else {
        for (auto& p : terreno->getHabitacao()->getZona(idZona)->getProcessadores()) {
            x += 3;
            if(x == 24){
                wZonas[posZona] << move_to(x, y+3) << set_color(0) << "*";
                break;
            }
            wZonas[posZona] << move_to(x, y + 3) << set_color(0) << p->getIdProcessador() << " ";
        }
        x = 0;
    }
}

void Interface::limpaZona(int idZona) {
    for(int i = 0; i < idZonas.size(); i++){
        if(idZonas[i] == idZona){
            wZonas[i].clear();
            idZonas[i] = -1;
            break;
        }
    }
}

void Interface::limpaLogs() {
    iInfo = 2;
    wInfo.clear();
    wInfo << move_to(0, 0) << set_color(3) << "Logs:";
}

bool Interface::existeZSPA(const int &idZona, const std::string &id){

    if (idZona == -1 && id.empty()) { //0 parametros

        if(terreno->getHabitacao()->getZonas().empty()){
            wInfo << move_to(0, iInfo++) << set_color(4) << "A habitacao ainda nao tem nenhuma zona";
            wInfo << move_to(0, iInfo++) << set_color(4) << "inicilizada. 'znova' para criar uma.";
            return false;
        }

    } else if (idZona != -1 && id.empty()) { //1 parametro - idZona

        if(terreno->getHabitacao()->getZonas().empty()){
            wInfo << move_to(0, iInfo++) << set_color(4) << "A habitacao ainda nao tem nenhuma zona";
            wInfo << move_to(0, iInfo++) << set_color(4) << "inicilizada. 'znova' para criar uma.";
            return false;
        }

        if(terreno->getHabitacao()->getZona(idZona) == nullptr){
            wInfo << move_to(0, iInfo++) << set_color(4) << "Essa zona nao existe.";
            return false;
        }

    } else if (idZona != -1 && !id.empty()) { //2 parametros - idzona + idSPA

        if(terreno->getHabitacao()->getZonas().empty()){
            wInfo << move_to(0, iInfo++) << set_color(4) << "A habitacao ainda nao tem nenhuma zona";
            wInfo << move_to(0, iInfo++) << set_color(4) << "inicilizada. 'znova' para criar uma.";
            return false;
        }

        if(terreno->getHabitacao()->getZona(idZona) == nullptr){
            wInfo << move_to(0, iInfo++) << set_color(4) << "Essa zona nao existe.";
            return false;
        }

        if(id[0] != 'p' && id[0] != 's' && id[0] != 'a' && id[0] != 'A'){
            wInfo << move_to(0, iInfo++) << set_color(4) << "ID invalido.";
            return false;
        }

        if(id[0] == 'p'){
            if(terreno->getHabitacao()->getZona(idZona)->getProcessadores().empty()){
                wInfo << move_to(0, iInfo++) << set_color(4) << "A zona ainda nao tem nenhum processador.";
                wInfo << move_to(0, iInfo++) << set_color(4) << "'cnovo' para criar um.";
                return false;
            }
            if (terreno->getHabitacao()->getZona(idZona)->getProcessador(id) == nullptr){
                wInfo << move_to(0, iInfo++) << set_color(4) << "Esse processador nao existe.";
                return false;
            }
        }
        else if(id[0] == 's'){
            if(terreno->getHabitacao()->getZona(idZona)->getSensores().empty()){
                wInfo << move_to(0, iInfo++) << set_color(4) << "A zona ainda nao tem nenhum sensor.";
                wInfo << move_to(0, iInfo++) << set_color(4) << "'cnovo' para criar um.";
                return false;
            }
            if (terreno->getHabitacao()->getZona(idZona)->getSensor(id) == nullptr){
                wInfo << move_to(0, iInfo++) << set_color(4) << "Esse sensor nao existe.";
                return false;
            }
        }
        else if(id[0] == 'a' || id[0] == 'A'){
            if(terreno->getHabitacao()->getZona(idZona)->getAparelhos().empty()){
                wInfo << move_to(0, iInfo++) << set_color(4) << "A zona ainda nao tem nenhum aparelho.";
                wInfo << move_to(0, iInfo++) << set_color(4) << "'cnovo' para criar um.";
                return false;
            }
            if (terreno->getHabitacao()->getZona(idZona)->getAparelho(id) == nullptr){
                wInfo << move_to(0, iInfo++) << set_color(4) << "Esse aparelho nao existe.";
                return false;
            }
        }

    }

    return true;
}