/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "board_manager.h"

void Board_manager::connect_to_Internet(Board& ma_board){
            
    char buf[100];
    
    //Turns the WIFI on
    connection_request=1; //On libère la fonction connect de ActuatorI2CWifiModule qui est bloqué sur une boucle while infini

    strcpy(buf,url.c_str());//Send URL
    ma_board.bus.write(2,buf,100);
    trigger_get_website=1; 
    while(trigger_get_website){}//On attend que la fonction connect de ActuatorI2CWifiModule nous rende la main

    strcpy(buf,user.c_str());//Send User
    ma_board.bus.write(2,buf,100);
    trigger_get_user=1; //On libère la fonction connect de ActuatorI2CWifiModule qui est bloqué sur une boucle while infini
    while(trigger_get_user){} //On attend que la fonction connect de ActuatorI2CWifiModule nous rende la main

    strcpy(buf,password.c_str());//Send User
    ma_board.bus.write(2,buf,100);
    trigger_get_password=1;//On libère la fonction connect de ActuatorI2CWifiModule qui est bloqué sur une boucle while infini
    while(trigger_get_password){}//On attend que la fonction connect de ActuatorI2CWifiModule nous rende la main

    while(!connected){} //On attend que la connection wifi soit pleinement établie
}

void Board_manager::connect_to_Bluetooth(){
    //Turns the BLuetooth on
    connection_request_bluetooth=1; //On libère la fonction connect de ActuatorUARTBLuetoothModule qui est bloqué sur une boucle while infini

    while(!connected_bluetooth){} //On attend que la connection bluetooth soit pleinement établie
}

int Board_manager::compute_mean_pulse_10values(Board& ma_board){
    
    float result=0;
    int cumul=0;
    
    for(int i=0; i<10; i++){ //On recupère 10 valeur
      cumul+=ma_board.analogRead(5);       
      //sprintf(buf,"pulsation %d",puls);
      //Serial.println(buf);
    }
    
    result = cumul/10.0; //On divise par 10
    
    result += 5;
    result = (int)result/10 * 10; //Arrondi de la valeur de pulsation
    
    return (int)result;
}

void Board_manager::send_music_request(Board& ma_board, int mean_pulse){
    
    char buf[100];
    
    sprintf(buf,"Envoi d'un requête de musique à %d bpm",mean_pulse);
    ma_board.Serial.println(buf);
    sprintf(buf,"%d",mean_pulse);
    ma_board.bus.write(2,buf,100);
    while(!answer_ok){}
    answer_ok=0;
}

void Board_manager::send_music_to_bluetooth_device(Board& ma_board,Bibliotheque& ma_biblio,char* music){
    char buf[100];
    
    for (int i=0;i<10;i++){
        sprintf(buf,"%s", ma_biblio.get_Musique(music).get_Note(i));
        ma_board.bus_uart.write(1,buf,100); 
        trigger_get_values =1;
        while(trigger_get_values){}
    }
}