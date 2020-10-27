#include "estado_recompensa.h"

Estado * Estado_Recompensa::getEstado() const
{
    return estado;
}

void Estado_Recompensa::setEstado(Estado * value)
{
    estado = value;
}

Estado_Recompensa::Estado_Recompensa(Estado * e, float r):estado(e),recompensa(r)
{

}

float Estado_Recompensa::getRecompensa() const
{
    return recompensa;
}

void Estado_Recompensa::setRecompensa(float value)
{
    recompensa = value;
}



