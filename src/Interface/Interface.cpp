#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "../../lib/Terminal.h"
#include "Interface.h"
using namespace std;
using namespace term;

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
        iInfo = 2;
        wInfo.clear();
        wInfo << move_to(0, 0) << set_color(3) << "Logs:";
    }

    string naoExisteHab = "Nao existe nenhuma habitacao neste momento. 'hnova' para criar uma.";

    if(cmd == "prox") {
        string extra;
        string s = "Uso correto: prox";
        if(iss >> extra){
            sintaxe(s);
        }
        else{
            processa();
            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
            wInfo << move_to(0, iInfo++) << set_color(10) << "Avancou 1 instante.";
            terreno->getHabitacao()->setInstancia(terreno->getHabitacao()->getInstancia() + 1);
            return;
        }
    }
    else if (cmd == "avanca") {
        int n;
        string s = "Uso correto: avanca <n>";
        if (iss >> n) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Avancou [" << n << "] instantes.";
                terreno->getHabitacao()->setInstancia(terreno->getHabitacao()->getInstancia() + n);
                return;
            }
        } else {
            sintaxe(s);
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
        string extra;
        string s = "Uso correto: hrem";
        if(iss >> extra){
            sintaxe(s);
        } else{
            processa();
            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
            wInfo << move_to(0, iInfo++) << set_color(10) << "Habitacao eliminada.";

            delete terreno->getHabitacao();
            wHabitacao.clear();
            for (auto& w : wZonas) {
                w.clear();
            }
            wZonas.clear();

            existeHab = false;

            return;
        }
    }
    else if (cmd == "znova") {
        int linha, coluna;
        string s = "Uso correto: znova <linha> <coluna>";
        string limite = ", com 1 <= linha <= 4 e 1 <= coluna <= 4";
        if (iss >> linha >> coluna){
            string extra;
            if(iss >> extra || linha < 1 || linha > 4 || coluna < 1 || coluna > 4){
                sintaxe(s,limite);
            } else{
                if(!existeHab){
                    sintaxe(naoExisteHab);
                }
                else{
                    processa();
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    constroiZona(linha,coluna);
                    return;
                }
            }
        }else {
            sintaxe(s);
        }
    }
    else if (cmd == "zrem"){
        int idZona;
        string s = "Uso correto: zrem <ID zona>";
        if(iss >> idZona){
            string extra;
            if(iss >> extra){
                sintaxe(s);
            } else {
                if(!existeHab){
                    sintaxe(naoExisteHab);
                }
                else {
                    processa();
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;

                    switch(terreno->getHabitacao()->removeZona(idZona)){
                        case 1: //valido
                            //wZonas[idZona-1].clear();
                            for(int i = 0; i < idZonas.size() ; i++){
                                if(idZonas[i] == idZona){
                                    wZonas[i].clear();
                                    break;
                                }
                            }
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
            }
        } else {
            sintaxe(s);
        }
    }
    else if(cmd == "zlista"){
        string extra;
        string s = "Uso correto: zlista";
        if(iss >> extra){
            sintaxe(s);
        } else{
            if(!existeHab){
                sintaxe(naoExisteHab);
            }
            else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Zonas da habitacao:";
                return;
            }
        }
    }
    else if (cmd == "zcomp") {
        int idZona;
        string s = "Uso correto: zcomp <ID zona>";
        if(iss >> idZona){
            string extra;
            if(iss >> extra){
                sintaxe(s);
            } else {
                if(!existeHab){
                    sintaxe(naoExisteHab);
                }
                else {
                    processa();
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    wInfo << move_to(0, iInfo++) << set_color(10) << "Componentes da zona [" << idZona << "]:";
                    return;
                }
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "zprops") {
        int idZona;
        string s = "Uso correto: zprops <ID zona>";
        if(iss >> idZona){
            string extra;
            if(iss >> extra){
                sintaxe(s);
            } else {
                if(!existeHab){
                    sintaxe(naoExisteHab);
                }
                else {
                    processa();
                    wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                    wInfo << move_to(0, iInfo++) << set_color(10) << "Propriedades da zona [" << idZona << "]:";
                    return;
                }
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "pmod") {
        int idZona;
        string nome;
        int valor;
        string s = "Uso correto: pmod <ID zona> <nome> <valor>";
        if (iss >> idZona >> nome >> valor){
            string extra;
            if(iss >> extra){
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Valor da propriedade [" << nome << "] da zona [" << idZona << "]";
                wInfo << move_to(0, iInfo++) << set_color(10) << "alterado para [" << valor << "].";
                return;
            }
        }else {
            sintaxe(s);
        }
    }
    else if (cmd == "cnovo") {
        int idZona;
        char spa;
        string tipoComando;
        string s = "Uso correto: cnovo <ID zona> <s | p | a> <tipo | comando>";
        if(iss >> idZona >> spa >> tipoComando){
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                if (spa != 's' && spa != 'p' && spa != 'a'){
                    sintaxe(s);
                } else{
                    if (spa == 'p'){
                        if (tipoComando == "liga" || tipoComando == "desliga"){
                            processa();
                            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                            wInfo << move_to(0, iInfo++) << set_color(10) << "Adicionado um processador a zona [" << idZona << "].";

                            return;
                        }
                        else {
                            sintaxe(s);
                        }
                    }
                    else if (spa == 'a') {
                        processa();
                        wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                        wInfo << move_to(0, iInfo++) << set_color(10) << "Adicionado o aparelho [" << tipoComando << "] a zona [" << idZona << "].";
                        return;
                    }
                    else if (spa == 's') {
                        processa();
                        wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                        wInfo << move_to(0, iInfo++) << set_color(10) << "Adicionado o sensor [" << tipoComando << "] a zona [" << idZona << "].";
                        return;
                    }
                }
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "crem") {
        int idZona,id;
        char spa;
        string s = "Uso correto: crem <ID zona> <s | p | a> <ID>";
        if(iss >> idZona >> spa >> id) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                if (spa != 's' && spa != 'p' && spa != 'a'){
                    sintaxe(s);
                } else{
                    if (spa == 'p'){
                        processa();
                        wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                        wInfo << move_to(0, iInfo++) << set_color(10) << "Removido o processador [" << id << "] da zona [" << idZona << "].";
                        return;
                    }
                    else if (spa == 'a') {
                        processa();
                        wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                        wInfo << move_to(0, iInfo++) << set_color(10) << "Removido o aparelho [" << id << "] da zona [" << idZona << "].";
                        return;
                    }
                    else if (spa == 's') {
                        processa();
                        wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                        wInfo << move_to(0, iInfo++) << set_color(10) << "Removido o sensor [" << id << "] da zona [" << idZona << "].";
                        return;
                    }
                }
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "rnova") {
        int idZona,idProcRegras,idSensor,x,y;
        string regra,extra;
        bool encontrou = false; //bool para saber se encontrou uma das regras

        string arrayRegras[] = {"igual_a","menor_que","maior_que","entre","fora"};
        string s = "Uso correto: rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]";

        //rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]
        if(iss >> idZona >> idProcRegras >> regra >> idSensor){
            for (const auto& valor : arrayRegras) {
                if (regra == valor) {
                    encontrou = true;
                    break;
                }
            }
            if(!encontrou){
                char resposta;
                if(!fichAberto){
                    do{
                        wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
                        wComandos << move_to(0, 2) << set_color(4) << "Sintaxe invalida. Essa regra nao existe. ";
                        wComandos << move_to(0, 3) << set_color(0) << "Pretende ver as regras dos processadores? (S/N)";
                        resposta = wComandos.getchar();
                        if(resposta == 'S' || resposta == 's'){
                            wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
                            wComandos << move_to(0, 2) << set_color(0) << "Regras atuais: igual_a (x) , menor_que (x) , maior_que (x), entre (x,y) , fora (x,y)";
                            wComandos << move_to(0, 3) << set_color(0) << "Pressione qualquer tecla para continuar . . .    ";
                            wComandos.getchar();
                            wComandos.clear();
                            return;
                        }
                        else if (resposta == 'N' || resposta == 'n'){
                            wComandos.clear();
                            return;
                        }
                    }while(resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');
                }
            }
            else{
                if(regra == "entre" || regra == "fora"){
                    if(iss >> x >> y){
                        if (iss >> extra) {
                            sintaxe(s);
                        }
                        else {
                            processa();
                            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                            wInfo << move_to(0, iInfo++) << set_color(10) << "Regra [" << regra << "(x:" << x << " y:" << y <<")] adicionada";
                            wInfo << move_to(0, iInfo++) << set_color(10) << "ao processador [" << idProcRegras << "] e associada ao sensor [" << idSensor <<"] ";
                            wInfo << move_to(0, iInfo++) << set_color(10) << "da zona [" << idZona << "]";
                            return;
                        }
                    }
                    else {
                        sintaxe(s);
                    }
                }
                else {
                    if(iss >> x) {
                        if (iss >> extra) {
                            sintaxe(s);
                        } else {
                            processa();
                            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                            wInfo << move_to(0, iInfo++) << set_color(10) << "Regra [" << regra << "(x:" << x <<")] adicionada";
                            wInfo << move_to(0, iInfo++) << set_color(10) << "ao processador [" << idProcRegras << "] e associada ao sensor [" << idSensor <<"] ";
                            wInfo << move_to(0, iInfo++) << set_color(10) << "da zona [" << idZona << "]";
                            return;
                        }
                    }
                    else {
                        sintaxe(s);
                    }
                }
            }
        }
        else {
            sintaxe (s);
        }
    }
    else if (cmd == "pmuda") {
        int idZona,idProcRegras;
        string pcomando;
        string s = "Uso correto: pmuda <ID zona> <ID proc. regras> <novo comando>";

        if(iss >> idZona >> idProcRegras >> pcomando) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Comando do processador [" << idProcRegras << "] da zona [" << idZona << "] ";
                wInfo << move_to(0, iInfo++) << set_color(10) << "alterado para [" << pcomando << "].";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "rlista") {
        int idZona,idProcRegras;
        string s = "Uso correto: rlista <ID zona> <ID proc. regras>";
        if(iss >> idZona >> idProcRegras) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Comandos do processador [" << idProcRegras << "] da zona [" << idZona << "]:";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "rrem") {
        int idZona,idProcRegras,idRegra;
        string s = "Uso correto: rrem <ID zona> <ID proc. regras> <ID regra>";
        if(iss >> idZona >> idProcRegras >> idRegra) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Regra [" << idRegra << "] removida do processador [" << idProcRegras << "] ";
                wInfo << move_to(0, iInfo++) << set_color(10) << "da zona [" << idZona <<"].";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "asoc") {
        int idZona,idProcRegras,idAparelho;
        string s = "Uso correto: asoc <ID zona> <ID proc. regras> <ID aparelho>";
        if(iss >> idZona >> idProcRegras >> idAparelho) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Processador [" << idProcRegras << "] associado ao aparelho [" << idAparelho << "] ";
                wInfo << move_to(0, iInfo++) << set_color(10) << "da zona [" << idZona << "].";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "ades") {
        int idZona,idProcRegras,idAparelho;
        string s = "Uso correto: ades <ID zona> <ID proc. regras> <ID aparelho>";
        if(iss >> idZona >> idProcRegras >> idAparelho) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Processador [" << idProcRegras << "] desassociado ao aparelho [" << idAparelho << "] ";
                wInfo << move_to(0, iInfo++) << set_color(10) << "da zona [" << idZona << "].";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "acom") {
        int idZona,idAparelho;
        string acomando;
        string s = "Uso correto: acom <ID zona> <ID aparelho> <comando>";

        if(iss >> idZona >> idAparelho >> acomando) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Comando [" << acomando << "] enviado ao aparelho [" << idAparelho << "] ";
                wInfo << move_to(0, iInfo++) << set_color(10) << "da zona [" << idZona << "].";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "psalva") {
        int idZona,idProcRegras;
        string nome;
        string s = "Uso correto: psalva <ID zona> <ID proc. regras> <nome>";

        if(iss >> idZona >> idProcRegras >> nome) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Regras do processador [" << idProcRegras << "] da zona [" << idZona << "] ";
                wInfo << move_to(0, iInfo++) << set_color(10) << "guardadas [" << nome << "] na memoria.";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "prepoe") {
        string nome;
        string s = "Uso correto: prepoe <nome>";

        if(iss >> nome) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Processador [" << nome << "] reposto com sucesso.";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "prem") {
        string nome;
        string s = "Uso correto: prem <nome>";

        if(iss >> nome) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Copia [" << nome << "] com as regras do processador ";
                wInfo << move_to(0, iInfo++) << set_color(10) << "eliminada da memoria.";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if(cmd == "plista") {
        string extra;
        string s = "Uso correto: plista";

        if(iss >> extra){
            sintaxe(s);
        }
        else{
            processa();
            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
            wInfo << move_to(0, iInfo++) << set_color(10) << "Copias de processadores guardadas em memoria:";
            return;
        }
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
    else if (cmd == "clearLogs") {
        string extra;
        string s = "Uso correto: clearLogs";
        if(iss >> extra){
            sintaxe(s);
        }
        else{
            processa();
            wInfo.clear();
            wInfo << move_to(0, 0) << set_color(3) << "Logs:";
            iInfo = 2;
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
    //wHabitacao(x 0 ,y 6,w 120,h 37)
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

void Interface::constroiZona(int linha, int coluna) {
    int x = 0, y = 0;

    int numColunas = terreno->getHabitacao()->getHabColunas();
    int posZona = (linha - 1) * numColunas + (coluna - 1);

    int id = terreno->getHabitacao()->getZonas().size();

    idZonas[posZona] = id + 1;

    switch(terreno->getHabitacao()->adicionaZona(linha,coluna)) {
        case 1: //valido
            wInfo << move_to(0, iInfo++) << set_color(10) << "Criada uma nova zona. Linha [" << linha << "] Coluna [" << coluna << "]";
            wZonas[posZona] << move_to(x, y) << set_color(0) << "ID: " << terreno->getHabitacao()->getZonas()[id]->getIdZona();
            wZonas[posZona] << move_to(x, y+1) << set_color(0) << "S: " ;
            wZonas[posZona] << move_to(x, y+2) << set_color(0) << "P: " ;
            wZonas[posZona] << move_to(x, y+3) << set_color(0) << "A: " ;
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

