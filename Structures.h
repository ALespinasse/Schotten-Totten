/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fichier en-tete contenant la description des structures 'card' et       |
 |'player'                                                                |
 |Nom du fichier : Structures.h                                           |
 |=======================================================================*/

#pragma once

// Inclusion de librairies et fichiers annexes
#include <string>
#include <vector>

using namespace std;


// card est un enregistrement ayant 2 champs
struct card
{
    string color = ""; // couleur de la carte (rouge, vert, bleu, orange, jaune ou violet)
    int value = 0; // valeur de la carte (entier de 1 a 9)
};

// player est un enregistrement ayant 4 champs
struct player
{
    string name = ""; // nom du joueur
    vector<card> hand; // vecteur contenant la main du joueur (6 cartes 'card')
    vector<int> bounds; // vecteur contenant les bornes detenues par le joueur
    int pts = 0; // nombre de points du joueur
};

// win est un enregistrement ayant 2 champs
struct win
{
    bool state = false; // vrai si la manche est remportee par l'un des joueurs
    string player = ""; // nom du joueur remportant la manche
};