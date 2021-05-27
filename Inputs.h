/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fichier en-tete contenant la declaration des fonctions                  |
 |'card_bound_selection_player', 'cont_selection_ia' et                   |
 |'card_bound_selection_ia'                                               |
 |Nom du fichier : Inputs.h                                               |
 |=======================================================================*/

#pragma once

// Inclusion de librairies et fichiers annexes
#include <vector>
#include <string>
#include "Structures.h"

using namespace std;


void card_bound_selection_player(vector<card> b[2][9], player& p1, player& p2, string pcur, int choice[2]);

int cont_selection_ia(vector<card> b[2][9], vector<card>& d, player& p1, player& p2);

void card_bound_selection_ia(vector<card> b[2][9], vector<card>& d, player& p1, player& p2, int choice[2]);