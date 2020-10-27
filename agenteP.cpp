#include "agenteP.h"





float AgenteP::getA() const
{
    return a;
}


float AgenteP::getY() const
{
    return y;
}

void AgenteP::disminuirE()
{
    if(e > 0.10){
        e -= 0.02;
    }

}



int AgenteP::mejorAccion(int estado, Matrix * qValues){
    float valor = qValues->num(estado, 0) ;
    float temporal;
    int accion = 0 ;
    int cantI = 1;
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
        //   cout<<"r: "<<accion<<endl;
    }else{
        //     cout<<"i:"<<accion<<endl;
        //   cout<<"por mejor valor******************************************************************"<<endl;
        //   values->mostrar();
    }

    return accion  ;
}



int AgenteP ::politica(int estado, Matrix * qValues)
{
    int accion = -1;
    float ramdon = floatRandom();
    if(ramdon < e){
        accion = accionRamdon(qValues);
        // cout<<"aR: "<<accion<<endl;

    }else{
        accion = mejorAccion(estado, qValues);
    }
    return accion;
}

float AgenteP:: floatRandom(){

    float a = 1+ rand() %9;
    float b = 1 + rand() % 9 ;
    float num = 0 +( a/10) + (b / 100) ;
    return num;
}
int AgenteP::accionRamdon(Matrix * qValues)
{
    return   0+ rand() % qValues->columnas();


}
void AgenteP:: entrenar(int rank , int size, int it , Matrix * qValues , Entorno * entorno){

int menor ,  mayor;

    int muestra = qValues->filas() / size -1;
    if(rank == 0){
        menor =0;
        mayor = qValues->filas();
    }else if(rank == size - 1){
        menor = (rank -1) * muestra ;
        mayor = qValues->filas();
    }else{
        menor = (rank -1 )* muestra ;
        mayor = (rank ) * muestra ;
    }
    //int estadoI = buscaE(menor,muestra,entorno);// estado dado inicio


    //    ,
    //*******************************************
    int s = 0; // estado actual
    float r;  // recompensa
    int ac;   //accion

    int sp;   //estado
    int pasos =0;  // cantidad de pasos
    Estado_Recompensa * est = new Estado_Recompensa(0,0);
    bool bandera ;
    for(int i =0; i < it ; i++){
        pasos =0;
        s =buscaE(menor,muestra,entorno);
        bandera = true;
        while(bandera){
            pasos++;
            ac = politica(s,qValues);
            delete est;
            est = entorno->accion(ac,s);

            sp = est->getEstado()->getIndex();
            r = est->getRecompensa();
            qValues->num(qValues->num(s,ac) +
                                      a *
                                      (r + y * qValues->num(sp,mejorAccion(sp,qValues))
                                       - qValues->num(s,ac) ),s,ac) ;

            s = sp;
            if(rank == 1){
                entorno->mostrar(ac,s);
            }
            if(est->getEstado()->getFin() == true || s < menor || s > mayor){
                bandera = false;
                disminuirE();
                //   cout<<"encontro meta"<<endl;
                //  agente->getValues()->mostrar();
                //   system("pause");
            }
            if(pasos > 2000){
                bandera = false;
                cout<<"Demaciados pasos  >2000"<<endl;
            }
        }
        cout<<"pasos: "<<pasos<<endl;
        system("pause");
    }
    //****************************************

}
int AgenteP:: buscaE(int inicio,int rango,Entorno * e){
    int s = inicio + rand() % rango / 2 ;
    while(!e->posible(s)){
        s = inicio + rand() % rango / 2 ;
    }
    return s;
}
