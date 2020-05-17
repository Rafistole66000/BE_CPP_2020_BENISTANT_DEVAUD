/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "pulse_sensor.h"
using namespace std;

int Time_Between_Two_Pulse=500; //unit: ms

DigitalSensorPulse::DigitalSensorPulse():Device(),temps(Time_Between_Two_Pulse){
    alea=5;
    val=ceill(((float)1/temps)*60000);  //Converts time in ms into BPM 
}

void DigitalSensorPulse::run(){
  while(1){
    if(ptrmem!=NULL){
      temps = Time_Between_Two_Pulse + (rand()%alea); //Modify randomly the pulse value with +-5
      *ptrmem=ceill(((float)1/temps)*60000); ; //Update BPM value
    }
    usleep(temps*1000); //ms to us
  }
}