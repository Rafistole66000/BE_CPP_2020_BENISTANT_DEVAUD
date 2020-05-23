/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bibliotheque.h
 * Author: emmadevaud
 *
 * Created on 22 mai 2020, 14:17
 */
#include "Common_includes.h"

#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H


class Musique {
protected:
    char valeurs[10][UART_BUFFER_SIZE];
    int BPM ;
    
public : 
    Musique(); 
    void set_values(char val[10][UART_BUFFER_SIZE]);
    void set_BPM (int bpm);
    virtual ~Musique();
};

//--------------- Classe Bibliothèque -----------------
class Bibliotheque {
protected: 
    map <string,Musique> maBibliotheque ; 
    map <string,Musique> :: iterator myit ; 
    
    
public:
    Bibliotheque();
    
    void MiseAJourBiblio(char musique[UART_BUFFER_SIZE],int bpm, char val [10][UART_BUFFER_SIZE] );
    virtual ~Bibliotheque();
    
    class Exception_biblio{
    public :
     string code;
     Exception_biblio(string ch);
     string getException_biblio();
    };
     
     

};

#endif /* BIBLIOTHEQUE_H */

