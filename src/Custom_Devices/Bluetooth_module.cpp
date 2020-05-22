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
#include "Wifi_module.h"
#include "Bibliotheque.h"

using namespace std;

bool connection_request_bluetooth=0; //Used the first time to connect Bluetooth
bool connected_bluetooth=0;

string const Nom_fichier_Bluetooth="Bluetooth_Devices.txt";



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
    
    Bibliotheque MaBiblio=Bibliotheque() ; 
    string musique_a_envoyer ;
    while(1){
        //if (1){
        if ( (UARTbus!=NULL)&&!(UARTbus->isEmptyRegister(UARTaddr))){
          Device::UARTbus->requestFrom(UARTaddr, buf, UART_BUFFER_SIZE);
          cout << "---BLUETOOTH MODULE: "<< endl;
          
          //Ici les données sont recues par le module c'est la que tu dois les gérer genre afficher "J'ai bien recu, j'envoie au casque" ou quoi
          // étape 1 : vérification de la réception du nom de la chanson via la requête 
          cout << "J'ai bien reçu la réponse : " << buf << endl; 
          musique_a_envoyer=MaBiblio.RechercherMusique(buf);
          cout << "J'ai trouvé : " << musique_a_envoyer<< " dans la bibliothèque " ;
          cout << endl; 
          
          cout << "J'envoie au device audio la musique : " << musique_a_envoyer  ;
          cout  <<endl ;
          
      
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
            
            if(choix<0 || choix>=cpt || !(cin>>choix)){ //l'utilisateur a fait un mauvais choix
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

