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
    map <string,int> maBibliotheque ; 
    map <string,int> :: iterator myit ; 
    
public:
    Bibliotheque();
    string RechercherMusique(string musique);
    virtual ~Bibliotheque();
    
     
     

};

#endif /* BIBLIOTHEQUE_H */

