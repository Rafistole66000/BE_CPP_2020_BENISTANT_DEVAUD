
#include "mydevices.h"

using namespace std;

int luminosite_environnement=300;

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}

// classe I2CActuatorScreen
UARTActuatorScreen::UARTActuatorScreen ():Device(){
  }

void UARTActuatorScreen::run(){
  while(1){
    if ( (UARTbus!=NULL)&&!(UARTbus->isEmptyRegister(UARTaddr))){
      Device::UARTbus->requestFrom(UARTaddr, buf, UART_BUFFER_SIZE);
      cout << "---UART :"<< buf << endl;
    }
    sleep(1);
    }
}

// classe AnalogSensorLuminosity

AnalogSensorLuminosity::AnalogSensorLuminosity(int d):Device(),val(luminosite_environnement),temps(d){
  alea=1;
}
  
void AnalogSensorLuminosity::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL){
        val = luminosite_environnement;
        *ptrmem=val+alea;   
    }
    sleep(temps);
  }
}

// classe IntelligentDigitalActutatorLED

IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t): DigitalActuatorLED(t){
    previous_state = LOW;
}

void IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
        state=*ptrmem;
 
    if (state==LOW){
        cout << "((((intLed eteint))))\n";
        
        if(previous_state==HIGH){
            previous_state = LOW;
            luminosite_environnement-=50;
        }
    }
    else if(state==HIGH){
        cout << "((((intLed allume))))\n";
        
        if(previous_state==LOW){
            previous_state = HIGH;
            luminosite_environnement+=50;
        }
    }
    sleep(temps);
    }
}

// classe ExternalDigitalSensorButton

ExternalDigitalSensorButton::ExternalDigitalSensorButton(int t) : Device(),state(OFF), temps(t){};

void ExternalDigitalSensorButton::run(){
  while(1){
      if(state == OFF){
        if(ifstream("on.txt")){// le fichier existe
           state = ON;
           if(ptrmem!=NULL)
                *ptrmem=state;
        }
        else
            cout << "Bouton OFF" << endl;
      }
      if(state == ON){
        if(!ifstream("on.txt")){// le fichier existe
           state = OFF;
           if(ptrmem!=NULL)
                *ptrmem=state;
        }
        cout << "Bouton ON" << endl;
      }
    sleep(temps);
  }
}