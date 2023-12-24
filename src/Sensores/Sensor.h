//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_SENSOR_H
#define TRABALHO_SENSOR_H


class Sensor {
private:
    int idSensor;
    static int nextIdSensor;
public:
    Sensor();
    int getIdSensor() const;
};


#endif //TRABALHO_SENSOR_H
