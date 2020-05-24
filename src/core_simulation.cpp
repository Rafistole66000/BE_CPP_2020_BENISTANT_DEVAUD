
#include <thread>
#include <unistd.h>
#include <string.h>

#include "core_simulation.h"

// class BoardException
int BoardException::get(){return num;}

string BoardException::text(){
  string s;
  switch(num){
  case SPEED : s=string("mauvaise vitesse de la liaison terminal");break;
  case INOUT : s=string("mauvaise utilisation du sens de l'entrée/sortie"); break;
  case ADDRESS : s=string("mauvaise adresse de la pin"); break;
  case SIZE : s=string("taille erronée"); break;
  case EMPTY: s=string("zone vide"); break;
  default: s=string("erreur inconnue");
  }
  return s;
}

// classe terminale
void Terminal::begin(int speed){
  if (speed!=9600){
    cerr << "wrong speed\n";
    throw BoardException(SPEED);
  }
}
void Terminal::println(string s){
  cout << endl << "Serial: "<< s<<endl;
}

// representatoin du bus I2C
I2C::I2C(){
  for(int i=0;i<MAX_I2C_DEVICES;i++){
    registre[i]=new char[I2C_BUFFER_SIZE];
    vide[i]=true;
  }
}

bool I2C::isEmptyRegister(int addr){
  bool result=true;
  if ((addr>=0)&&(addr<MAX_I2C_DEVICES))
    result=vide[addr];
  else
    throw BoardException(ADDRESS);
  return result;
}

int I2C::write(int addr, char* bytes, int size){
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  if ((size<0)||(size>I2C_BUFFER_SIZE))
    throw BoardException(SIZE);
  tabmutex[addr].lock();
  memcpy(registre[addr],bytes,size*sizeof(char));
  vide[addr]=false;
  tabmutex[addr].unlock();
  return size;
}

int I2C::requestFrom(int addr, char* bytes, int size){
  int result =0;
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  if ((size<0)||(size>I2C_BUFFER_SIZE))
    throw BoardException(SIZE);
  if (vide[addr]==false){
    tabmutex[addr].lock();
    memcpy(bytes,registre[addr],size*sizeof(char));
    vide[addr]=true;
    tabmutex[addr].unlock();
    result =size;
  }
  return result;
}

char * I2C::getRegistre(int addr){
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  return (registre[addr]);
}

bool* I2C::getVide(int addr){
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  return (&vide[addr]);
}

// representatoin du bus UART
UART::UART(){
  for(int i=0;i<MAX_UART_DEVICES;i++){
    registre[i]=new char[UART_BUFFER_SIZE];
    vide[i]=true;
  }
}

bool UART::isEmptyRegister(int addr){
  bool result=true;
  if ((addr>=0)&&(addr<MAX_UART_DEVICES))
    result=vide[addr];
  else
    throw BoardException(ADDRESS);
  return result;
}

int UART::write(int addr, char* bytes, int size){
  if ((addr<0)||(addr>=MAX_UART_DEVICES))
    throw BoardException(ADDRESS);
  if ((size<0)||(size>UART_BUFFER_SIZE))
    throw BoardException(SIZE);
  tabmutex[addr].lock();
  memcpy(registre[addr],bytes,size*sizeof(char));
  vide[addr]=false;
  tabmutex[addr].unlock();
  return size;
}

int UART::requestFrom(int addr, char* bytes, int size){
  int result =0;
  if ((addr<0)||(addr>=MAX_UART_DEVICES))
    throw BoardException(ADDRESS);
  if ((size<0)||(size>UART_BUFFER_SIZE))
    throw BoardException(SIZE);
  if (vide[addr]==false){
    tabmutex[addr].lock();
    memcpy(bytes,registre[addr],size*sizeof(char));
    vide[addr]=true;
    tabmutex[addr].unlock();
    result =size;
  }
  return result;
}

char * UART::getRegistre(int addr){
  if ((addr<0)||(addr>=MAX_UART_DEVICES))
    throw BoardException(ADDRESS);
  return (registre[addr]);
}

bool* UART::getVide(int addr){
  if ((addr<0)||(addr>=MAX_UART_DEVICES))
    throw BoardException(ADDRESS);
  return (&vide[addr]);
}


// classe generique reprenstant un capteur/actionneur
Device::Device(){
  ptrtype=NULL;
  ptrmem=NULL;
  i2caddr=-1;
  i2cbus=NULL;
}

void Device::run(){
  while(1){
    cout << "empty device\n";
    sleep(3);
  }
}

void Device::setPinMem(unsigned short* ptr,enum typeio *c){
  ptrtype=c;
  ptrmem=ptr;
}

void Device::setI2CAddr(int addr, I2C * bus){
  i2caddr=addr;
  i2cbus=bus;
}

void Device::setUARTAddr(int addr, UART * bus_uart){
  UARTaddr=addr;
  UARTbus=bus_uart;
}

// classe representant une carte arduino
void Board::run(){
  try{
    setup();
    while(1) loop();
  }
  catch(BoardException e){
    cout <<"exception: "<<e.text() <<endl;
  }
}

void Board::pin(int p, Device& s){
  s.setPinMem(&io[p], &stateio[p]);
  tabthreadpin[p]=new thread(&Device::run,&s);
  
}

void Board::pinMode(int p,enum typeio t){
  stateio[p]=t;
}

void Board::digitalWrite(int i, int l){
  if (stateio[i]==OUTPUT)
    io[i]=l;
  else
    throw BoardException(INOUT);
}

int Board::digitalRead(int i){
  int   result=0;
  if (stateio[i]==INPUT)
    result= io[i];
  else
    throw BoardException(INOUT);
  return result;
}

void Board::analogWrite(int i, int l){
  if (stateio[i]==OUTPUT)
    io[i]=l;
  else
    throw BoardException(INOUT);
}

int Board::analogRead(int i){
  int   result=0;
  if (stateio[i]==INPUT)
    result= io[i];
  else
    throw BoardException(INOUT);
  return result;
}

void Board::i2c(int addr,Device& dev){
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  dev.setI2CAddr(addr,&bus);
  tabthreadbus[addr]=new thread(&Device::run,&dev);
}

void Board::uart(int addr,Device& dev){
  if ((addr<0)||(addr>=MAX_UART_DEVICES))
    throw BoardException(ADDRESS);
  dev.setUARTAddr(addr,&bus_uart);
  tabthreadbusUART[addr]=new thread(&Device::run,&dev);
}
