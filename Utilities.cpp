/*=========================================================================
 |  LESPINASSE Antoine                                    15 / 11 / 2020  |
 |                            Jeu Schotten-Totten                         |
 |------------------------------------------------------------------------|
 |Fonctions secondaires 'get_actual_strength' et 'get_potential_strength' |
 |                                                                        |
 |Nom du fichier : Utilities.cpp                                          |
 ========================================================================*/

 // Inclusion de librairies et fichiers annexes
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Structures.h"
#include "Utilities.h"

using namespace std;


/*
Fonction get_actual_strength :
Permet de determiner la force d'une combinaison de 3 cartes sur une borne
*/
int get_actual_strength(vector<card>& comb)
{
    int strength = 0; // force de la combinaison
    bool found_prev = false; // true si carte de valeur v-1 trouvee (v = valeur carte consideree)
    bool found_fol = false; // true si carte de valeur v+1 trouvee (v = valeur carte consideree)
    int values[3];

    for (int i = 0; i < 3; i++) {
        values[i] = comb[i].value;
    }

    // 3 cartes quelconques
    strength = 1;

    // suite
    for (int i = 0; i < 3; i++) {
        found_prev = find(begin(values), end(values), values[i] - 1) != end(values);
        found_fol = find(begin(values), end(values), values[i] + 1) != end(values);
        if (found_prev && found_fol) {
            strength = 2;
        }
    }

    // meme couleur
    if ((comb[0].color == comb[1].color) && (comb[1].color == comb[2].color)) {
        if (strength == 1) {
            strength = 3; // 3 meme couleur
        }
        else {
            strength = 5; // suite & 3 meme couleur
        }
    }

    // meme valeur
    if ((comb[0].value == comb[1].value) && (comb[1].value == comb[2].value)) {
        strength = 4;
    }

    return strength;
}


