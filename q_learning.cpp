#include "q_learning.h"
#include<iostream>
using namespace std;
float Q_Learning::getE() const
{
    return e;
}

void Q_Learning::setE(float value)
{
    e = value;
}

int Q_Learning::accionRamdon(int estado)
{
    int accion = 0+ rand() % cantAcciones;
    while(get(estado,accion).getVacio()){
        accion = 0+ rand() % cantAcciones;
    }
    return accion;
}

Q_Learning::~Q_Learning()
{
    delete [] matrix;
}



int Q_Learning::politica(int estado)
{
    int accion = -1;
    float ramdon = floatRandom();
    if(ramdon < e){
        accion = accionRamdon(estado);
        if(a>0){
            e-=0.02;
        }
    }else{
        accion = mejorAccion(estado);
    }
    return accion;
}

Recompensa_Estado Q_Learning::get(int estado , int accion)
{
    if(estado <  0 || estado > cantEstados || accion < 0 || accion > cantAcciones){
        cout<<"indice fuera de rango"<<endl;
        system("pause");
    }
    return matrix[estado * cantAcciones + accion]; //[fila * cantidad de  columnas + columna]
}
float Q_Learning:: floatRandom(){

    float a = 1+ rand() %9;
    float b = 1 + rand() % 9 ;
    float num = 0 +( a/10) + (b / 100) ;
    return num;
}
int Q_Learning::mejorAccion(int estado){
    float valor ;
    float temporal;
    int accion = -2 ;
    bool encontrado  = false;
    for(int i =0; i < cantAcciones; i++){
        if(!get(estado, 0).getVacio()){
            if(!encontrado){
                encontrado = true;
                valor = get(estado, i).getValor()  ;
                accion = i;
            }else{
                temporal = get(estado,i).getValor();
                if(temporal > valor){
                    valor = temporal;
                    accion = i;
                }
            }

        }
    }
    return accion;
}

void Q_Learning::entrenar(int inicio , int fin , int iteraciones){
    int estado  , accion, estadoSiguiente;
    float recompensa;
    bool bandera;
    float valor;
    for(int i =0; i < iteraciones; i++){
        bandera = true;
        estado = inicio;

        while(bandera){
            accion = politica(estado);
            estadoSiguiente = get(estado,accion).getEstadoSiguiente();
            recompensa =  get(estado,accion).getRecompensa();
            if(estadoSiguiente == fin){
                valor = get(estado,accion).getValor() + a * (get(estadoSiguiente,0).getRecompensa()  - get(estado,accion).getValor());

            }else{
                valor = get(estado,accion).getValor() + a * (get(estadoSiguiente,0).getRecompensa() + y * get(estadoSiguiente,mejorAccion(estadoSiguiente)).getValor() - get(estado,accion).getValor());
            }
//cout <<"estado: "<<estado<<endl;
            get(estado,accion).setValor(valor);
            estado = estadoSiguiente;
            if(estado == fin){
                bandera = false;
            }


        }
    }

}

Q_Learning::Q_Learning(int estados , int acciones)
{
    matrix = new Recompensa_Estado[estados * acciones];

    cantEstados = estados;
    cantAcciones = acciones;
}

void Q_Learning :: addEstadoAccion(int estado , int accion ,Recompensa_Estado * value){
    get(estado,accion).set(value);
}
void Q_Learning :: mostrar(){
    for (int i =0; i < cantEstados ; i++){
        for (int j =0; j < cantAcciones ; j++){
            cout<<"e: "<<i<<" a: "<<j<<" r: "<< get(i,j).getRecompensa()<<endl;
        }
    }
}

