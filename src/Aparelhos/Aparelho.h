//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_APARELHO_H
#define TRABALHO_APARELHO_H
#include <string>
#include <cctype>

using namespace std;

class Aparelho {
private:
    string idAparelho;
    static int nextIdAparelho;
    string tipo;
    bool ligado;
public:
    Aparelho(const string& tipo);
    virtual ~Aparelho();

    //getters e setters
    const string &getIdAparelho() const;
    const string &getTipo() const;
    bool isLigado() const;
    void setLigado();
    void setDesligado();
};


#endif //TRABALHO_APARELHO_H
