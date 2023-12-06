//
// Created by Utilizador on 28/10/2023.
//

#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H
#endif //TRABALHO_COMANDOS_H
#include <string>
#include "../../lib/Terminal.h"
using namespace std;
using namespace term;

class Interface{
private:
    Terminal &terminal;
    Window wComandos;
    Window wInfo;
    Window wHabitacao;
    int iInfo = 2; //incrementa o y do moveto wInfo
    bool fichAberto = false; //flag para ler o ficheiro
public:
    Interface(Terminal &t);
    //Comandos
    void processaComandos();
    void executaComandos(const string& comando);
    void carregaComandos(const string& nomeFich);
    void sintaxe(const string& s);
    void sintaxe (const string& s, const string& limite);
    void processa();
};