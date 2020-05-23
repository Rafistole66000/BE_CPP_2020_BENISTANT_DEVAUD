#include "board_manager.h"

Board_manager my_board_manager;
bool devices_on=0;

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

        sprintf(buf,"Envoi d'un requête de musique à %d bpm",mean_pulse);
        Serial.println(buf);
        sprintf(buf,"%d",mean_pulse);
        bus.write(2,buf,100);
        while(!answer_ok){}
        answer_ok=0;
        
        //Ecrit ton code ici, la variable answer contient le nom de la musique pour la pulsation choisie
        sprintf(buf,"%s",answer);
        Serial.println(buf);
        bus_uart.write(1,buf,100); 
        trigger_get_song=1; 
        while(trigger_get_song){}
        
        sprintf(buf,"%d",(int)mean_pulse);
        bus_uart.write(1,buf,100); 
        trigger_get_bpm=1; 
        while(trigger_get_bpm){}
            
    }
    
    if(cpt%10==0 && cpt!=0){
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


