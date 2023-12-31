//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_APARELHO_H
#define TRABALHO_APARELHO_H
#include <string>
#include <cctype>
#include <sstream>

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
    int counterLigado = 0;
public:
    Aparelho(Zona* zona, const string& tipo);
    virtual ~Aparelho();

    virtual bool recebeComando(const string& comando);

    virtual void aoLigar() = 0;
    virtual void aoDesligar() = 0;
    virtual void atualiza() = 0;

    //getters e setters
    const string &getIdAparelho() const;
    const string &getTipo() const;
    bool isLigado() const;
    void setLigado();
    void setDesligado();
    int getCounterLigado() const;
    void incrementaCounterLigado();
    void resetCounterLigado();
    Zona *getZona() const;
    const string &getComando() const;
    void setComando(const string &comando);
    static void setNextIdAparelho(int nextIdAparelho);
};


#endif //TRABALHO_APARELHO_H
