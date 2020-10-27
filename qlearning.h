#ifndef QLEARNING_H
#define QLEARNING_H

#include<agente.h>
#include<entorno.h>

class Qlearning
{
private:
    Agente * agente;
    Entorno * entorno;
public:
    Qlearning(Matrix * en, Matrix * re);
    void entrenar(int it);
    void entrenarP();
};

#endif // QLEARNING_H
