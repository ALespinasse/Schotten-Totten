/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fichier en-tete contenant la declaration des fonctions                  |
 |'contest_bound_33' et 'contest_bound_3_12'                              |
 |Nom du fichier : Contest.h                                              |
 |=======================================================================*/

#pragma once

// Inclusion de librairies et fichiers annexes
#include <vector>
#include <string>
#include "Structures.h"

using namespace std;


void contest_bound_33(vector<card> b[2][9], player& p1, player& p2, int last[9], int num);

void contest_bound_3_12(vector<card> b[2][9], vector<card>& d, player& p1, player& p2, string pcur, int num);