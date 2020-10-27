#ifndef QLEARNIGP_H
#define QLEARNIGP_H
#include<matrix.h>
#include<entorno.h>
#include<agentepa.h>

class QlearnigP
{
private:
    Matrix * values;
    Entorno * entorno;
    AgentePa * agente;
public:

    void entrenar(int it);
    QlearnigP(Matrix *en, Matrix *re);
};

#endif // QLEARNIGP_H
