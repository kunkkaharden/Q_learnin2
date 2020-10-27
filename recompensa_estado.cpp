#include "recompensa_estado.h"



float Recompensa_Estado::getRecompensa() const
{
    return recompensa;
}

void Recompensa_Estado::setRecompensa(float value)
{
    recompensa = value;
}



bool Recompensa_Estado::getVacio() const
{
    return vacio;
}

void Recompensa_Estado::setVacio(bool value)
{
    vacio = value;
}

float Recompensa_Estado::getValor() const
{
    return valor;
}

void Recompensa_Estado::setValor(float value)
{
    valor = value;
}

int Recompensa_Estado::getEstadoSiguiente() const
{
    return estadoSiguiente;
}

void Recompensa_Estado::setEstadoSiguiente(int value)
{
    estadoSiguiente = value;
}

Recompensa_Estado::~Recompensa_Estado()
{
valor = 5;
recompensa = 6;
}

Recompensa_Estado::Recompensa_Estado()
{   estadoSiguiente =1;
    valor =2;
    vacio = true;
    recompensa = 3;
    
}

Recompensa_Estado::Recompensa_Estado(int estadoE , float valorE, float recompensaE)
{
    this->estadoSiguiente =estadoE;
   this->valor =valorE;
      this->vacio = false;
      this->recompensa = recompensaE;

}


void Recompensa_Estado::set(Recompensa_Estado * value)
{
 //  estadoSiguiente = value->getEstadoSiguiente();
  //  valor = value->getValor();
 //   vacio = false;
 //   recompensa = value->getRecompensa();
    setEstadoSiguiente( value->getEstadoSiguiente());
    setRecompensa(value->getRecompensa());
    setVacio("false");
    setValor(value->getValor());

}
