/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Wifi_module.h"

using namespace std;

bool connection_request=0; //Used the first time to connect Wifi
bool trigger_get_website=0; //Used the first time to connect Wifi
bool trigger_get_user=0; //Used the first time to connect Wifi
bool trigger_get_password=0; //Used the first time to connect Wifi

bool connected=0;

string const Nom_fichier_Spotify="Internet_Spotify.txt";

// classe I2CActuatorScreen
I2CActuatorWifiModule::I2CActuatorWifiModule():Device(){
  }

void I2CActuatorWifiModule::run(){
    
    connect();
    
    while(!connected){}
  
    while(1){
        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          cout << "---WIFI MODULE: "<< buf << endl;
        }
        sleep(1);
        }
}
  
void I2CActuatorWifiModule::connect(){
  ifstream fichier_spotify(Nom_fichier_Spotify); //crée une flux de lecture sur le fichier Internet_Spotify
  
  string ligne; //Permettra de stocker ce qu'on va lire
  char web[I2C_BUFFER_SIZE];
  char my_user[I2C_BUFFER_SIZE];
  char my_password[I2C_BUFFER_SIZE];
  string current_user;
  string current_password;
  
  istringstream iss;
  int trouve;
  
  while(1){
      
      if(connection_request){
  
        trouve=0; //passe à 1 si on trouve le user
        
        while(!trigger_get_website){}//Wait Till website is written
        
        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          strcpy(web,buf);
          cout << "---WIFI MODULE: "<< buf << endl;
          trigger_get_website = 0;
        }
        
        while(!trigger_get_user){}//Wait Till website is written

        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          strcpy(my_user,buf);
          cout << "---WIFI MODULE: "<< buf << endl;
          trigger_get_user = 0;
        }
        sleep(1);   

        while(!trigger_get_password){}//Wait Till website is written

        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          strcpy(my_password,buf);
          cout << "---WIFI MODULE: "<< buf << endl;
          trigger_get_password=0;
        }
        sleep(1);    
        
        cout << "Connection à Internet à l'adresse " << web << endl;
        

        if(fichier_spotify){ // On teste si tout est OK
            // Tout est OK, on peut utiliser le fichier
            while(getline(fichier_spotify,ligne) && !trouve){
                iss.str(ligne);
                getline(iss, current_user, ':');
                getline(iss, current_password, '\n');

                if(my_user==current_user){
                    if(my_password==current_password){
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
                cout << "Utilisateur inconnu, connect fails" << endl;
                exit(1);
                break;
            case 1:
                cout << "Bienvenue " << user << endl;
                connected=1;
                connection_request=0;
                break;
            default:
                cout << "Mot de passe incorrect, connect fails" << endl; 
                exit(1);
        }
  
    }
  }
}
  