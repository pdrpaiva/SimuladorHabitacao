cmake_minimum_required(VERSION 3.23)
project(Trabalho)

set(CMAKE_CXX_STANDARD 20)

add_executable(Trabalho src/main.cpp lib/Terminal.cpp lib/Terminal.h src/Sensores/Sensor.cpp src/Sensores/Sensor.h src/Processadores/ProcessadorRegras.cpp src/Processadores/ProcessadorRegras.h src/Processadores/Regra.cpp src/Processadores/Regra.h src/Aparelhos/Aparelho.cpp src/Aparelhos/Aparelho.h src/Propriedades/Propriedade.cpp src/Propriedades/Propriedade.h src/Zonas/Zona.cpp src/Zonas/Zona.h src/Sensores/TemperaturaSensor.cpp src/Sensores/TemperaturaSensor.h src/Sensores/MovimentoSensor.cpp src/Sensores/MovimentoSensor.h src/Sensores/LuminosidadeSensor.cpp src/Sensores/LuminosidadeSensor.h src/Sensores/RadiacaoSensor.cpp src/Sensores/RadiacaoSensor.h src/Sensores/HumidadeSensor.cpp src/Sensores/HumidadeSensor.h src/Sensores/SomSensor.cpp src/Sensores/SomSensor.h src/Sensores/FumoSensor.cpp src/Sensores/FumoSensor.h src/Habitacoes/Habitacao.cpp src/Habitacoes/Habitacao.h src/Interface/Interface.cpp src/Interface/Interface.h)

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/pdcurses.a)
