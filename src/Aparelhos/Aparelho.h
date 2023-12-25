//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_APARELHO_H
#define TRABALHO_APARELHO_H
#include <string>

using namespace std;

class Aparelho {
private:
    int idAparelho;
    static int nextIdAparelho;
    string tipo;
    bool ligado;
public:
    Aparelho(const string& tipo);
    ~Aparelho();

    //getters e setters
    const string &getTipo() const;
    bool isLigado() const;
    void setLigado(bool ligado);
    int getIdAparelho() const;
};


#endif //TRABALHO_APARELHO_H
