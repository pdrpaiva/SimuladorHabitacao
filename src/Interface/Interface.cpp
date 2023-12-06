#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "../../lib/Terminal.h"
#include "Interface.h"
using namespace std;
using namespace term;

Interface::Interface(Terminal &t) : terminal(t), wComandos(0, 0, 120, 6), wInfo(121, 0, 47, 43), wHabitacao(0,6,120,37){
    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }
    wInfo << move_to(0, 0) << set_color(3) << "Logs:";
}

void Interface::processaComandos() {
    wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
    wComandos << move_to(0, 2) << set_color(0) << ">> ";

    string comando;
    saida = false;
    wComandos >> comando;
    //getline(cin, comando);
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

    if(cmd == "prox") {
        string extra;
        string s = "prox";
        if(iss >> extra){
            sintaxe(s);
        }
        else{
            processa();
            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
            wInfo << move_to(0, iInfo++) << set_color(10) << "Avancou 1 instante.";
            return;
        }
    }
    else if (cmd == "avanca") {
        int n;
        string s = "avanca <n>";
        if (iss >> n) {
            string extra;
            if (iss >> extra) {
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Avancou [" << n << "] instantes.";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "hnova") {
        int numLinhas, numColunas;
        string s = "hnova <num linhas> <num colunas> ";
        string limite = ", com 2 <= num linhas <= 4 e 2 <= num colunas <= 4";
        if (iss >> numLinhas >> numColunas) {
            string extra;
            if (iss >> extra || numLinhas < 2 || numLinhas > 4 || numColunas < 2 || numColunas > 4) {
                sintaxe(s,limite);
            } else {
                processa();

                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                if(jaExistiuHab){
                    wInfo << move_to(0, iInfo++) << set_color(4) << "Habitacao atual foi apagada.";
                }
                wInfo << move_to(0, iInfo++) << set_color(10) << "Criada nova habitacao.";

                wZonas.clear();
                criaHabitacao(numLinhas,numColunas);

                jaExistiuHab = true;
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if(cmd == "hrem") {
        string extra;
        string s = "hrem";
        if(iss >> extra){
            sintaxe(s);
        } else{
            processa();
            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
            wInfo << move_to(0, iInfo++) << set_color(10) << "Habitacao eliminada.";
            return;
        }
    }
    else if (cmd == "znova") {
        int linha, coluna;
        string s = "znova <linha> <coluna>";
        string limite = ", com 2 <= linha <= 4 e 2 <= coluna <= 4";
        if (iss >> linha >> coluna){
            string extra;
            if(iss >> extra || linha < 2 || linha > 4 || coluna < 2 || coluna > 4){
                sintaxe(s,limite);
            } else{
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Criada uma nova zona. Linha [" << linha << "] Coluna [" << coluna << "]";
                return;
            }
        }else {
            sintaxe(s);
        }
    }
    else if (cmd == "zrem"){
        int idZona;
        string s = "zrem <ID zona>";
        if(iss >> idZona){
            string extra;
            if(iss >> extra){
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Zona [" << idZona << "] eliminada.";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if(cmd == "zlista"){
        string extra;
        string s = "zlista";
        if(iss >> extra){
            sintaxe(s);
        } else{
            processa();
            wInfo << move_to(0, iInfo++) << set_color(0) << comando;
            wInfo << move_to(0, iInfo++) << set_color(10) << "Zonas da habitacao:";
            return;
        }
    }
    else if (cmd == "zcomp") {
        int idZona;
        string s = "zcomp <ID zona>";
        if(iss >> idZona){
            string extra;
            if(iss >> extra){
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Componentes da zona [" << idZona << "]:";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "zprops") {
        int idZona;
        string s = "zprops <ID zona>";
        if(iss >> idZona){
            string extra;
            if(iss >> extra){
                sintaxe(s);
            } else {
                processa();
                wInfo << move_to(0, iInfo++) << set_color(0) << comando;
                wInfo << move_to(0, iInfo++) << set_color(10) << "Propriedades da zona [" << idZona << "]:";
                return;
            }
        } else {
            sintaxe(s);
        }
    }
    else if (cmd == "pmod") {
        int idZona;
        string nome;
        int valor;
        string s = "pmod <ID zona> <nome> <valor>";
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
        string s = "cnovo <ID zona> <s | p | a> <tipo | comando>";
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
        string s = "crem <ID zona> <s | p | a> <ID>";
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
        string s = "rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]";

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
        string s = "pmuda <ID zona> <ID proc. regras> <novo comando>";

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
        string s = "rlista <ID zona> <ID proc. regras>";
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
        string s = "rrem <ID zona> <ID proc. regras> <ID regra>";
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
        string s = "asoc <ID zona> <ID proc. regras> <ID aparelho>";
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
        string s = "ades <ID zona> <ID proc. regras> <ID aparelho>";
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
        string s = "acom <ID zona> <ID aparelho> <comando>";

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
        string s = "psalva <ID zona> <ID proc. regras> <nome>";

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
        string s = "prepoe <nome>";

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
        string s = "prem <nome>";

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
        string s = "plista";

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
        string s = "exec <nome de ficheiro>";
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
        string s = "prox";
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
    wComandos << move_to(0, 2) << set_color(4) << "Sintaxe invalida. Uso correto: " << s;
    wComandos << move_to(0, 3) << set_color(0) << "Pressione qualquer tecla para continuar . . .";
    if(!fichAberto)
        wComandos.getchar();
    wComandos.clear();
}

void Interface::sintaxe(const string &s, const string &limite) {
    wComandos << move_to(0, 0) << set_color(3) << "Comandos:";
    wComandos << move_to(0, 2) << set_color(4) << "Sintaxe invalida. Uso correto: " << s << limite;
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

void Interface::criaHabitacao(int nLinhas, int nColunas) {
    //wHabitacao(x 0 ,y 6,w 120,h 37)
    int x, y = 8, w = 27, h = 17;

    for (int i = 0; i < nLinhas; i++) {
        x = 3;
        for (int j = 0; j < nColunas; j++) {
            wZonas.emplace_back(x, y, w, h,true);
            x += 29;
        }
        y += 17;
    }
}

