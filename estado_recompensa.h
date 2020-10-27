#ifndef ESTADO_RECOMPENSA_H
#define ESTADO_RECOMPENSA_H
#include<estado.h>

class Estado_Recompensa
{
private :
    Estado  * estado;
    float recompensa;
public:
    Estado_Recompensa(Estado * e, float r);

    Estado *getEstado() const;
    void setEstado(Estado *value);
    float getRecompensa() const;
    void setRecompensa(float value);
};

#endif // ESTADO_RECOMPENSA_H
