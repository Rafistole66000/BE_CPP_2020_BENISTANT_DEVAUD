#include "core_simulation.h"
#include "mydevices.h"

int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,TEMP);
  AnalogSensorLuminosity luminosite(DELAY); //Notre capteur de luminosité
  
  DigitalActuatorLED led1(DELAY);
  IntelligentDigitalActuatorLED intLed1(DELAY); //Creation of my Intelligent LED
  
  I2CActuatorScreen screen;
  
  // branchement des capteurs actionneurs
  esp8266.pin(1,temperature);
  esp8266.pin(0,led1);
  esp8266.i2c(1,screen);
  
  esp8266.pin(2,luminosite); //Capteur de température relié à pin 2
  esp8266.pin(3,intLed1); //Notre première Led intelligente
  
  // allumage de la carte
  esp8266.run();
  return 0;
}


