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
bool answer_ok=0;

string const Nom_fichier_Spotify="Internet_Spotify.txt";
string const Donnees_Spotify="Donnees_Spotify.txt";
char answer[I2C_BUFFER_SIZE];

// classe I2CActuatorScreen
I2CActuatorWifiModule::I2CActuatorWifiModule():Device(){
  }

void I2CActuatorWifiModule::run(){
    ifstream fichier_spotify; //crée une flux de lecture sur le fichier Donnees_Spotify
    string ligne; //Permettra de stocker ce qu'on va lire
    char my_bpm[I2C_BUFFER_SIZE]; //On y va stocker ce qu'on va lire sur le buffer
    string bpm; //on y va stocker ce qu'on va lire du fichier 
    string song;
    
    int i;//loop
    
    istringstream iss;
    bool trouve=0;
    
    connect();
    
    while(!connected){}
  
    while(1){
        
        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          strcpy(my_bpm,buf);
          //cout << "---WIFI MODULE: "<< buf << endl;
          
          fichier_spotify.open(Donnees_Spotify);
          
          if(fichier_spotify){ // On teste si tout est OK
            trouve=0;  
            while(getline(fichier_spotify,ligne) && !trouve){//Des qu'on a trouve une chanson dans le fichier on s'arrete
                iss.str(ligne);
                getline(iss, bpm, ':');
                getline(iss, song, '\n');

                if(my_bpm==bpm){
                    trouve=1;
                    
                    for(i = 0; song[i] != '\0'; i++)
                        answer[i] = song[i];
                    answer[i]='\0';
                    
                    
                    answer_ok=1;
                    cout << "---screen : une chanson à " << my_bpm << "bpm est " << answer << endl;
                }
                iss.clear();
            }
            if(!trouve){
                cout << "---screen: Il n'y a pas de chanson à ces BPM " << endl;                
            }
          }
          
          fichier_spotify.close();
      
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
      
      while(!connection_request){}//
  
        trouve=0; //S'il reste à 0 alors le User est inconnu sinon voir les autres cas plus loin
        
        while(!trigger_get_website){}//Wait Till website is written
        
        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          strcpy(web,buf);
          trigger_get_website = 0; //On rend la main à notre main boucle dans sketch_ino.cpp
        }
        
        while(!trigger_get_user){}//Wait Till website is written

        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          strcpy(my_user,buf);
          trigger_get_user = 0; //On rend la main à notre main boucle dans sketch_ino.cpp
        }
        sleep(1);   

        while(!trigger_get_password){}//Wait Till website is written

        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
          Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
          strcpy(my_password,buf);
          trigger_get_password=0; //On rend la main à notre main boucle dans sketch_ino.cpp
        }
        sleep(1);    
        
        cout << "---screen : Connection à Internet à l'adresse " << web << endl;
        

        if(fichier_spotify){ // On teste si tout est OK
            // Tout est OK, on peut utiliser le fichier
            while(getline(fichier_spotify,ligne) && !trouve){
                iss.str(ligne);
                getline(iss, current_user, ':');
                getline(iss, current_password, '\n');

                if(my_user==current_user){
                    if(my_password==current_password){
                        trouve = 1;//Tout est bon
                    }
                    else{
                        trouve = 2;//Le user existe mais le mot de passe est incorrect
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
                cout << "---screen : Utilisateur inconnu, connect fails" << endl;
                exit(1);
                break;
            case 1:
                cout << "---screen : Bienvenue " << my_user << endl << endl;
                connected=1;
                connection_request=0;
                break;
            default:
                cout << "---screen : Mot de passe incorrect, connect fails" << endl; 
                exit(1);
        }
}
  