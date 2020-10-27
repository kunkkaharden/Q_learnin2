#include "agente.h"
Agente::Agente(int f , int c)
{
    values = new Matrix( 0,f, c);
}



Matrix *Agente::getValues() const
{
    return values;
}

float Agente::getA() const
{
    return a;
}


float Agente::getY() const
{
    return y;
}

void Agente::disminuirE()
{
    if(e > 0.10){
        e -= 0.02;
    }

}



int Agente::mejorAccion(int estado){
    float valor = values->num(estado, 0) ;
    float temporal;
    int accion = 0 ;
    int cantI = 1;
    for(int i =1; i < values->columnas(); i++){
        temporal = values->num(estado, i) ;
        if(temporal > valor){
            valor = temporal;
            accion = i;

        }else  if(temporal == valor){
            cantI++;
        }
    }

    if(cantI == values->columnas()){
        accion = accionRamdon();
     //   cout<<"r: "<<accion<<endl;
    }else{
     //     cout<<"i:"<<accion<<endl;
     //   cout<<"por mejor valor******************************************************************"<<endl;
     //   values->mostrar();
    }

    return accion  ;
}



int Agente ::politica(int estado)
{
    int accion = -1;
    float ramdon = floatRandom();
    if(ramdon < e){
        accion = accionRamdon();
       // cout<<"aR: "<<accion<<endl;

    }else{
        accion = mejorAccion(estado);
    }
    return accion;
}

float Agente:: floatRandom(){

    float a = 1+ rand() %9;
    float b = 1 + rand() % 9 ;
    float num = 0 +( a/10) + (b / 100) ;
    return num;
}
int Agente::accionRamdon()
{
    return   0+ rand() % values->columnas();


}
