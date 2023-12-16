//
// Created by Utilizador on 28/10/2023.
//

#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H

#include <string>
#include <vector>
#include "../../lib/Terminal.h"
//#include "../Habitacoes/Habitacao.h"
#include "../Habitacoes/GestorHabitacao.h"

using namespace std;
using namespace term;

class Interface{
private:
    GestorHabitacao* gestorHabitacao;

    Terminal &terminal;
    Window wComandos;
    Window wInfo;
    Window wHabitacao;
    vector <Window> wZonas;

    //habitacao
    bool existeHab = false;
    int instancia = 0;

    //info / outros
    int iInfo = 2; //incrementa o y do moveto wInfo
    bool fichAberto = false;
    bool saida = false;

public:
    Interface(Terminal &t,GestorHabitacao* gestorHabitacao);
    ~Interface();
    //Comandos
    void processaComandos();
    void executaComandos(const string& comando);
    void carregaComandos(const string& nomeFich);
    void sintaxe(const string& s);
    void sintaxe (const string& s, const string& s2);
    void processa();
    bool Sair() const;
    void desenhaHabitacao(int nLinhas,int nColunas);
    void desenhaZona(int nLinhas,int nColunas);
};
#endif //TRABALHO_COMANDOS_H