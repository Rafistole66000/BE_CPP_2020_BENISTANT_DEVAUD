#include <unistd.h>
#include "core_simulation.h"

extern int luminosite_environnement;

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT);
  pinMode(0,OUTPUT);
  pinMode(2,INPUT); //capteur de température
  pinMode(3,OUTPUT); //intLed1
  pinMode(4,INPUT); //bouton1
}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  int val;
  int lum;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<6;i++){
      
      if(digitalRead(4)==ON)//Bouton and LED
          digitalWrite(3,HIGH);
      else
          digitalWrite(3,LOW);
    
    // lecture sur la pin 1 : capteur de temperature
    val=analogRead(1);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);

    lum=analogRead(2);       
    sprintf(buf,"luminosite %d",lum);
    Serial.println(buf);
    
    if(cpt%3==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      sprintf(buf,"%d",val);
      bus.write(1,buf,100);
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


