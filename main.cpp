#include <QCoreApplication>
#include<iostream>
#include<matrix.h>
#include<qlearning.h>
#include<qlearnigp.h>
#include<recursos.h>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    float e[] = {1, 1, 1, 0, 1, 0, 1, 1,
                 1, 1, 0, 0, 1,	0, 1, 1,
                 1, 1, 1, 1, 1,	0, 0, 1,
                 1, 0, 1, 1, 1, 1, 1, 1,
                 0, 0, 1, 1, 1, 1, 1, 1,
                 1, 0, 1, 1, 1, 0, 1, 2,
                 1, 1, 1, 1, 1, 0, 1, 1,
                 1, 1, 1, 1, 1, 0, 1, 1};

    float r[] = {0,	0, 0, 0, 0,	0, 0, 0,
                 0,	0, 0, 0, 0,	0, 0, 0,
                 0,	0, 0, 0, 0,	0, 0, 0,
                 0,	0, 0, 0, 0,	0, 0, 0,
                 0,	0, 0, 0, 0,	0, 0, 0,
                 0,	0, 0, 0, 0,	0, 0, 80,
                 0,	0, 0, 0, 0,	0, 0, 0,
                 0,	0, 0, 0, 0,	0, 0, 0};
/*
   float e[]={ 1, 1, 1,	1, 1, 1,
               1, 1, 0,	1, 1, 1,
               1, 1, 1,	0, 1, 2};

   float r[]={ 0, 0, 0,	0, 0, 0,
               0, 0, 0,	0, 0, 0,
               0, 0, 0,	0, 0, 5,

                };


*/ Recursos *recursos = new Recursos();
  //  Matrix *entorno = recursos->getMatrix("entorno.csv");
  // Matrix *recompensas = recursos->getMatrix("recompensa.csv");
  // Matrix * entorno = new Matrix(8,8,e);
 //  Matrix * recompensas = new Matrix(8,8,r);
    //entorno->mostrar();
   // recompensas->mostrar();
    int dimension = 100; ///matrix n x n
    Matrix *entorno = recursos->crearEntorno(dimension);
   // entorno->mostrar();
   // system("pause");
     Matrix *recompensas = recursos->crearRecompensas(dimension);
   // recompensas->mostrar();
        // system("pause");
    QlearnigP * q = new QlearnigP(entorno, recompensas);
    q->entrenar(10000);
cout<<"FIN"<<"\a"<<endl;
    return a.exec();
}
