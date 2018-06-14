#include <Servo.h>

//Define Inputs and Output Pins
int frontHallSensorInputPin = 7;
int backHallSensorInputPin = 9;
int bottomDisconnectedRailPin = 8;
int servoPin = 4;

//Define default status variables of pins
int initialFrontHallSensorReading;
int initialBackHallSensorReading;
boolean isTrainPassing = false;
Servo bridge;

//Abstraction Functions
void setBottomRail(boolean isEnabled){
  if (isEnabled){
    digitalWrite(bottomDisconnectedRailPin,LOW);
  }else{
    digitalWrite(bottomDisconnectedRailPin,HIGH);
  }
}

boolean getFrontHallSensorReading(){
  return digitalRead(frontHallSensorInputPin);
}
boolean getBackHallSensorReading(){
  return digitalRead(backHallSensorInputPin);
}

boolean isTrainPassingFrontSensor(){
  if (getFrontHallSensorReading() != initialFrontHallSensorReading){
    return true;
  }else{
    return false;
  }
}

boolean isTrainPassingBackSensor(){
  if (getBackHallSensorReading() != initialBackHallSensorReading){
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
  initialFrontHallSensorReading = 1;
  initialBackHallSensorReading = 1;
  setBottomRail(false);
}

void loop() {
  if (isTrainPassingFrontSensor() && !isTrainPassing){
    isTrainPassing = true;
    moveBridgeTo(20);
    delay(1000);
    setBottomRail(true);
  }
  if (isTrainPassingBackSensor() && isTrainPassing){
    isTrainPassing = false;
    moveBridgeTo(0);
    setBottomRail(false);
  }
}