int get_potential_strength(vector<card> b[2][9], vector<card>& d, player& p1, player& p2, int ind, int bound)
{
    int strength = 0; // force de la combinaison

    bool found_inf1 = false; // carte de valeur v-2 encore disponible
    bool found_inf2 = false; // carte de valeur v-1 encore disponible
    bool found_sup1 = false; // carte de valeur v+1 encore disponible
    bool found_sup2 = false; // carte de valeur v+2 encore disponible
    int count_color = 0;
    int count_value = 0;
    bool found_same_color = false; // meme couleur encore disponible
    bool found_same_value = false; // brelan encore disponible
    int strength_temp;

    int n_cards = b[ind][bound].size(); 
    vector<card> comb = b[ind][bound];
    vector<string> remaining_color;
    vector<int> remaining_value;

    for (size_t i = 0; i < d.size(); i++) {
        remaining_color.push_back(d[i].color);
        remaining_value.push_back(d[i].value);
    }
    for (int i = 0; i < 6; i++) {
        remaining_color.push_back(p1.hand[i].color);
        remaining_color.push_back(p2.hand[i].color);
        remaining_value.push_back(p1.hand[i].value);
        remaining_value.push_back(p2.hand[i].value);
    }

    switch (n_cards)
    {
    case 0:
        for (size_t i = 0; i < remaining_color.size(); i++) {
            
            // cartes quelconques possibles
            strength_temp = 1;

            if (remaining_value[i] > 1) {
                found_inf1 = find(begin(remaining_value), end(remaining_value), remaining_value[i] - 1) != end(remaining_value);
            }
            if (remaining_value[i] > 2) {
                found_inf2 = find(begin(remaining_value), end(remaining_value), remaining_value[i] - 2) != end(remaining_value);
            }
            if (remaining_value[i] < 9) {
                found_sup1 = find(begin(remaining_value), end(remaining_value), remaining_value[i] + 1) != end(remaining_value);
            }
            if (remaining_value[i] < 8) {
                found_sup2 = find(begin(remaining_value), end(remaining_value), remaining_value[i] + 2) != end(remaining_value);
            }

            // suite possible
            if ((found_inf2 && found_inf1) || (found_inf1 && found_sup1) || (found_sup1 && found_sup2)) {
                strength_temp = 2;
            }

            count_color = 0;
            count_value = 0;
            for (size_t j = 0; j < remaining_color.size(); j++) {
                if ((i != j) && (remaining_color[j] == remaining_color[i])) {
                    count_color++;
                }
                if ((i != j) && (remaining_value[j] == remaining_value[i])) {
                    count_value++;
                }
            }
            found_same_color = (9 - count_color) >= 3;
            found_same_value = (6 - count_value) >= 3;

            // couleur possible
            if (found_same_color) {
                if (strength_temp == 2) {
                    strength_temp = 5; // suite et couleur possible
                }
                else {
                    strength_temp = 3; // couleur possible
                }
            }

            // brelan possible
            if (found_same_value) {
                strength_temp = 4;
            }

            if (strength_temp > strength) {
                strength = strength_temp;
            }
        }
        break;

    case 1:
        // cartes quelconques possibles
        strength = 1;

        if (comb[0].value > 1) {
            found_inf1 = find(begin(remaining_value), end(remaining_value), comb[0].value - 1) != end(remaining_value);
        }
        if (comb[0].value > 2) {
            found_inf2 = find(begin(remaining_value), end(remaining_value), comb[0].value - 2) != end(remaining_value);
        }
        if (comb[0].value < 9) {
            found_sup1 = find(begin(remaining_value), end(remaining_value), comb[0].value + 1) != end(remaining_value);
        }
        if (comb[0].value < 8) {
            found_sup2 = find(begin(remaining_value), end(remaining_value), comb[0].value + 2) != end(remaining_value);
        }

        // suite possible
        if ((found_inf2 && found_inf1) || (found_inf1 && found_sup1) || (found_sup1 && found_sup2)) {
            strength = 2;
        }

        for (size_t i = 0; i < remaining_color.size(); i++) {
            if (remaining_color[i] == comb[0].color) {
                count_color++;
            }
            if (remaining_value[i] == comb[0].value) {
                count_value++;
            }
        }
        found_same_color = (9 - count_color) >= 2;
        found_same_value = (6 - count_value) >= 2;

        // couleur possible
        if (found_same_color) {
            if (strength == 2) {
                strength = 5; // suite et couleur possible
            }
            else {
                strength = 3; // couleur possible
            }
        }

        // brelan possible
        if (found_same_value) {
            strength = 4;
        }

        break;

    case 2:
        found_inf1 = find(begin(remaining_value), end(remaining_value), comb[0].value - 1) != end(remaining_value);
        found_inf2 = find(begin(remaining_value), end(remaining_value), comb[0].value - 2) != end(remaining_value);
        found_sup1 = find(begin(remaining_value), end(remaining_value), comb[0].value + 1) != end(remaining_value);
        found_sup2 = find(begin(remaining_value), end(remaining_value), comb[0].value + 2) != end(remaining_value);
        for (size_t i = 0; i < remaining_color.size(); i++) {
            if (remaining_color[i] == comb[0].color) {
                count_color++;
            }
            if (remaining_value[i] == comb[0].value) {
                count_value++;
            }
        }
        found_same_color = (9 - count_color) >= 1;
        found_same_value = (6 - count_value) >= 1;

        // cartes quelconques possibles
        strength = 1;

        // suite possible
        if ((comb[1].value == comb[0].value - 1) && (found_inf2 || found_sup1)) {
            strength = 2;
        }
        if ((comb[1].value == comb[0].value + 1) && (found_inf1 || found_sup2)) {
            strength = 2;
        }

        // couleur possible
        if ((comb[0].color == comb[1].color) && (found_same_color)) {
            if (strength == 2) {
                strength = 5; // suite et couleur possible
            }
            else {
                strength = 3; // couleur possible
            }
        }

        // brelan possible
        if ((comb[0].value == comb[1].value) && (found_same_value)) {
            strength = 4;
        }

        break;

    default:
        break;
    }

    return strength;
}