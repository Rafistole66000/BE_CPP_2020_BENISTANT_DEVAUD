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
using namespace std;


//----------------------- Classe Musique ---------------------------------
//Constructeur
Musique :: Musique(){
    
    int i ;
    int j ; 
    for(i=0; i<10; i++){
        for(j = 0; j<1024 ; j++)
            valeurs[i][j]='\0';
    }
    BPM=0;
}

// Destructeur 
Musique :: ~Musique() {
}

// Assesseurs 
void Musique :: set_values(char val[10][UART_BUFFER_SIZE]) {
    int i ;
    int j ; 
    for(i=0; i<10; i++){
        for(j = 0; j<1024 ; j++)
            valeurs[i][j]=val[i][j];
    }
    
}

void Musique :: set_BPM (int bpm){
    BPM=bpm ; 
}

//Redefinition de l'opérateur <<
ostream & operator<<(ostream &os, const Musique& ma_musique){
    os << "BPM: " << ma_musique.BPM << endl;
    os << "Note: ";
    for(int i=0; i<10; i++)
        os << ma_musique.valeurs[i] << " ";
    os << endl;
    return os;
}

// ---------------------- Classe Bibliothèque ----------------------------
// Constructeur 
Bibliotheque::Bibliotheque() {
   
    //maBibliotheque["K-Maro-Femme Like U"]="130;
    //maBibliotheque["Pascal Obispo-Tombe pour elle"]="120"; 
    //maBibliotheque ["Marc Lavoine-Elle a les yeux revolver"]="80";
}

Bibliotheque :: Exception_biblio :: Exception_biblio(string ch): code(ch){}

string Bibliotheque :: Exception_biblio :: getException_biblio(){
    return code;
}



// Fonction qui recherche si la musique reçue est déjà dans la bibliothèque 

void Bibliotheque :: MiseAJourBiblio(char musique[UART_BUFFER_SIZE],int bpm,char val[10][UART_BUFFER_SIZE]){
   
    map <string,Musique>::iterator iter_biblio=maBibliotheque.begin();
    
    //Si la bibliothèque est vide j'ajoute la musique directement 
    if (maBibliotheque.begin()==maBibliotheque.end()){
        Musique maMusique=Musique() ;
        maMusique.set_values(val);
        maMusique.set_BPM(bpm);
        maBibliotheque[musique]=maMusique; 
        cout << "---screen : Ajout de la musique à la bibliothèque ->  " << musique << endl; 
        cout << maMusique;
       
    }else{
        
    // Vérification si la musique est dans la bibliothèque
         while ((iter_biblio->first != musique) && (iter_biblio!=maBibliotheque.end())){
            iter_biblio++ ;     
        }
        
         if(iter_biblio->first != musique) //Si elle y est
            cout << "La musique est déjà dans la bibliothèque "<< endl ;
         
         else{ // Si elle n'y est pas après le parcours , je l'ajoute 
                Musique maMusique=Musique() ;
                maMusique.set_values(val);
                maMusique.set_BPM(bpm);
                maBibliotheque[musique]=maMusique;
                cout << "---screen : Ajout de la musique à la bibliothèque ->  " << musique << endl; 
                cout << maMusique;
            }
         }  
    }

//Destructeur
Bibliotheque::~Bibliotheque() {
}

