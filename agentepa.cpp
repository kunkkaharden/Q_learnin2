#include "agentepa.h"
#include<omp.h>
#include<entorno.h>
#include<matrix.h>
#include<ar.h>
AgentePa::AgentePa()
{

}

float AgentePa::getA() const
{
    return a;
}


float AgentePa::getY() const
{
    return y;
}

void AgentePa::disminuirE()
{
    if(e > 0.10){
        e -= 0.02;
    }

}



int AgentePa::mejorAccion(int estado, Matrix * qValues){
    float valor = qValues->num(estado, 0) ;
    float temporal;
    int accion = 0 ;
    int cantI = 1; // cantidad de valores iguales
    for(int i =1; i < qValues->columnas(); i++){
        temporal = qValues->num(estado, i) ;
        if(temporal > valor){
            valor = temporal;
            accion = i;

        }else  if(temporal == valor){
            cantI++;
        }
    }

    if(cantI == qValues->columnas()){
        accion = accionRamdon(qValues);

    }

    return accion  ;
}



int AgentePa ::politica(int estado, Matrix * qValues)
{
    int accion = -1;
    float ramdon = floatRandom();
    if(ramdon < e){
        accion = accionRamdon(qValues);
    }else{
        accion = mejorAccion(estado, qValues);
    }
    return accion;
}

float AgentePa:: floatRandom(){

    float a = 1+ rand() %9;
    float b = 1 + rand() % 9 ;
    float num = 0 +( a/10) + (b / 100) ;
    return num;
}
int AgentePa::accionRamdon(Matrix * qValues)
{
    return   0+ rand() % qValues->columnas();


}
void AgentePa:: entrenar(int rank , int size, int it , Matrix * qValues , Entorno * entorno){
    this->rank = rank;
    int menor ,  mayor; //rango inferior y superior de los grupos

    int muestra = qValues->filas() / (size -1);
    if(rank == 0){
        e = 0.30;
        menor =0;
        mayor = qValues->filas();
    }else if(rank == size - 1){
        menor = (rank -1) * muestra ;
        mayor = qValues->filas();
    }else{
        menor = (rank -1 )* muestra ;
        mayor = (rank ) * muestra ;
    }

    int s = 0; // estado actual
    float r;   // recompensa
    int ac;    // accion

    int sp;   //estado siguiente
    int pasos =0;  // cantidad de pasos
    Estado_Recompensa * est = new Estado_Recompensa(0,0);
    bool bandera ; //para el fin de episodio
    for(int i =0; i < it ; i++){
        pasos =0;
        s =0;
        if(rank !=0){
            s = buscaE(menor,muestra,entorno);
        }

        bandera = true;
        while(bandera){
            pasos++;
            ac = politica(s,qValues);
            delete est;
            est = entorno->accion(ac,s);

            sp = est->getEstado()->getIndex();
            r = est->getRecompensa();
//#pragma omp critical
            qValues->num(qValues->num(s,ac) +
                         a *
                         (r + y * qValues->num(sp,mejorAccion(sp,qValues))
                          - qValues->num(s,ac) ),s,ac) ;

            s = sp;
          /* if(rank == 0){
                entorno->mostrar(ac,s);
                system("pause");

            }*/
            if(est->getEstado()->isTerminal() == true || s < menor || s > mayor){
                bandera = false;
                disminuirE();
                //   cout<<"encontro meta"<<endl;
                //  agente->getValues()->mostrar();
                //   system("pause");
            }
            if(pasos > 2000){
                bandera = false;


                //   cout<<"Demaciados pasos  >2000"<<endl;
            }
        }

        if(rank ==0)
            cout<<"pasos: "<<pasos<<" por "<<rank<<endl;
        //  system("pause");
    }
    //****************************************

}

