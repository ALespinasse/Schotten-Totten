/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fonctions secondaires 'contest_bound_33' et 'contest_bound_3_12'        |
 |                                                                        |
 |Nom du fichier : Input.cpp                                              |
 ========================================================================*/

// Inclusion de librairies et fichiers annexes
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Structures.h"
#include "Contest.h"
#include "Utilities.h"

using namespace std;


/*
Fonction contest_bound_33 :
Permet au joueur de contester une borne de son choix, dans le cas ou les 2 joueurs y ont place 3 cartes
*/
void contest_bound_33(vector<card> b[2][9], player& p1, player& p2, int last[9], int num)
{
    int strength[2] = { 0,0 }; // "force" de la combinaison des cartes de chaque joueur sur la borne jouee

    for (int i = 0; i < 2; i++) {
        strength[i] = get_actual_strength(b[i][num - 1]);
    }

    if (strength[0] > strength[1]) {
        cout << p1.name << " s'accapare la borne " << num << " !" << endl;
        p1.bounds.push_back(num);
    }
    if (strength[0] < strength[1]) {
        cout << p2.name << " s'accapare la borne " << num << " !" << endl;
        p2.bounds.push_back(num);
    }
    if (strength[0] == strength[1]) {

        // determination de la somme des valeurs des 3 cartes des joueurs 
        strength[0] = 0;
        strength[1] = 0;
        for (int i = 0; i < 3; i++) {
            strength[0] += b[0][num - 1][i].value;
            strength[1] += b[1][num - 1][i].value;
        }

        if (strength[0] > strength[1]) {
            cout << p1.name << " s'accapare la borne " << num << " !" << endl;
            p1.bounds.push_back(num);
        }
        if (strength[0] < strength[1]) {
            cout << p2.name << " s'accapare la borne " << num << " !" << endl;
            p2.bounds.push_back(num);
        }
        if (strength[0] == strength[1]) {
            if (last[num - 1] == 1) {
                cout << p1.name << " s'accapare la borne " << num << " !" << endl;
                p1.bounds.push_back(num);
            }
            else {
                cout << p2.name << " s'accapare la borne " << num << " !" << endl;
                p2.bounds.push_back(num);
            }
        }
    }
}


/*
Fonction contest_bound_3_12 :
Permet au joueur de contester une borne de son choix, dans le cas ou il y a place 3 cartes et l'adversaire 0, 1 ou 2
*/
void contest_bound_3_12(vector<card> b[2][9], vector<card>& d, player& p1, player& p2, string pcur, int num)
{
    int strength[2] = { 0,0 }; // "force" de la combinaison des cartes de chaque joueur sur la borne jouee

    if (pcur == p1.name) {
        strength[0] = get_actual_strength(b[0][num - 1]);
        strength[1] = get_potential_strength(b, d, p1, p2, 1, num - 1);
        if (strength[0] > strength[1]) {
            cout << p1.name << " s'accapare la borne " << num << " !" << endl;
            p1.bounds.push_back(num);
        }
    } else {
        strength[1] = get_actual_strength(b[1][num - 1]);
        strength[0] = get_potential_strength(b, d, p1, p2, 0, num - 1);
        if (strength[0] < strength[1]) {
            cout << p2.name << " s'accapare la borne " << num << " !" << endl;
            p2.bounds.push_back(num);
        }
    }

}