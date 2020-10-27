#include "qlearnigp.h"
#include<omp.h>
#include<agente.h>
QlearnigP::QlearnigP(Matrix *en, Matrix *re)
{
    entorno = new Entorno(en,re);
    values = new Matrix(en->columnas() *  en->filas(), 4);
    //  agente = new AgentePa();
}
void QlearnigP::entrenar(int it)
{
    int size = 4, rank = 0 ;
    double inicio , fin;
    AgentePa * a ;
    inicio = omp_get_wtime();
//#pragma omp parallel private(rank, a)
   // {

      //  size = omp_get_num_threads();
       // rank = omp_get_thread_num();
        a = new AgentePa();
        a->entrenar(rank, size, it,values,entorno);
        delete a;
  //  }
    fin = omp_get_wtime();
    cout<<"tiempo: "<<fin - inicio<<endl;
}

