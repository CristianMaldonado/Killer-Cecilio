  
  #include <Chasis.h>
  #include <Ruedas.h>
  #include <PuenteH.h>
  #include <NewPing.h>
  #define DIST_MAX 20
  #define PORCENTAJE_VELOCIDAD 20
  #define BLANCO LOW
  #define NEGRO HIGH

  const int ena = 13;
  const int in1 = 12;
  const int in2 = 11;
  const int in3 = 10;
  const int in4 = 9;
  const int enb = 8;
  const int triggerDelantero = 22;
  const int triggerTrasero = 53;
  const int echoDelantero = 23;
  const int echoTrasero = 52;
  const int sensorFrontal = 24;
  const int sensorTrasero = 47;
  const int sensorDerecha = 48;
  const int sensorIzquierda = 49;

  NewPing sonarDelatero(triggerDelantero, echoDelantero, DIST_MAX);
  NewPing sonarTrasero(triggerTrasero, echoTrasero, DIST_MAX);
  Chasis chasis;

  void setup(){
    Serial.begin(9600);
    chasis.inicializar(ena, enb, in1, in2, in3, in4, PORCENTAJE_VELOCIDAD);
    inicializarSensoresBlanco();
  }

  void loop(){

    if(meEstoySaliendo()){
      meterse();
    }else if(algoDelante()){
        chasis.avanzar();
      }else if(algoDetras()){
          chasis.retroceder();
        }else {
          chasis.rotarIzquierda();
          chasis.editarVelocidad(5);
          chasis.frenar();
          chasis.editarVelocidad(PORCENTAJE_VELOCIDAD);      
        }
  }

  boolean algoDetras(){
    return (sonarTrasero.ping_cm() != 0);
  }

  boolean algoAdelante(){
    return (sonarDelatero.ping_cm() != 0);
  }

  void meterse(){
    if(meSalgoPorDelante()){
      chasis.retroceder();
    }else if(meSalgoPorDetras()){
      chasis.avanzar();
    }
    if(meSalgoPorLaIzquierda() && estoyAvanzando()) {chasis.doblarDerecha()}
    if(meSalgoPorLaIzquierda() && estoyRetrocediendo()) {chasis.doblarIzquierda()}
    if(meSalgoPorLaDerecha() && estoyAvanzando()) {chasis.doblarIzquierda()}
    if(meSalgoPorLaDerecha() && estoyRetrocediendo()) {chasis.doblarDerecha()}
  }

  boolean meSalgoPorDelante(){
    return (digitalRead(sensorFrontal) == BLANCO);
  }

  boolean meSalgoPorDetras(){
    return (digitalRead(sensorTrasero) == BLANCO);
  }

  boolean estoyAvanzando(){
    return (chasis.estado == 0);
  }

  boolean estoyRetrocediendo(){
    return (chasis.estado == 1);
  }

  boolean meEstoySaliendo(){
    return (meSalgoPorDelante() || meSalgoPorDetras() || meSalgoPorLaDerecha() || meSalgoPorLaIzquierda());
  }

  void inicializarSensoresBlanco(){
  pinMode(sensorFrontal, INPUT);
  pinMode(sensorTrasero, INPUT);
  pinMode(sensorIzquierda, INPUT);
  pinMode(sensorDerecha, INPUT);
}
