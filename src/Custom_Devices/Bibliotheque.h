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

#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include "Common_includes.h"


class Musique {
protected:
    char valeurs[10][UART_BUFFER_SIZE];
    int BPM ;
    
public : 
    Musique(); 
    void set_values(char val[10][UART_BUFFER_SIZE]);
    void set_BPM (int bpm);
    char* get_Note(int index);
    
    virtual ~Musique();
    
    friend ostream & operator<<(ostream &os, const Musique& ma_musique);
    
};

//--------------- Classe Bibliothèque -----------------
class Bibliotheque {
protected: 
    map <string,Musique> maBibliotheque ;    
    
public:
    Bibliotheque();
    
    void MiseAJourBiblio(char musique[UART_BUFFER_SIZE],int bpm, char val [10][UART_BUFFER_SIZE] );
    Musique& get_Musique(char* index);
    virtual ~Bibliotheque();
    
    class Exception_biblio{
    public :
     string code;
     Exception_biblio(string ch);
     string getException_biblio();
    };
     
     

};

#endif /* BIBLIOTHEQUE_H */

