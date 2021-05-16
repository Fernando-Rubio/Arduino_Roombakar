#include <Servo.h>          //Libreria servomotor
#include <NewPing.h>        //Libreria sensor ultrasonidos. Descaragada
#include <TimerFreeTone.h>  //Libreria para el uso de zumbador. Descaragada



//L298N pines de control
const int MotorIzqDelante = 4;
const int MotorIzqDetras = 5;
const int MotorDerDelante = 3;
const int MotorDerDetras = 2;


//Pines del sensor
#define trig_pin A1
#define echo_pin A3

#define maximum_distance 450

boolean continua_hacia_delante = false;
int dist = 100;
NewPing sonar(trig_pin, echo_pin, maximum_distance);
Servo servo_motor;

//Zumbador
#define TONE_PIN 8
int melodia[] = {900};
int duracion[] = {250};


void setup() {
  pinMode(MotorIzqDelante, OUTPUT);
  pinMode(MotorIzqDetras, OUTPUT);
  pinMode(MotorDerDelante, OUTPUT);
  pinMode(MotorDerDetras, OUTPUT);
  pinMode(TONE_PIN, OUTPUT);
  servo_motor.attach(12);
  //Orientarlo hacia delante
  servo_motor.write(90);
  delay(2000);
  dist = leer();
  delay(100);
  dist = leer();
  delay(100);
  dist = leer();
  delay(100);
  dist = leer();
  delay(100);
  //Leer valores distancia
}

void loop() {
  //distancia a la derecha
  int distDer = 0;
  //distancia a la izquierda
  int distIzq = 0;
  delay(50);
  //distancia a la que se encuentra el objeto
  if (dist <= 25) {
    parada();
    delay(300);
    atras();
    delay(400);
    parada();
    delay(300);
    distDer = miraDerecha();
    delay(300);
    distIzq = miraIzquierda();
    delay(300);
    //si puede girar a derecha
    if (dist >= distIzq) {
      giro_derecha();
      parada();
    }
    //si no, gira izquierda
    else {
      giro_izquierda();
      parada();
    }
  }
  //si la distancia al objeto es mayor
  else {
    continuar();
  }
  dist = leer();
}

void parada() {
  digitalWrite(MotorIzqDetras, LOW);
  digitalWrite(MotorIzqDelante, LOW);
  digitalWrite(MotorDerDelante, LOW);
  digitalWrite(MotorDerDetras, LOW);
  //Hacemos sonar el zumbador al detectar algo
  TimerFreeTone(TONE_PIN, melodia[0], duracion[0]);
  delay(50);
}

void continuar() {
  if (!continua_hacia_delante) {
    continua_hacia_delante = true;
    digitalWrite(MotorIzqDelante, HIGH);
    digitalWrite(MotorDerDelante, HIGH);
    digitalWrite(MotorIzqDetras, LOW);
    digitalWrite(MotorDerDetras, LOW);
  }
}

void atras() {
  continua_hacia_delante = false;
  digitalWrite(MotorIzqDetras, HIGH);
  digitalWrite(MotorDerDetras, HIGH);
  digitalWrite(MotorIzqDelante, LOW);
  digitalWrite(MotorDerDelante, LOW);
}

void giro_derecha() {
  //rotar sobre si mismo
  digitalWrite(MotorIzqDelante, HIGH);
  digitalWrite(MotorDerDetras, HIGH);
  digitalWrite(MotorIzqDetras, LOW);
  digitalWrite(MotorDerDelante, LOW);
  delay(300);
  //continuar hacia delante
  digitalWrite(MotorIzqDelante, HIGH);
  digitalWrite(MotorDerDelante, HIGH);
  digitalWrite(MotorIzqDetras, LOW);
  digitalWrite(MotorDerDetras, LOW);
}

void giro_izquierda() {
  //rotar sobre si mismo
  digitalWrite(MotorIzqDetras, HIGH);
  digitalWrite(MotorDerDelante, HIGH);
  digitalWrite(MotorIzqDelante, LOW);
  digitalWrite(MotorDerDetras, LOW);
  delay(300);
  //continuar hacia delante
  digitalWrite(MotorIzqDelante, HIGH);
  digitalWrite(MotorDerDelante, HIGH);
  digitalWrite(MotorIzqDetras, LOW);
  digitalWrite(MotorDerDetras, LOW);
}

int miraDerecha() {
  //giramos sensor hacia la derecha
  servo_motor.write(10);
  delay(500);
  int dist = leer();
  delay(100);
  servo_motor.write(90);
  return dist;
}

int miraIzquierda() {
  //giramos sensor hacia la izquierda
  servo_motor.write(170);
  delay(500);
  int dist = leer();
  delay(100);
  servo_motor.write(90);
  return dist;
  delay(100);
}

int leer() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    //si la distancia al objeto es mayor que lo que lee
    //ponemos una distancia estandar
    cm = 250;
  }
  return cm;
}
