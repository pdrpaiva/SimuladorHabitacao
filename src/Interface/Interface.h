//
// Created by Utilizador on 28/10/2023.
//

#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H

#include <string>
#include <vector>
#include "../../lib/Terminal.h"
using namespace std;
using namespace term;

class Interface{
private:
    Terminal &terminal;
    Window wComandos;
    Window wInfo;
    Window wHabitacao;
    vector <Window> wZonas;
    int iInfo = 2; //incrementa o y do moveto wInfo
    bool fichAberto = false;
    bool saida = false;
    bool existeHab = false;
    int instancia = 0;
public:
    Interface(Terminal &t);
    //Comandos
    void processaComandos();
    void executaComandos(const string& comando);
    void carregaComandos(const string& nomeFich);
    void sintaxe(const string& s);
    void sintaxe (const string& s, const string& limite);
    void processa();
    bool Sair() const;
    void criaHabitacao(int nLinhas,int nColunas);
    void criaZona(int nLinhas,int nColunas);
};
#endif //TRABALHO_COMANDOS_H