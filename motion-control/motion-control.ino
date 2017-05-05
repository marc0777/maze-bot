#include <Wire.h>
#include <Moviment.h>
#include <IMU.h>
#include <PID.h>

//#define CORRECTION false

#define MASTER_ADDRESS 8
#define ADDRESS 7
#define OUT_MIN 100
#define OUT_MAX 255

#define Kp 2
#define Ki 5
#define Kd 1

double Setpoint, inputPID, outputPID; //copiato dall'esempio della libreria del PID
PID pid(&inputPID, &outputPID, &Setpoint, Kp, Ki, Kd, DIRECT);  //inizializzazione dell'oggetto PID copiato senza capire cos'è il DIRECT
//che non è stato trovato da nessuna parte, ma stranamente compila
//l'input e l'output sono le variabili dove bisognerà assegnare il valore
//letto il Setpoint è la variabile di riferimento, le tre costanti sono i
//parametri da mettere apposto.


float direzione = 0;
byte state = 255;
byte requested = 255;
byte prevState = 255;
int inclination;

Moviment mov(65);
IMU orientation;

void receiveEvent(int howMany) {
  byte input = Wire.read();
  if (input < 200) state = input;
  else if (input == 255) requested = 0;
  else mov.setSpeed((input-200)*5);
}

void send(byte data, byte address) {
  Wire.beginTransmission(address);
  Wire.write(data);
  Wire.endTransmission();
}


void answer() {
  if (requested!=255) {
    inclination=orientation.pitch();
    send(inclination+90,MASTER_ADDRESS);
    requested=255;
  }
}

void rotationSpeed(bool direction , float endRotation) {
  direzione = orientation.yaw();
  if (endRotation-direzione>0) mov.setK(40+((endRotation - direzione)*2), 60+((endRotation - direzione)*2));
  else mov.setK(60+((direzione - endRotation)*2), 40+((direzione - endRotation)*2));
  mov.rotate(direction);
}// negare la condizione se il filtro funziona in modo diverso

void goStraight(bool invert) {
  orientation.start();
  mov.go(invert);
  while (state == 1 || state == 3) {
    direzione = orientation.yaw()-180;
    if (direzione < 0) mov.setK(0, 10);
    else if (direzione > 0) mov.setK(10, 0);
    answer();
    mov.go(invert);
  }
}

void turn(bool invert) {
  orientation.start();
  mov.rotate(invert);
  float end = endAngle(orientation.yaw(), invert);
  if (invert) {
    while(orientation.yaw()<end) rotationSpeed(invert,end);
    mov.stop();
    while(orientation.yaw()>end) rotationSpeed(!invert,end);
  }
  else {
    while(orientation.yaw()>end) rotationSpeed(invert,end);
    mov.stop();
    while(orientation.yaw()<end) rotationSpeed(!invert,end);
  }
  mov.setK(0,0);
  mov.stop();
  state=9;
  send(255,MASTER_ADDRESS);
}

float endAngle(float angle, bool invert) {
  if (invert) {
    angle += 90;
    return (angle > 360) ? angle - 360 : angle;
  }
  else {
    angle -= 90;
    return (angle < 0) ? angle + 360 : angle;
  }
}

void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  orientation.begin();
  delay(100);
  orientation.calibrate();
  delay(100);
  orientation.start();
  pid.SetOutputLimits(OUT_MIN, OUT_MAX);
}

void loop() {
  if (state!=prevState) {
    switch (state) {
    case 9:
      mov.stop();
      break;
    case 1:
//      #ifdef CORRECTION
   //   mov.go(false);
//      #else
      goStraight(false);
//      #endif
      break;
    case 2:
      turn(false);
      break;
    case 3:
//      #ifdef CORRECTION
 //     mov.go(true);
  //    #else
      goStraight(true);
 //     #endif
      break;
    case 4:
      turn(true);
      break;
    case 5:
      mov.rotate(false);
      break;
    case 6:
      mov.rotate(true);
      break;
    }
    prevState=state;
  }
  answer();
}
