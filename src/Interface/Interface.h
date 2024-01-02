//
// Created by Utilizador on 28/10/2023.
//

#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "../../lib/Terminal.h"
#include "../Terreno/Terreno.h"

using namespace std;
using namespace term;

class Interface{
private:
    Terreno* terreno;

    Terminal &terminal;
    Window wComandos;
    Window wInfo;
    Window wHabitacao;
    vector <Window> wZonas;

    //habitacao
    bool existeHab = false;
    int instancia = 0;

    //zonas
    vector <int> idZonas;

    //info / outros
    int iInfo = 2; //incrementa o y do moveto wInfo
    bool fichAberto = false;
    bool saida = false;

public:
    Interface(Terminal &t, Terreno* terreno);
    ~Interface();
    //Comandos
    void processaComandos();
    void executaComandos(const string& comando);
    void carregaComandos(const string& nomeFich);
    void sintaxe(const string& s);
    void sintaxe (const string& s, const string& s2);
    void processa();
    bool Sair() const;
    void constroiHabitacao(int nLinhas,int nColunas);
    void avanca(int it);
    void constroiZona(int nLinhas,int nColunas);
    void limpaZona(int idZona);
    void limpaLogs();
    void atualizaZona(int idZona);

    //verificacoes
    bool existeZSPA(const int &idZona = -1, const std::string &id = "");
};
#endif //TRABALHO_COMANDOS_H