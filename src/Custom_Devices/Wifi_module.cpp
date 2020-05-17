/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Wifi_module.h"

using namespace std;

bool connection_request=0; //Used the first time to connect Wifi

string const Nom_fichier_Spotify="Internet_Spotify.txt";

// classe I2CActuatorScreen
I2CActuatorWifiModule::I2CActuatorWifiModule():Device(){
  }

void I2CActuatorWifiModule::run(){
    bool first_connection=1;
  
    while(1){
        if(!connection_request) //if device turns off then it will reconnect to wifi the next start
            first_connection=1;
            
        if(connection_request && first_connection){ //Only connect if it's the arduino start
            connect();
            first_connection=0;
        }

        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          cout << "---Request:"<< buf << endl;
        }
        sleep(1);
        }
}
  
void I2CActuatorWifiModule::connect(){
  ifstream fichier_spotify(Nom_fichier_Spotify); //crée une flux de lecture sur le fichier Internet_Spotify
  
  string ligne; //Permettra de stocker ce qu'on va lire
  string current_user;
  string current_password;
  
  istringstream iss;
  
  int trouve=0; //passe à 1 si on trouve le user
  
  cout << "Connection à Internet à l'adresse " << url << endl;
  
  if(fichier_spotify){ // On teste si tout est OK
      // Tout est OK, on peut utiliser le fichier
      while(getline(fichier_spotify,ligne) && !trouve){
          iss.str(ligne);
          getline(iss, current_user, ':');
          getline(iss, current_password, '\n');
          
          if(user==current_user){
              if(password==current_password){
                  trouve = 1;
              }
              else{
                  trouve = 2;
              }
          }
          //cout << current_user << " : " << current_password << endl;
          iss.clear();
      }
}
else
{
    cout << "Erreur : Impossible d'ouvrir le fichier." << endl;
}
  
  sleep(2); //Simule le temps d'attente
  
  switch(trouve){
      case 0:
          cout << "Utilisateur inconnu" << endl;
          break;
      case 1:
          cout << "Bienvenue " << user << endl;
          break;
      default:
          cout << "Mot de passe incorrect" << endl; 
  }
     
}