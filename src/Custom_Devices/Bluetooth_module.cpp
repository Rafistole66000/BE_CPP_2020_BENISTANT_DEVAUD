/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bluetooth_module.cpp
 * Author: raphael/emma
 *
 * Created on May 20, 2020, 9:58 AM
 */

#include "Bluetooth_module.h"
#include "Wifi_module.h"
#include "Bibliotheque.h"

using namespace std;

bool connection_request_bluetooth=0; //Used the first time to connect Bluetooth
bool connected_bluetooth=0;


bool trigger_get_values =0;
bool send_music =0;


string const Nom_fichier_Bluetooth="Bluetooth_Devices.txt";
//Bibliotheque MaBiblio=Bibliotheque() ; 

char  nom_musique_a_envoyer[UART_BUFFER_SIZE] ;
char valeurs_musique_a_envoyer[10][UART_BUFFER_SIZE];


// classe UARTActuatorScreen
UARTActuatorBluetoothModule::UARTActuatorBluetoothModule():Device(){
  }

void UARTActuatorBluetoothModule::run(){
    try{
        connect();
    }
    catch(ExceptionConnexion){
        cout << "---screen : Le choix n'est pas dans la liste!" << endl;
        exit(1);
    }
            
    while(!connected_bluetooth){}
    
  
    
    while(1){
        
        // Réception des données de la musique à envoyer au device audio 
        int i ; 
        cout << endl << "---module bluetooth : J'ai bien reçu les données suivantes ";
        for (i=0;i<10;i++){
            while(!trigger_get_values){}
                if ( (UARTbus!=NULL)&&!(UARTbus->isEmptyRegister(UARTaddr))){
                    Device::UARTbus->requestFrom(UARTaddr, buf, UART_BUFFER_SIZE);
                    strcpy(valeurs_musique_a_envoyer[i],buf) ;
                    trigger_get_values=0;
                    cout << valeurs_musique_a_envoyer[i]<< " "; 
            } 
        }
        cout << endl; 
        
         //Envoie la musique pour que l'audio device la diffuse ensuite 
        
          cout << endl << "---module bluetooth : Début de l'envoie au device audio de ";
          //cout << nom_musique_a_envoyer << endl ;
        int j ; 
        for (j=0;j<10;j++){
          cout << valeurs_musique_a_envoyer[j] << " " ; 
        } 
        cout << endl << "---module bluetooth : Fin de l'envoie au device audio \n ";
        send_music=0;
       
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
            
            if(choix<0 || choix>=cpt || !(choix)){ //l'utilisateur a fait un mauvais choix
                throw ExceptionConnexion();
            }
            else{    
            cout << "Connection à " << choix << endl;
            
            sleep(1);
            
            connected_bluetooth = 1;
            
            cout << "Bluetooth connecté" << endl << endl;
            }
            
          }
        else
        {
            cout << "Erreur : Impossible d'ouvrir le fichier." << endl;
        }

        sleep(2); //Simule le temps d'attente
}
