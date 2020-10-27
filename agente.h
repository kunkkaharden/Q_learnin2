#ifndef AGENTE_H
#define AGENTE_H
#include<matrix.h>
#include<entorno.h>
#include<estado.h>
class Agente
{
private:
    Matrix * values;
    float e = 0.95; //[0-1] para ver la probabilidad de escoger una accion aleatoria
    float a = 0.5;    //[0-1] factor de aprendizaje  0: no se aprende 1: se olvida lo
    //aprendido anteriormente solo se tiene en cuenta la ultima experiencia
    float y = 0.5;    //[0-1] factor de descuento    0: corto plazo  1: largo plazo

public:
  //  Agente();

    int mejorAccion(int estado);
    int index(Estado * e);
    float floatRandom();
    int politica(int estado);
    Matrix *getValues() const;
    Agente(int filas, int columnas);
    int accionRamdon();
    float getA() const;
    float getY() const;
   void disminuirE();
};

#endif // AGENTE_H
