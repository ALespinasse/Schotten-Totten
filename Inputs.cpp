/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fonctions secondaires 'card_bound_selection_player', 'cont_selection_ia'|
 |et 'card_bound_selection_ia'                                            |  
 |                                                                        |
 |Nom du fichier : Input.cpp                                              |
 ========================================================================*/

// Inclusion de librairies et fichiers annexes
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Structures.h"
#include "Inputs.h"
#include "Utilities.h"

using namespace std;


/*
Fonction card_bound_selection_player :
Permet au joueur de selectionner la carte qu'il va jouer et la borne sur laquelle placer sa carte, en verifiant que cette borne est disponible 
*/
void card_bound_selection_player(vector<card> b[2][9], player& p1, player& p2, string pcur, int choice[2])
{
    bool find1 = false; // true si la borne choisie appartient deja au joueur 1
    bool find2 = false; // true si la borne choisie appartient deja au joueur 2
    bool possible = false; // true s'il est possible de poser sa carte sur la borne choisie
    
    // saisie de la carte choisie
    cout << "Carte choisie (entier de 1 a 6) : "; cin >> choice[0];    

    int n = 0;
    while (possible == false) {
        
        if (n > 0) {
            cout << "Choix impossible, veuillez recommencer..." << endl;
            cout << endl;
        }

        // choix de la borne
        cout << "Borne choisie (entier de 1 a 9) : "; cin >> choice[1];

        possible = true;
        find1 = find(p1.bounds.begin(), p1.bounds.end(), choice[1]) != p1.bounds.end();
        find2 = find(p2.bounds.begin(), p2.bounds.end(), choice[1]) != p2.bounds.end();

        if (((pcur == p1.name) && (b[0][choice[1] - 1].size() == 3)) || find1 || find2) {
            possible = false;
        }
        if (((pcur == p2.name) && (b[1][choice[1] - 1].size() == 3)) || find1 || find2) {
            possible = false;
        }
        cout << endl;
        n++;
    }
    cout << endl;
}


/*
Fonction cont_selection_ia :
Determination de la borne a contestee par l'IA
*/
int cont_selection_ia(vector<card> b[2][9], vector<card>& d, player& p1, player& p2)
{
    int strength_ia = 0; // force de la combinaison de cartes de l'IA sur la borne considérée
    int strength_player = 0; // force de la combinaison de cartes du joueur sur la borne considérée
    int bound = 0;

    for (int i = 0; i < 9; i++) {
        if (b[1][i].size() == 3) {
            strength_ia = get_actual_strength(b[1][i]);
            if (b[0][i].size() == 3) {
                strength_player = get_actual_strength(b[0][i]);
            } else {
                strength_player = get_potential_strength(b, d, p1, p2, 0, i);
            }
            if (strength_ia > strength_player) {
                bound = i + 1;
            }
        }
    }
    return bound;
}


/*
Fonction card_bound_selection_ia :
Determination de la carte jouee par l'IA et la borne sur laquelle la placer
*/
void card_bound_selection_ia(vector<card> b[2][9], vector<card>& d, player& p1, player& p2, int choice[2])
{
    int strength_player = 0; // force de la combinaison de cartes du joueur sur la borne considérée
    bool find1 = false; // true si la borne choisie appartient deja au joueur 1
    bool find2 = false; // true si la borne choisie appartient deja au joueur 2
    int strength_ia = 0;
    int strength_ia_temp = 0;
    int size_temp;

    for (int i = 0; i < 9; i++) {
        find1 = find(p1.bounds.begin(), p1.bounds.end(), i + 1) != p1.bounds.end();
        find2 = find(p2.bounds.begin(), p2.bounds.end(), i + 1) != p2.bounds.end();
	    if (!(find1) && !(find2) && (b[1][i].size() < 3)) {
            
            //determination de la force de la combinaison du joueur
            if (b[0][i].size() == 3) {
                strength_player = get_actual_strength(b[0][i]);
            }
            else {
                strength_player = get_potential_strength(b, d, p1, p2, 0, i);
            }
            
            for (int j = 0; j < 6; j++) {

                //ajout virtuel d'une carte clan sur la borne
                b[1][i].push_back(p2.hand[j]);

                //determination de la taille de la combinaison ainsi formee
                size_temp = b[1][i].size();
                
                if (size_temp < 3) {
                    
                    for (int k = 0; k < 6; k++) {
                        if (k != j) {

                            //ajout virtuel d'une carte clan sur la borne
                            b[1][i].push_back(p2.hand[k]);

                            //determination de la taille de la combinaison ainsi formee
                            size_temp = b[1][i].size();

                            if (size_temp < 3) {

                                for (int l = 0; l < 6; l++) {
                                    if ((l != k) && (k != j) && (l != j)) {
                                        //ajout virtuel d'une carte clan sur la borne
                                        b[1][i].push_back(p2.hand[l]);

                                        strength_ia_temp = get_actual_strength(b[1][i]);
                                        if (strength_ia_temp > strength_ia) {
                                            strength_ia = strength_ia_temp;
                                            choice[0] = j + 1;
                                            choice[1] = i + 1;
                                        }
                                        //retrait de la carte clan ajoutee sur la borne
                                        b[1][i].pop_back();
                                    }
                                }

                            } else {
                                strength_ia_temp = get_actual_strength(b[1][i]);
                                if (strength_ia_temp > strength_ia) {
                                    strength_ia = strength_ia_temp;
                                    choice[0] = j + 1;
                                    choice[1] = i + 1;
                                }
                            }
                            //retrait de la carte clan ajoutee sur la borne
                            b[1][i].pop_back();
                        }
                    }

                } else {
                    strength_ia_temp = get_actual_strength(b[1][i]);
                    if (strength_ia_temp > strength_ia) {
                        strength_ia = strength_ia_temp;
                        choice[0] = j + 1;
                        choice[1] = i + 1;
                    }
                }    
                //retrait de la carte clan ajoutee sur la borne
                b[1][i].pop_back();
            }
	    }
    }
}
