#include "Chasis.h"
#include "PuenteH.h"
#include <Arduino.h>

Chasis::Chasis(){}
Chasis::~Chasis(){}
void Chasis::inicializar(int ena, int enb, int in1, int in2, int in3, int in4, int porcentajeVelocidad){
  this->puenteH.inicializar(ena, enb, in1, in2, in3, in4);
  this->editarVelocidad(porcentajeVelocidad);
}
void Chasis::avanzar(){
  this->demorar(&PuenteH::avanzar);
  estado = ESTOY_AVANZADO;
}

void Chasis::retroceder(){
  this->demorar(&PuenteH::retroceder);
  estado = ESTOY_RETROCEDIENDO;
}
void Chasis::frenar(){
  this->demorar(&PuenteH::frenar);
}
void Chasis::rotarIzquierda(){
  this->demorar(&PuenteH::rotarIzquierda);
}
void Chasis::rotarDerecha(){
  this->demorar(&PuenteH::rotarDerecha);
}

void Chasis::editarVelocidad(int editarVelocidad){
  this->porcentajeVelocidad = 100 - porcentajeVelocidad;
  if (this->porcentajeVelocidad < 0)
  {
    this->porcentajeVelocidad = 0;
  }
}

void Chasis::demorar(void (PuenteH::*accion)()){
  (this->puenteH.*accion)();
  for (int i = 1; i < this->porcentajeVelocidad*10; ++i)
  {
    this->puenteH.frenar();
  }
  (this->puenteH.*accion)();
}