/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bluetooth_module.cpp
 * Author: raphael
 *
 * Created on May 20, 2020, 9:58 AM
 */

#include "Bluetooth_module.h"

using namespace std;

bool connection_request_bluetooth=0; //Used the first time to connect Bluetooth
bool connected_bluetooth=0;

string const Nom_fichier_Bluetooth="Bluetooth_Devices.txt";

// classe I2CActuatorScreen
UARTActuatorBluetoothModule::UARTActuatorBluetoothModule():Device(){
  }

void UARTActuatorBluetoothModule::run(){
    
    connect();
    
    while(!connected_bluetooth){}
  
    while(1){
        
        if ( (UARTbus!=NULL)&&!(UARTbus->isEmptyRegister(UARTaddr))){
          Device::UARTbus->requestFrom(UARTaddr, buf, UART_BUFFER_SIZE);
          cout << "---BLUETOOTH MODULE: "<< buf << endl;
          
          //Ici les données sont recue par le module c'est la que tu dois les gérer genre afficher "J'ai bien recu, j'envoie au casque" ou quoi
      
        } 
        sleep(1);
        }
}
  
void UARTActuatorBluetoothModule::connect(){
  ifstream fichier_bluetooth(Nom_fichier_Bluetooth); //crée une flux de lecture sur le fichier Internet_Spotify
  
  string ligne; //Permettra de stocker ce qu'on va lire
  string current_device;
  
  istringstream iss;
  int cpt=1;
  int choix;
      
      while(!connection_request_bluetooth){}//
        
        cout << "---screen : Les modules bluetooth disponibles sont: " << endl;
        

        if(fichier_bluetooth){ // On teste si tout est OK
            // Tout est OK, on peut utiliser le fichier
            while(getline(fichier_bluetooth,ligne)){
                iss.str(ligne);
                getline(iss, current_device, '\n');

                cout << cpt++ << ") " << current_device << endl;
                
                iss.clear();
            }
            
            cout << "Choisissez svp: ";
            
            cin >> choix;
            
            cout << "Connection à " << choix << endl;
            
            sleep(1);
            
            connected_bluetooth = 1;
            
            cout << "Bluetooth connecté" << endl;
            
          }
          else
          {
              cout << "Erreur : Impossible d'ouvrir le fichier." << endl;
          }

        sleep(2); //Simule le temps d'attente
}

