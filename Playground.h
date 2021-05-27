/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fichier en-tete contenant la declaration des fonctions 'init_deck' ,    |
 |'display_board', 'update' et 'victory'                                  |
 |Nom du fichier : Playground.h                                           |
 |=======================================================================*/

#pragma once

// Inclusion de librairies et fichiers annexes
#include <vector>
#include <string>
#include "Structures.h"

using namespace std;


vector<card> init_deck();

void display_board(vector<card> b[2][9], player& p1, player& p2, string pcur, int round);

void update(vector<card> b[2][9], vector<card>& d, player& p1, player& p2, string pcur, int index_card, int bound, int last[9]);

void detect_victory(player& p1, player& p2, win& victory);