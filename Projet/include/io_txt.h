#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "../include/grille.h"
#include "../include/jeu.h"

/**
 * @brief affichage d'un trait horizontal
 * 
 * @param c int
 */
void affiche_trait (int c);

/**
 * @brief affichage d'une ligne de la grille
 * 
 * @param c int colonne
 * @param ligne pointeur vers ligne
 */
void affiche_ligne (int c, int* ligne);

/**
 * @brief affichage d'une grille
 * 
 * @param g grille
 */
void affiche_grille (grille g);

/**
 * @brief effacement d'une grille
 * 
 * @param g grille
 */
void efface_grille (grille g);

/**
 * @brief debute le jeu
 * 
 * @param g pointeur vers grille
 * @param gc pointeur vers grille
 */
void debut_jeu(grille *g, grille *gc);

#endif
