#ifndef RECOMPENSA_ESTADO_H
#define RECOMPENSA_ESTADO_H


class Recompensa_Estado
{
private:
  int estadoSiguiente;
    float recompensa;
    float valor;
    bool vacio;

public:
   ~Recompensa_Estado();
    Recompensa_Estado();

    float getRecompensa() const;
    void setRecompensa(float value);

    bool getVacio() const;
    void setVacio(bool value);
    float getValor() const;
    void setValor(float value);
  //  Recompensa_Estado(Recompensa_Estado *value);

    int getEstadoSiguiente() const;
    void setEstadoSiguiente(int value);
    Recompensa_Estado(int estado, float valorE, float recompensaE);
    void set(Recompensa_Estado *value);
};

#endif // RECOMPENSA_ESTADO_H
