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

// Constructeur 
Bibliotheque::Bibliotheque() {
   
    //maBibliotheque["K-Maro-Femme Like U"]="130;
    maBibliotheque["Pascal Obispo-Tombe pour elle"]="120"; 
    //maBibliotheque ["Marc Lavoine-Elle a les yeux revolver"]="80";
    myit=maBibliotheque.begin();
}

Bibliotheque :: Exception_biblio :: Exception_biblio(string ch): code(ch){}

string Bibliotheque :: Exception_biblio :: getException_biblio(){
    return code;
}



// Fonction qui recherche si la musique reçue est déjà dans la bibliothèque 

string Bibliotheque :: RechercherMusique (string musique){
    
    if (maBibliotheque.begin()==maBibliotheque.end()){
        throw Exception_biblio("La bibliothèque est vide"); 
    }
    
    while ((myit->first != musique) && (myit!=maBibliotheque.end())){
     myit ++ ; 
     
    }
    if (myit==maBibliotheque.end() && (myit->first != musique)){
         throw Exception_biblio("La musique n'est pas dans la bibliothèque"); 
      
        
    }
   
    return (myit->first);
}

//Destructeur
Bibliotheque::~Bibliotheque() {
}

