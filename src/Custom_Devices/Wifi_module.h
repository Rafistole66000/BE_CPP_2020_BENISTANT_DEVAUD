/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wifi_module.h
 * Author: raphael
 *
 * Created on May 17, 2020, 1:52 PM
 */

#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include "Common_includes.h"

extern bool connection_request;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorWifiModule : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorWifiModule ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
  //Connection du Module Wifi à Internet
  void connect();
};

#endif /* WIFI_MODULE_H */

