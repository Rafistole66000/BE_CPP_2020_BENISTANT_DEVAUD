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
    //maBibliotheque["Pascal Obispo-Tombe pour elle"]="120"; 
    //maBibliotheque ["Marc Lavoine-Elle a les yeux revolver"]="80";
    myit=maBibliotheque.begin();
}

Bibliotheque :: Exception_biblio :: Exception_biblio(string ch): code(ch){}

string Bibliotheque :: Exception_biblio :: getException_biblio(){
    return code;
}



// Fonction qui recherche si la musique reçue est déjà dans la bibliothèque 

string Bibliotheque :: RechercherMusique (char musique[UART_BUFFER_SIZE],char bpm[UART_BUFFER_SIZE]){
    string Resultat ; 
    //Si la bibliothèque est vide j'ajoute la musique directement
    if (maBibliotheque.begin()==maBibliotheque.end()){
        maBibliotheque[musique]=bpm; 
        myit=maBibliotheque.begin(); 
        cout << "---screen : Ajout de la musique à la bibliothèque : " << myit->first<< endl; 
        Resultat = myit->first; 
    }
    // Vérification si la musique est dans la bibliothèque
    while ((myit->first != musique) && (myit!=maBibliotheque.end())){
     myit ++ ; 
     
    }
    Resultat = myit->first;
    // Si elle n'y est pas après le parcours , je l'ajoute 
    if (myit==maBibliotheque.end() && (myit->first != musique)){
        maBibliotheque[musique]=bpm;  
        myit=maBibliotheque.end(); 
        cout << "---screen : Ajout de la musique à la bibliothèque : " << myit->first<<endl; 
        Resultat = myit->first; 
      
        
    }
   
    return (Resultat);
}

//Destructeur
Bibliotheque::~Bibliotheque() {
}

