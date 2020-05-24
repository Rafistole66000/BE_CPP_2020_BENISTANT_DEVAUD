#include "board_manager.h"

Board_manager my_board_manager;
bool devices_on=0;
Bibliotheque MaBiblio = Bibliotheque() ;

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sortie en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT);
  pinMode(0,OUTPUT);
  pinMode(2,INPUT); //capteur de température
  pinMode(3,OUTPUT); //intLed1
  pinMode(4,INPUT); //intLed1
  pinMode(5,INPUT); //capteur de pulsation
}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  //int val;
  //int lum;
  //int puls;
  int mean_pulse;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<6;i++){
 
      
      if(digitalRead(4)==ON && !devices_on){//Bouton On/Off
          devices_on = 1; //Evite de retourner dans ce if inutile après le premier tour
         
          if(!connected){//On parle du Wifi
              my_board_manager.connect_to_Internet(*this);
          }
          
          if(!connected_bluetooth){
              my_board_manager.connect_to_Bluetooth();
          }
      }
 
      mean_pulse = my_board_manager.compute_mean_pulse_10values(*this);
      
    if(connected){
        if(!send_music){
            my_board_manager.send_music_request(*this, mean_pulse);
            send_music=1;
        
        
        
            // Mise à jour de la bibliothèque en fonction de la réponse de spotify 
            
            MaBiblio.MiseAJourBiblio(answer,mean_pulse,music_values); //SEGMENTATION FAULT LA !!!!!!!

            //Affiche du nom de la chanson sur l'écran
            sprintf(buf,"%s",answer);
            Serial.println(buf);

            // La variable music_values contient les données de la musique, transmission au module bluetooth  
            my_board_manager.send_music_to_bluetooth_device(*this,MaBiblio,answer);
        }           
    }
    
    if(cpt%5==0 && cpt!=0){ //Passe la pulsation à 200 en moyenne au lieu de 120
        //cout << "Pulsation changes";
        Time_Between_Two_Pulse=300;
    }
    
    cpt++;
    sleep(1);
  }
  
// on eteint et on allume la LED
  if(bascule)
    digitalWrite(0,HIGH);
  else
    digitalWrite(0,LOW);
  bascule=1-bascule;
  
}
