#ifndef Q_LEARNING_H
#define Q_LEARNING_H
#include<recompensa_estado.h>
#include<stdlib.h>
class Q_Learning
{
private:
    float e = 0.50; //[0-1] para ver la probabilidad de escoger una accion aleatoria
    float a = 0.5;    //[0-1] factor de aprendizaje  0: no se aprende 1: se olvida lo
    //aprendido anteriormente solo se tiene en cuenta la ultima experiencia
    float y = 0.5;    //[0-1] factor de descuento    0: corto plazo  1: largo plazo
    int cantEstados;
    int cantAcciones;
    Recompensa_Estado *matrix;
public:

    ~Q_Learning();
 //   Q_Learning();
    int politica(int estado);
    Recompensa_Estado get(int estado, int accion);
    float getE() const;
    void setE(float value);
    int accionRamdon(int estado);
    float floatRandom();
    int mejorAccion(int estado);
    void entrenar(int inicio, int fin, int iteraciones);
    void addEstadoAccion(int estado, int accion, Recompensa_Estado *value);
    Q_Learning(int estados, int acciones);
    void mostrar();
  //  Recompensa_Estado get(int estado, int accion);
};

#endif // Q_LEARNING_H
