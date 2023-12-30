//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_APARELHO_H
#define TRABALHO_APARELHO_H
#include <string>
#include <cctype>

using namespace std;
class Zona;

class Aparelho {
private:
    string idAparelho;
    static int nextIdAparelho;
    string tipo;
    string comando;
    bool ligado;
    Zona* zona;
public:
    Aparelho(Zona* zona, const string& tipo);
    virtual ~Aparelho();

    bool recebeComando(const string& comando);

    virtual void aoLigar() = 0;
    virtual void aoDesligar() = 0;

    //getters e setters
    const string &getIdAparelho() const;
    const string &getTipo() const;
    void setLigado();
    void setDesligado();
    Zona *getZona() const;
    const string &getComando() const;
};


#endif //TRABALHO_APARELHO_H
