/**
 * @file grille.c
 * @author Lis Ambre
 * @brief fonctions "allocation/libération/initialisation"
 * @version 2.0
 * @date 06-03-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/grille.h"

/**
 * @brief alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * 
 * @param l nmbre de lignes
 * @param c nmbre de colonnes
 * @param g pointeur vers la grille
 */
void alloue_grille (int l, int c, grille* g)
{
	g->nbl=l;
	g->nbc=c;
	g -> cellules=(int**)malloc(l*sizeof(int*));

	for (int i=0;i<l;i++)
	{
		g -> cellules[i]= (int*)malloc(c*sizeof(int));
	}
	
	for (int i=0;i<l;i++)
		for (int j=0;j<c;j++)
			set_morte(i,j,*g);

}
/**
 * @brief libere_grille
 * 
 * @param g pointeur vers la grille
 */
void libere_grille(grille* g){
    
    for(int i=0;i<g->nbl;++i)
	{
 		free(g->cellules[i]);
	}
	free(g->cellules);
}
/**
 * @brief alloue et initalise la grille g à partir d'un fichier
 * 
 * @param filename pointeur vers le fichier
 * @param g pointeur vers la grille
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);

	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);

	alloue_grille(l,c,g);

	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	int no_viable = 0;
    fscanf(pfile, "%d", &no_viable);
    for(n=0; n < no_viable; n++){
        fscanf(pfile, "%d", &i);
        fscanf(pfile, "%d", &j);
        non_viable(i, j, *g);
    }

	fclose (pfile);
	return;
}
/**
 * @brief continue à vivre sans vieillir
 * 
 * @param i indice ligne cellule
 * @param j indice colonne cellule
 * @param g grille
 */
void immortel(int i,int j, grille g){}
/**
 * @brief vieillit de 1 et si son age dépasse 8,il meurt 
 * 
 * @param i indice ligne cellule
 * @param j indice colonne cellule
 * @param g grille
 */
void mortel(int i,int j, grille g){
	g.cellules[i][j] = (g.cellules[i][j]+1) % 9;
}


/**
 * @brief recopie gs dans gd (sans allocation)
 * 
 * @param gs grille
 * @param gd grille
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;
}

int egalite_grilles( grille g1, grille g2)
{
	if(g1.nbl!=g2.nbl ||g1.nbc!= g2.nbc) return 0;
	
	int i,j;
	for(i=0;i<g1.nbl;i++)
		for(j=0;j<g1.nbc;j++)
			if(g1.cellules[i][j]!=g2.cellules[i][j])
				return 0;
	return 1;
}
