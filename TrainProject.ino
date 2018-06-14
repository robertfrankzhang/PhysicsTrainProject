#include <Servo.h>

//Define Inputs and Output Pins
#ifdef IN_SCHOOL
int frontHallSensorInputPin = 7;
int backHallSensorInputPin = 9;
int bottomDisconnectedRailPin = 8;
int servoPin = 4;
#else
int frontHallSensorInputPin = 2;
int backHallSensorInputPin = 3;
int bottomDisconnectedRailPin = 6;
int servoPin = 4;
#endif


//Define default status variables of pins
int initialFrontHallSensorReading;
int initialBackHallSensorReading;
boolean isTrainPassing = false;
Servo bridge;

//Abstraction Functions
void setBottomRail(boolean isEnabled){
  if (isEnabled){
    digitalWrite(bottomDisconnectedRailPin,HIGH);
  }else{
    digitalWrite(bottomDisconnectedRailPin,LOW);
  }
}

boolean getFrontHallSensorReading(){
  return digitalRead(frontHallSensorInputPin);
}
boolean getBackHallSensorReading(){
  return digitalRead(backHallSensorInputPin);
}

boolean isTrainPassingFrontSensor(){
  if (digitalRead(frontHallSensorInputPin) != initialFrontHallSensorReading){
    return true;
  }else{
    return false;
  }
}

boolean isTrainPassingBackSensor(){
  if (digitalRead(backHallSensorInputPin) != getBackHallSensorReading()){
    return true;
  }else{
    return false;
  }
}

void moveBridgeTo(int amount){
  bridge.write(amount);
}
//

void setup() {
  //Setup pin modes
  pinMode(frontHallSensorInputPin,INPUT);
  pinMode(backHallSensorInputPin,INPUT);
  pinMode(bottomDisconnectedRailPin,OUTPUT);
  bridge.attach(servoPin);

  //Get initial readings
  initialFrontHallSensorReading = getFrontHallSensorReading();
  initialBackHallSensorReading = getBackHallSensorReading();
}

void loop() {
  if (isTrainPassingFrontSensor() && !isTrainPassing){
    isTrainPassing = true;
    moveBridgeTo(20);
    setBottomRail(true);
  }
  if (isTrainPassingBackSensor() && isTrainPassing){
    isTrainPassing = false;
    moveBridgeTo(0);
    setBottomRail(false);
  }
}
