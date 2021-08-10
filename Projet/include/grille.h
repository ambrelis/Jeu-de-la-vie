#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
 * 
 * @param nbl nmbre de lignes
 * @param nbc nmbre de colonnes
 * @param cellules pointeur de pointeur vers les cellules
 */
typedef struct {
	int nbl; 
	int nbc; 
	int** cellules;
} grille;
 
/**
 * @brief alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * 
 * @param l int ligne
 * @param c int colonne 
 * @param g pointeur vers grille
 */
void alloue_grille (int l, int c, grille* g);

/**
 * @brief libère une grille
 * 
 * @param g pointeur vers grille g
 */
void libere_grille (grille* g);

/**
 * @brief alloue et initalise la grille g à partir d'un fichier
 * 
 * @param filename pointeur vers filename
 * @param g pointeur vers grille g
 */
void init_grille_from_file (char * filename, grille* g);

/**
 * @brief rend vivante la cellule (i,j) de la grille g
 * 
 * @param i int 
 * @param j int
 * @param g grille
 */
static inline void set_vivante(int i, int j, grille g)
{
    g.cellules[i][j] = 1;
}

/**
 * @brief rend morte la cellule (i,j) de la grille g
 * 
 * @param i 
 * @param j 
 * @param g 
 */
static inline void set_morte(int i, int j, grille g)
{
    g.cellules[i][j] = 0;
}

/**
 * @brief test si la cellule (i,j) de la grille g est vivante
 * 
 * @param i int
 * @param j int
 * @param g grille 
 * @return int 
 */
static inline int est_vivante(int i, int j, grille g)
{
    return g.cellules[i][j] > 0;
}

/**
 * @brief ne vieillit pas
 * 
 * @param i int
 * @param j int
 * @param g grille
 */
void immortel(int i,int j, grille g);

/**
 * @brief vieillit de 1 et meurt si son age dépasse 8
 * 
 * @param i int
 * @param j int
 * @param g grille
 */
void mortel(int i,int j, grille g);

/**
 * @brief recopie gs dans gd (sans allocation)
 * 
 * @param gs grille
 * @param gd grille
 */
void copie_grille (grille gs, grille gd);

/**
 * @brief cellules ou la vie ne peut pas se développer
 * 
 * @param i int
 * @param j int
 * @param g grille
 */
static inline void non_viable(int i, int j, grille g)
{
    g.cellules[i][j] = -1;
}

static inline int viable(int i, int j, grille g)
{
    return g.cellules[i][j] >= 0;
}
int egalite_grilles(grille g1,grille g2);
#endif
