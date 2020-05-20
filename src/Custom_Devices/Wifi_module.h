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
extern bool trigger_get_website; //Used the first time to connect Wifi
extern bool trigger_get_user; //Used the first time to connect Wifi
extern bool trigger_get_password; //Used the first time to connect Wifi

extern bool connected; //WIFI is connected

extern bool answer_ok; //it means we can read the answer given by Spotify
extern char answer[I2C_BUFFER_SIZE]; //This global variable stores the name of the music SPotify sends back

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorWifiModule : public Device{
protected:
    // memorise les données envoyées au module WIFI
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorWifiModule ();
  //Connection du Module Wifi à Internet
  void connect();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

#endif /* WIFI_MODULE_H */

