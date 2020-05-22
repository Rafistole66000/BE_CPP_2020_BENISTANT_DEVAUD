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

class Bibliotheque {
protected: 
    map <string,string> maBibliotheque ; 
    map <string,string> :: iterator myit ; 
    
    
public:
    Bibliotheque();
    
    string RechercherMusique(char musique[UART_BUFFER_SIZE],char bpm[UART_BUFFER_SIZE] );
    virtual ~Bibliotheque();
    
    class Exception_biblio{
    public :
     string code;
     Exception_biblio(string ch);
     string getException_biblio();
    };
     
     

};

#endif /* BIBLIOTHEQUE_H */

