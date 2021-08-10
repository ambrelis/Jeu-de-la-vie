/**
 * @file main.c
 * @author Lis Ambre
 * @brief fonction principale
 * @version 2.0
 * @date 06-03-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>

#include "../include/grille.h"
#include "../include/io_txt.h"
#include "../include/jeu.h"

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
