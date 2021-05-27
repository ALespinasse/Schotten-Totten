/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fichier en-tete contenant la declaration des fonctions                  |
 |'get_actual_strength' et 'get_potential_strength'                       |
 |Nom du fichier : Utilities.h                                            |
 |=======================================================================*/

#pragma once

// Inclusion de librairies et fichiers annexes
#include <vector>
#include <string>
#include "Structures.h"


int get_actual_strength(vector<card>& comb);

int get_potential_strength(vector<card> b[2][9], vector<card>& d, player& p1, player& p2, int ind, int bound);