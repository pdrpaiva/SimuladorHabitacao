//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_SENSOR_H
#define TRABALHO_SENSOR_H
#include <string>

using namespace std;

class Sensor {
private:
    string idSensor;
    static int nextIdSensor;
    string tipo;
    int valor;
public:
    Sensor(const string& tipo, int valor);
    virtual ~Sensor();

    const string &getIdSensor() const;
    const string &getTipo() const;
    void setValor(int valor);
    int getValor() const;
    static void setNextIdSensor(int nextIdSensor);
};


#endif //TRABALHO_SENSOR_H
