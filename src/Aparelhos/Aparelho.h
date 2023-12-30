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
    bool ligado;
    Zona* zona;
public:
    Aparelho(Zona* zona, const string& tipo);
    virtual ~Aparelho();

    bool enviaComando(const string& comando);

    virtual void aoLigar();
    virtual void aoDesligar();

    //getters e setters
    const string &getIdAparelho() const;
    const string &getTipo() const;
    bool isLigado() const;
    void setLigado(bool ligado);
    void setDesligado(bool ligado);
    Zona *getZona() const;
};


#endif //TRABALHO_APARELHO_H
