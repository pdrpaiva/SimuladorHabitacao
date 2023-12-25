//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_SENSOR_H
#define TRABALHO_SENSOR_H
#include <string>

using namespace std;

class Sensor {
private:
    int idSensor;
    static int nextIdSensor;
    string tipo;
public:
    Sensor(const string& tipo);
    ~Sensor();
    int getIdSensor() const;
    const string &getTipo() const;
};


#endif //TRABALHO_SENSOR_H
