#include "core_simulation.h"
#include "mydevices.h"

int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,TEMP);
  AnalogSensorLuminosity luminosite(DELAY); //Notre capteur de luminosité
  DigitalSensorPulse pulse; //Notre capteur de luminosité
  
  
  DigitalActuatorLED led1(DELAY);
  IntelligentDigitalActuatorLED intLed1(DELAY); //Creation of my Intelligent LED
  ExternalDigitalSensorButton bouton1(DELAY);
  
  I2CActuatorScreen screen;
  I2CActuatorWifiModule wifi;
  
  UARTActuatorScreen screen_uart;
  
  // branchement des capteurs actionneurs
  esp8266.pin(1,temperature);
  esp8266.pin(0,led1);
  esp8266.i2c(1,screen);
  esp8266.uart(1,screen_uart);
  esp8266.i2c(2,wifi);
  
  
  esp8266.pin(2,luminosite); //Capteur de température relié à pin 2
  esp8266.pin(3,intLed1); //Notre première Led intelligente
  esp8266.pin(4,bouton1); //Notre boI2CActuatorScreenuton externe
  esp8266.pin(5,pulse); //Notre capteur de pulstation
  
  
  // allumage de la carte
  //wifi.connect();
  esp8266.run();
  return 0;
}


