#ifndef __JEU_H
#define __JEU_H

#include "../include/grille.h"

/**
 * @brief modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * 
 * @param i int
 * @param m int
 * @return int 
 */
static inline int modulo(int i, int m) 
{
    return (i+m)%m;
}

/**
 * @brief compte le nombre de voisins vivants de la cellule (i,j) les bords sont cycliques.
 * 
 * @param i int
 * @param j int
 * @param g grille
 * @return int 
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);

/**
 * @brief compte le nombre de voisins vivants de la cellule (i,j) les bords sont non cycliques.
 * 
 * @param i int
 * @param j int
 * @param g grille
 * @return int 
 */
int compte_voisins_vivants_non_cyclique(int i,int j, grille g);

/**
 * @brief fait évoluer la grille g d'un pas de temps
 * 
 * @param g pointeur vers grille g
 * @param gc pointeur vers grille gc
 */
void evolue (grille *g, grille *gc);

int recherche_oscillation(grille *g, int p_max);
#endif
