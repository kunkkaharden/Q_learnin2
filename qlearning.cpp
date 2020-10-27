#include "qlearning.h"


Qlearning::Qlearning(Matrix *en, Matrix *re)
{
    entorno = new Entorno(en,re);
    agente = new Agente(en->columnas() * en->filas() , 4);
}
void Qlearning :: entrenar(int it ){
    int s = 0; // estado actual
    float r;  // recompensa
    int ac;   //accion

    int sp;   //estado
    int pasos =0;  // cantidad de pasos
    Estado_Recompensa * est = new Estado_Recompensa(0,0);
    bool bandera ;
    for(int i =0; i < it ; i++){
        pasos =0;
        s = 0;
        bandera = true;
        while(bandera){
            pasos++;
            ac = agente->politica(s);
            delete est;
            est = entorno->accion(ac,s);

            sp = est->getEstado()->getIndex();
            r = est->getRecompensa();
            agente->getValues()->num( agente->getValues()->num(s,ac) +
                                      agente->getA() *
                                      (r + agente->getY() * agente->getValues()->num(sp,agente->mejorAccion(sp))
                                       - agente->getValues()->num(s,ac) ),s,ac) ;

            s = sp;
            if(est->getEstado()->getFin() == true){
                bandera = false;
                agente->disminuirE();
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

}

