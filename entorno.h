#ifndef ENTORNO_H
#define ENTORNO_H
#include<matrix.h>
#include<iostream>
#include<estado_recompensa.h>
#include <cordenadas.h>
#include<vector>
#include<QList>


using namespace std;

class Entorno
{
private:
    Matrix * recompensa;
    Matrix * entorno;
    QList<Cordenadas> * mapa;


public:
    Entorno(Matrix * en , Matrix *  re );
    Estado_Recompensa *  accion(int accion, int est);
    void  hacerMapa();
    Cordenadas * toCordenada(int);
    int toInt(Cordenadas * c);
    void mostrar(int accion, Cordenadas *estado);
    bool posible(int s);
    void mostrar(int accion, int estado);
};

#endif // ENTORNO_H
