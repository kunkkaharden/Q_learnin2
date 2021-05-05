#ifndef AGENTEPA_H
#define AGENTEPA_H
#include<matrix.h>
#include<entorno.h>
#include<estado.h>
#include<ar.h>

class AgentePa
{
private:
    Matrix * values;
    float e = 0.95; //[0-1] para ver la probabilidad de escoger una accion aleatoria
    float a = 0.99;    //[0-1] factor de aprendizaje  0: no se aprende 1: se olvida lo
    //aprendido anteriormente solo se tiene en cuenta la ultima experiencia
    float y = 0.99;    //[0-1] factor de descuento    0: corto plazo  1: largo plazo
    int rank;

public:
    AgentePa();

  //  int mejorAccion(int estado);
    int index(Estado * e);
    float floatRandom();
  //  int politica(int estado);
    Matrix *getValues() const;
   // Agente(int filas, int columnas);
    int accionRamdon(Matrix *qValues);
    float getA() const;
    float getY() const;
    void disminuirE();
    int mejorAccion(int estado, Matrix *qValues);
    int buscaE(int inicio, int  muestra ,Entorno *e);
    int politica(int estado, Matrix *qValues);
    void entrenar(int rank, int size, int it, Matrix *qValues, Entorno *entorno);
    void entrenarSarsa(int rank, int size, int it, Matrix *qValues, Entorno *entorno);
    void entrenarRL(Algoritmo, int rank, int size, int it, Matrix *qValues, Entorno *entorno);
    void q(int s, int *pasos, Matrix *qValues, Entorno *entorno, int menor, int mayor);
    void sarsa(int s, int *pasos, Matrix *qValues, Entorno *entorno, int menor, int mayor);

};

#endif // AGENTEPA_H
