/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bibliotheque.cpp
 * Author: emmadevaud
 * 
 * Created on 22 mai 2020, 14:17
 */

#include "Bibliotheque.h"
#include "Common_includes.h"
using namespace std;
Bibliotheque::Bibliotheque() {
    maBibliotheque["Pascal Obispo-Tombe pour elle"]=120; 
    myit=maBibliotheque.begin();
}

string Bibliotheque :: RechercherMusique (string musique){
    
    cout << myit->first << endl ; 
    int Trouve =0;
    while ((myit->first != musique) && (myit!=maBibliotheque.end())){
     myit ++ ; 
     
    }
    return (myit->first);
}

Bibliotheque::~Bibliotheque() {
}

