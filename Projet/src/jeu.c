/**
 * @file jeu.c
 * @author Lis Ambre
 * @brief fonctions compte voisins vivants cycliques/non-cycliques puis evolution
 * @version 3.0
 * @date 06-03-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/jeu.h"

int (*compte_voisins_vivants) (int, int, grille)=compte_voisins_vivants_non_cyclique;
void (*vie)(int,int,grille) = immortel;
/**
 * @brief compte le nombre de voisins vivants de la cellule (i,j) (les bords sont cycliques.)
 * 
 * @param i indice ligne
 * @param j indice colonne
 * @param g grille
 * @return int v nmbre de voisins vivants
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}
/**
 * @brief compte le nombre de voisins vivants de la cellule (i,j) (les bords sont non cycliques.)
 * 
 * @param i indice de la ligne 
 * @param j indice colonne 
 * @param g grille
 * @return int v nombre de voisins 
 */
int compte_voisins_vivants_non_cyclique(int i,int j, grille g)
{
	int l = g.nbl;
	int c = g.nbc;
	int v = 0;

    if (i > 0) 
	v += est_vivante(i, j-1, g);
    if (j > 0) 
	v += est_vivante(i, j-1, g);
    if (i > 0 && j > 0) 
	v+= est_vivante(i-1, j-1, g);
    if (c - 1 > j && i > 0) 
	v+= est_vivante(i-1, j+1, g);
    if (l -1 > i && c-1 > j) 
	v+= est_vivante(i+1, j+1, g);
    if (c-1 > j)
	 v+= est_vivante(i, j+1, g);
    if (l- 1 > i && j > 0)
	 v+= est_vivante(i+1, j-1, g);
    if (l-1 > i) 
	v+= est_vivante(i+1, j, g);

    return v;
}

/**
 * @brief fait évoluer la grille g d'un pas de temps
 * 
 * @param g pointeur vers la grille
 * @param gc pointeur vers la grille
 */
void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (viable(i, j, *g)){
			v = compte_voisins_vivants(i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3  ) set_morte(i,j,*g);
				else vie(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
			}
		}
	}
	return;
}
/**
 * @brief recherche si la colonie est oscillante ou non 
 * 
 * @param g pointeur vers la grille g
 * @param p_max periode maximum
 * @return int 
 */

int recherche_oscillation(grille*g, int p_max)
{
	grille g1,gc1;
	alloue_grille(g->nbl,g->nbc,&g1);
	alloue_grille(g->nbl,g->nbc,&gc1);
	copie_grille(*g,g1);
	
	int i=0; int oscillant=0;
	while(i<p_max && oscillant==0){
	evolue(&g1,&gc1);
	i++;
	oscillant=egalite_grilles(*g,g1);
	}
	libere_grille(&g1);
	libere_grille(&gc1);
	
	if(oscillant){
		return i;
	}	
	else {
		return -1;
	}	
}
