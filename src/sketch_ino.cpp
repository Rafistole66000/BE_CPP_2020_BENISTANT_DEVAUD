#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
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
  int puls;
  float mean_pulse;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<6;i++){
 
      
      if(digitalRead(4)==ON){//Bouton and LED
          //digitalWrite(3,HIGH);
                  
          if(!connected){
            //Turns the WIFI on
            connection_request=1; //On libère la fonction connect de ActuatorI2CWifiModule qui est bloqué sur une boucle while infini
            
            strcpy(buf,url.c_str());//Send URL
            bus.write(2,buf,100);
            trigger_get_website=1; 
            while(trigger_get_website){}//On attend que la fonction connect de ActuatorI2CWifiModule nous rende la main

            strcpy(buf,user.c_str());//Send User
            bus.write(2,buf,100);
            trigger_get_user=1; //On libère la fonction connect de ActuatorI2CWifiModule qui est bloqué sur une boucle while infini
            while(trigger_get_user){} //On attend que la fonction connect de ActuatorI2CWifiModule nous rende la main

            strcpy(buf,password.c_str());//Send User
            bus.write(2,buf,100);
            trigger_get_password=1;//On libère la fonction connect de ActuatorI2CWifiModule qui est bloqué sur une boucle while infini
            while(trigger_get_password){}//On attend que la fonction connect de ActuatorI2CWifiModule nous rende la main
            
            while(!connected){} //On attend que la connection wifi soit pleinement établie
          }
          
          if(!connected_bluetooth){
            //Turns the BLuetooth on
            connection_request_bluetooth=1; //On libère la fonction connect de ActuatorUARTBLuetoothModule qui est bloqué sur une boucle while infini
            
            while(!connected_bluetooth){} //On attend que la connection bluetooth soit pleinement établie
          }
      }
 
      mean_pulse = 0;
      
      for(int i=0; i<10; i++){
            puls=analogRead(5);       
            //sprintf(buf,"pulsation %d",puls);
            mean_pulse+=puls;
            //Serial.println(buf);
      }
      
      mean_pulse = mean_pulse/10.0;
      
    if(connected){
        mean_pulse += 5;
        mean_pulse = (int)mean_pulse/10 * 10; //Arrondi de la valeur de pulsation
        sprintf(buf,"Envoi d'un requête de musique à %dbpm",(int)mean_pulse);
        Serial.println(buf);
        sprintf(buf,"%d",(int)mean_pulse);
        bus.write(2,buf,100);
        while(!answer_ok){}
        answer_ok=0;
        
        //Ecrit ton code ici, la variable answer contient le nom de la musique pour la pulsation choisi
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


