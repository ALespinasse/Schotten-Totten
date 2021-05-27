/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fonctions secondaires 'display_board', 'update  et 'victory'            |
 |                                                                        |
 |Nom du fichier : playground.cpp                                         |
 ========================================================================*/

// Inclusion de librairies et fichiers annexes
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Structures.h"
#include "Playground.h"

using namespace std;


/*
Fonction init_deck :
Fournie une pioche de 54 cartes melangees
*/
vector<card> init_deck()
{
    vector<card> deck;
    string list_colors[6] = { "rouge","vert","bleu","orange","jaune","violet" };
    card x;

    srand((unsigned int)time(NULL));

    // ajout des 54 cartes dans la pioche
    for (int i = 0; i < 6; i++) {
        for (int j = 1; j < 10; j++) {
            x.color = list_colors[i];
            x.value = j;
            deck.push_back(x);
        }
    }

    // melange de la pioche
    random_shuffle(deck.begin(), deck.end());

    return deck;
}


/*
Fonction display_board :
Afficher la plateau de jeu mis a jour a chaque tour de joueur
*/
void display_board(vector<card> b[2][9], player& p1, player& p2, string pcur, int round)
{
    cout << "====================================================================" << endl;
    cout << "============================= MANCHE " << round << " =============================" << endl;
    cout << "====================================================================" << endl;
    cout << p1.name << " a " << p1.pts << " points" << endl;
    cout << p2.name << " a " << p2.pts << " points" << endl;
    cout << endl;
    cout << "                             PLATEAU DE JEU                         " << endl;
    cout << "--------------------------------------------------------------------" << endl;
    for (int i = 1; i < 10; i++) {
        cout << "Borne " << i << " :" << endl;
        cout << "Cartes clan de " << p1.name << " -> ";
        if (b[0][i - 1].size() > 0) {
            for (size_t j = 0; j < b[0][i - 1].size(); j++) {
                cout << b[0][i - 1][j].color << " " << b[0][i - 1][j].value << " | ";
            }
        }
        else {
            cout << "N/a";
        }
        cout << endl;
        cout << "Cartes clan de " << p2.name << " -> ";
        if (b[1][i - 1].size() > 0) {
            for (size_t j = 0; j < b[1][i - 1].size(); j++) {
                cout << b[1][i - 1][j].color << " " << b[1][i - 1][j].value << " | ";
            }
        }
        else {
            cout << "N/a";
        }
        cout << endl;
        if (find(p1.bounds.begin(), p1.bounds.end(), i) != p1.bounds.end()) {
            cout << p1.name << " la possede! " << endl;
        }
        if (find(p2.bounds.begin(), p2.bounds.end(), i) != p2.bounds.end()) {
            cout << p2.name << " la possede! " << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;
    }
    cout << endl;
    cout << p1.name << " possede les bornes : ";
    for (size_t i = 0; i < p1.bounds.size(); i++) {
        cout << p1.bounds[i] << " ";
    }
    cout << endl;
    cout << p2.name << " possede les bornes : ";
    for (size_t i = 0; i < p2.bounds.size(); i++) {
        cout << p2.bounds[i] << " ";
    }
    cout << endl;
    cout << endl;
    cout << p1.name << " a en main -> ";
    for (int i = 0; i < 6; i++) {
        cout << p1.hand[i].color << " " << p1.hand[i].value << " | ";
    }
    cout << endl;
    cout << p2.name << " a en main -> ";
    for (int i = 0; i < 6; i++) {
        cout << p2.hand[i].color << " " << p2.hand[i].value << " | ";
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "C'est au tour de " << pcur << " de jouer !" << endl;
    cout << endl;
}

/*
Fonction update :
Met a jour le plateau de jeu, la pioche et la main des joueurs apres un tour de joueur
*/
void update(vector<card> b[2][9], vector<card>& d, player& p1, player& p2, string pcur, int index_card, int bound, int last[9])
{
    if (pcur == p1.name) {
        b[0][bound].push_back(p1.hand[index_card]); // ajout de la carte clan du joueur sur la borne
        p1.hand.erase(p1.hand.begin() + index_card); // retrait de la carte jouee de la main du joueur
        p1.hand.push_back(d.back()); // ajout d'une carte de la pioche dans la main du joueur
        d.pop_back(); // retrait de la derniere carte de la pioche
        last[bound] = 1; // stockage de l'info de dernier ajout de carte sur la borne
    } else {
        b[1][bound].push_back(p2.hand[index_card]);
        p2.hand.erase(p2.hand.begin() + index_card);
        p2.hand.push_back(d.back());
        d.pop_back();
        last[bound] = 2;
    }
}

/*
Fonction victory :
Detecte si un joueur remporte la manche active
*/
void detect_victory(player& p1, player& p2, win& victory)
{
    // si un des joueur a 5 bornes
    if (p1.bounds.size() == 5) {
        victory.state = true;
        victory.player = p1.name;
    }
    if (p2.bounds.size() == 5) {
        victory.state = true;
        victory.player = p2.name;
    }

    // si un des joueurs a + de 3 bornes avec 3 bornes qui se suivent
    if ((p1.bounds.size() == 3) || (p1.bounds.size() == 4)) {
        for (size_t i = 0; i < p1.bounds.size(); i++) {
            if ((find(p1.bounds.begin(), p1.bounds.end(), p1.bounds[i] - 1) != p1.bounds.end()) && (find(p1.bounds.begin(), p1.bounds.end(), p1.bounds[i] + 1) != p1.bounds.end())) {
                victory.state = true;
                victory.player = p1.name;
            }
        }
    }
    if ((p2.bounds.size() == 3) || (p2.bounds.size() == 4)) {
        for (size_t i = 0; i < p2.bounds.size(); i++) {
            if ((find(p2.bounds.begin(), p2.bounds.end(), p2.bounds[i] - 1) != p2.bounds.end()) && (find(p2.bounds.begin(), p2.bounds.end(), p2.bounds[i] + 1) != p2.bounds.end())) {
                victory.state = true;
                victory.player = p2.name;
            }
        }
    }
}