void AgentePa::entrenarRL(Algoritmo alg, int rank, int size, int it, Matrix *qValues, Entorno *entorno)
{

    this->rank = rank;
    int menor ,  mayor , muestra; //rango inferior y superior de los grupos


    if(size == 1){
        menor =0;
        muestra = mayor = qValues->filas();

    }else if(size > 2){
        muestra = qValues->filas() / (size -1);
        if(this->rank == 0){
            e = 0.30;
            menor =0;
            mayor = qValues->filas();
        }else if(this->rank == size - 1){
            menor = (rank -1) * muestra ;
            mayor = qValues->filas();
        }else{
            menor = (rank -1 )* muestra ;
            mayor = (rank ) * muestra ;
        }

    }


    int s = 0; // estado actual
    int pasos =0;  // cantidad de pasos

    for(int i =0; i < it ; i++){
        pasos =0;
        s =0;
        if(rank !=0){
            s = buscaE(menor,muestra,entorno);
        }
        if(alg == Q_Learning)
            q(s,&pasos,qValues,entorno,menor,mayor);
        else if(alg == Sarsa){
            sarsa(s,&pasos,qValues,entorno,menor,mayor);
        }

        if(this->rank == 0)

            cout<<"pasos: "<<pasos<<" por "<<rank<<endl;
        //  system("pause");
    }

}

//Q_Learning
void AgentePa::q(int s,int *pasos, Matrix *qValues,Entorno *entorno,int menor , int mayor)
{
    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    Estado_Recompensa * est = new Estado_Recompensa(0,0);
    bool bandera = true; //para el fin de episodio
    //**************
    while(bandera){
        (*pasos)++;

        ac = politica(s,qValues);
        delete est;
        est = entorno->accion(ac,s);

        sp = est->getEstado()->getIndex();
        r = est->getRecompensa();


        #pragma omp critical
        qValues->num(qValues->num(s,ac) +
                     a *
                     (r + y * qValues->num(sp,mejorAccion(sp,qValues))
                      - qValues->num(s,ac) ),s,ac) ;

        s = sp;
         /*if(rank == 0){
            entorno->mostrar(ac,s);
            cout<<"rank: "<<rank<<endl;
            system("pause");

        }*/
        if(est->getEstado()->isTerminal() == true || s < menor || s > mayor){
            bandera = false;
            disminuirE();
            //   cout<<"encontro meta"<<endl;
            //  agente->getValues()->mostrar();
            //   system("pause");
        }
        if((*pasos) > 500000){
            bandera = false;


            //   cout<<"Demaciados pasos  >2000"<<endl;
        }

    }

}

void AgentePa::sarsa(int s,int *pasos, Matrix *qValues,Entorno *entorno,int menor , int mayor)
{
    float r;   // recompensa
    int ac;    // accion
    int sp;   //estado siguiente
    int acp;  // accion siguiente
    Estado_Recompensa * est = new Estado_Recompensa(0,0);
    ac = politica(s,qValues);
    bool bandera = true; //para el fin de episodio
    while(bandera){
        (*pasos)++;

        delete est;
        est = entorno->accion(ac,s); //informacion del estado siguiente

        sp = est->getEstado()->getIndex();
        r = est->getRecompensa();
        if(!est->getEstado()->isTerminal()){
            acp =  politica(sp,qValues);
//#pragma omp critical
            qValues->num(qValues->num(s,ac) +
                         a *
                         (r + y * qValues->num(sp,acp)
                          - qValues->num(s,ac) ),s,ac) ;


        }else{
//#pragma omp critical
            qValues->num(qValues->num(s,ac) +
                         a *
                         (r  - qValues->num(s,ac) ),s,ac) ;


        }

        s = sp; ac = acp;
        /*  if(rank == 0){
            entorno->mostrar(ac,s);
            system("pause");

        }*/
        if(est->getEstado()->isTerminal() || s < menor || s > mayor){
            bandera = false;
            disminuirE();
            //   cout<<"encontro meta"<<endl;
            //  agente->getValues()->mostrar();
            //   system("pause");
        }
        if((*pasos) > 500000){
            bandera = false;


            //   cout<<"Demaciados pasos  >2000"<<endl;
        }

    }

}
/**
 *Para buscar el estado de inicio se episodio
 *
 */
int AgentePa:: buscaE(int inicio,int rango,Entorno * e){
    int s = 0 ;
    do{
        s = inicio + rand() %   rango/2  ;
    }while(!e->posible(s));

    return s;
}
