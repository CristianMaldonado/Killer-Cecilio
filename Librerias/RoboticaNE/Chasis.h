#ifndef __CHASIS_H__
#define __CHASIS_H__
#include "PuenteH.h"
#include <Arduino.h>

class Chasis
{
public:
  Chasis();
  virtual ~Chasis();
  void inicializar(int ena, int enb, int in1, int in2, int in3, int in4, int porcentajeVelocidad = 100);
  void avanzar();
  void retroceder();
  void frenar();
  void rotarIzquierda();
  void rotarDerecha();
  void editarVelocidad(int porcentajeVelocidad);
protected:
  PuenteH puenteH;
  int porcentajeVelocidad;
private:
  void demorar(void (PuenteH::*accion)());
};

#endif