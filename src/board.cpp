#include "core_simulation.h"
#include "mydevices.h"

char on[]="on.txt";
char led[]="led.txt";
char* p_on=on;
char* p_led=led;

int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,TEMP);
  AnalogSensorLuminosity luminosite(DELAY); //Notre capteur de luminosité
  DigitalSensorPulse pulse; //Notre capteur de luminosité
  
  DigitalActuatorLED led1(DELAY);
  IntelligentDigitalActuatorLED intLed1(DELAY); //Creation of my Intelligent LED
  ExternalDigitalSensorButton bouton1(DELAY,on);
  ExternalDigitalSensorButton bouton2(DELAY,led);
  
  I2CActuatorScreen screen;
  I2CActuatorWifiModule wifi;
  
  UARTActuatorBluetoothModule bluetooth;
  
  // branchement des capteurs actionneurs
  esp8266.pin(1,temperature);
  //esp8266.pin(0,led1);
  esp8266.i2c(1,screen);
  esp8266.uart(1,bluetooth);
  esp8266.i2c(2,wifi);
  
  
  esp8266.pin(2,luminosite); //Capteur de température relié à pin 2
  //esp8266.pin(3,intLed1); //Notre première Led intelligente
  esp8266.pin(4,bouton1); //bouton on/off systeme
  esp8266.pin(6,bouton2); //bouton on/off led
  esp8266.pin(5,pulse); //Notre capteur de pulstation
  
  
  // allumage de la carte
  //wifi.connect();
  esp8266.run();
  return 0;
}


