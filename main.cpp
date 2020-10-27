#include <QCoreApplication>
#include<iostream>
#include<matrix.h>
#include<qlearning.h>
#include<qlearnigp.h>
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

*/
    Matrix * entorno = new Matrix(8,8,e);
    Matrix * recompensas = new Matrix(8,8,r);

    QlearnigP * q = new QlearnigP(entorno, recompensas);
    q->entrenar(50);
cout<<"FIN"<<endl;
    return a.exec();
}
