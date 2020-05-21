/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bluetooth_module.h
 * Author: raphael
 *
 * Created on May 20, 2020, 9:58 AM
 */

#ifndef BLUETOOTH_MODULE_H
#define BLUETOOTH_MODULE_H

#include "Common_includes.h"

extern bool connection_request_bluetooth;
extern bool connected_bluetooth; //Bluetooth is connected


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

// exemple d'actionneur sur le bus UART permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class UARTActuatorBluetoothModule : public Device{
protected:
    // memorise les données envoyées au module WIFI
  char buf[UART_BUFFER_SIZE];
  
public:
  // constructeur
  UARTActuatorBluetoothModule ();
  //Connection du Module Bluetooth à un appareil Bluetooth
  void connect();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
  
  class ExceptionConnexion{
  };

};

#endif /* BLUETOOTH_MODULE_H */

