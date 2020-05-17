/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pulse_sensor.h
 * Author: raphael
 *
 * Created on May 17, 2020, 10:15 AM
 * We assume that a Oprational Amplificator is set in a hysterisis mode to transform the signal into an almost perfect square signal
 */

#ifndef PULSE_SENSOR_H
#define PULSE_SENSOR_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "../core_simulation.h"
#include <fstream>
#include <cmath>

//Pulse global variable
extern int Time_Between_Two_Pulse;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/* exemple de capteur digital, la valeur de la période est calculé en prenant la différence de temps entre 2 interruptions en ne considérant que les montées ou que les descentes, 
ne pas oublier d'heriter de Device*/
class DigitalSensorPulse: public Device {
private:
  // fait osciller la valeur du capteur de 5
  int alea;
  // valeur de la fréquence mesuree en bpm
  int val;
  /* temps entre 2 prises de valeurs /!\ C'est ce qui varie/!\*/
  int temps;
  
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  DigitalSensorPulse();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};


#endif /* PULSE_SENSOR_H */

