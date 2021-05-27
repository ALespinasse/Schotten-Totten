/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fonction principale :                                                   |
 |Permettre a deux joueurs de s'affronter ou a un joueur d'affronter un   |
 |ordinateur sur une partie du jeu Schotten-Totten                        |
 |                                                                        |
 | Nom du fichier : Schotten-Totten.cpp                                   |
 |=======================================================================*/

// Inclusion de librairies et fichiers annexes
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Structures.h"
#include "Playground.h"
#include "Inputs.h"
#include "Contest.h"


using namespace std;


int main()
{
    int n_rounds; // nombre de manches de la partie

    player p1; // joueur 1
    player p2; // joueur 2

    vector<card> board[2][9]; // plateau de jeu

    string current_player; // joueur actif
    
    bool pvp; // true si joueur contre joueur, faux si joueur contre IA
    int last[9] = { 0,0,0,0,0,0,0,0,0 }; // dernier joueur ayant pose la derniere carte pour chaque borne
    int cont_bound; // borne contestee par le joueur actif
    int choice_card_bound[2] = { 0,0 }; // indice de la carte et borne choisies par le joueur actif
    int size1; // nombre de cartes posees par le joueur 1 sur la borne contestee
    int size2; // nombre de cartes posees par le joueur 2 sur la borne contestee

    // saisie des noms des joueurs et du nombre de manches
    cout << "Joueur contre joueur ? (1 ou 0) -> "; cin >> pvp;
    cout << "Joueur 1 : "; cin >> p1.name;
    if (pvp){
        cout << "Joueur 2 : "; cin >> p2.name;
    } else {
        p2.name = "ordinateur";
    }
    cout << "Nombre de manches de la partie : "; cin >> n_rounds;

    // determination du joueur qui commence
    srand((unsigned int)time(NULL));
    if (rand() % 2 + 1 == 1) {
        current_player = p2.name;
    } else {
        current_player = p1.name;
    }

    // initialisation de la pioche
    vector<card> deck = init_deck();

    // initialisation des mains des 2 joueurs
    for (int i = 0; i < 6; i++) {
        p1.hand.push_back(deck.back());
        deck.pop_back();
        p2.hand.push_back(deck.back());
        deck.pop_back();
    }

    int round = 1;
    win victory;
    victory.state = false;

    while (round <= n_rounds) {

        while (victory.state == false) {

            // nettoyage de la console
            system("cls");

            // changement du joueur actif a chaque debut de tour
            if (current_player == p1.name) {
                current_player = p2.name;
            } else {
                current_player = p1.name;
            }

            // affichage du plateau de jeu
            display_board(board, p1, p2, current_player, round);

	        if (current_player != "ordinateur") {
                // saisie de la borne a revendiquer
                cout << "Numero de la borne a revendiquer (de 1 a 9, 0 si aucune borne renvendiquee) : "; cin >> cont_bound;
	        } else {
		        // determination de la borne revendiquee par l'IA
                cont_bound = cont_selection_ia(board, deck, p1, p2);
	        }

            if (cont_bound > 0) {
                // revendication de la borne
                size1 = board[0][cont_bound - 1].size();
                size2 = board[1][cont_bound - 1].size();
                if ((size1 == 3) && (size2 == 3)) {
                    contest_bound_33(board, p1, p2, last, cont_bound); // les deux joueurs ont 3 cartes sur la borne
                }
                if (((current_player == p1.name) && (size1 == 3) && (size2 < 3)) || ((current_player == p2.name) && (size1 == 3) && (size2 < 3))) {
                    contest_bound_3_12(board, deck, p1, p2, current_player, cont_bound); // seul un des deux joueurs a 3 cartes sur la borne
                }
            }

            // detection de victoire
            detect_victory(p1, p2, victory);

            if (victory.state == false) {
                if (current_player != "ordinateur") {
		            // choix de la carte et de la borne a jouer par le joueur
                    card_bound_selection_player(board, p1, p2, current_player, choice_card_bound);
		        } else {
		            // choix de la carte et de la borne a jouer par l'IA
                    card_bound_selection_ia(board, deck, p1, p2, choice_card_bound);
		        }
                // mise a jour des elements du jeu 
                update(board, deck, p1, p2, current_player, choice_card_bound[0] - 1, choice_card_bound[1] - 1, last);
            }

        }

        // affichage du joueur ayant remporte la manche et mise a jour des nombres de points
        if (victory.player == p1.name) {
            p1.pts += 5;
            p2.pts += p2.bounds.size();
            cout << p1.name << " remporte la manche !" << endl;
        } else {
            p2.pts += 5;
            p1.pts += p1.bounds.size();
            cout << p2.name << " remporte la manche !" << endl;
        }
        victory.state = false;
        round++;
    }

    // affichage du joueur ayant remporte la partie
    cout << "La partie est terminee et ";
    if (p1.pts > p2.pts) {
        cout << p1.name << " l'emporte avec " << p1.pts << " points !";
    }
    if (p1.pts < p2.pts) {
        cout << p2.name << " l'emporte avec " << p2.pts << " points !";
    }
    if (p1.pts == p2.pts) {
        cout << p1.name << " et " << p2.name << " sont ex aequo avec " << p1.pts << " points !";
    }
    system("pause>0");
    return 0;
}