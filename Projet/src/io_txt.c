/**
 * @file io.c
 * @author Lis Ambre
 * @brief fonction affiche trait/ligne, puis efface grille
 * @version 2.0
 * @date 06-03-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/io_txt.h"

static int temps_evolution=0;
static int periode =0;
void (*vie) (int, int, grille);
/**
 * @brief affichage d'un trait horizontal
 * 
 * @param c nmbre colonnes
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}
/**
 * @brief affichage d'une ligne de la grille
 * 
 * @param c nmbre colonnes
 * @param ligne pointeur vers la ligne
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); 
        else if (ligne[i] == -1) printf("| x ");
        
        else printf ("| %d ",ligne[i]);
	printf("|\n");
	return;
}
/**
 * @brief affichage d'une grille
 * 
 * @param g grille
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
    printf("temps evolution=%d",temps_evolution);
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}
/**
 * @brief effacement d'une grille
 * 
 * @param g grille
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}
 int (*compte_voisins_vivants) (int, int, grille);
/**
 * @brief debute le jeu
 * 
 * @param g pointeur vers une grille
 * @param gc pointeur vers une grille
 */
void debut_jeu(grille *g, grille *gc){
    char c = getchar(); 
    while (c != 'q') // touche 'q' pour quitter
    { 
        switch (c) {
            case '\n' : 
            { // touche "entree" pour évoluer
                evolue(g,gc);
                temps_evolution++;
                efface_grille(*g);
                affiche_grille(*g);
                break;
            }
            case 'n':
            {   //touche n pour entrer une nouvelle grille
                char nom[50];
                printf("Entrez un nom pour la grille : \n");
                scanf("%s",nom);
                temps_evolution=0;
                efface_grille(*g);
                //efface l'ancienne grille
                libere_grille(g);
                libere_grille(gc);
                //libere les grilles 
                //initialisation d'une nouvelle grille
                init_grille_from_file(nom,g);
                //allocation de la nouvelle grille
                alloue_grille(g->nbl, g->nbc, gc);
                //affichage
                affiche_grille( *g);    

                break;
                

            }
            case 'c': //touche c pour activer/desactiver mode cyclique/non-cyclique
           {
            getchar(); //elimine \n après appuie sur la touche 'c'
            if (compte_voisins_vivants==compte_voisins_vivants_cyclique){
                compte_voisins_vivants=compte_voisins_vivants_non_cyclique;
                    printf("mode non cyclique \n");
            }
            else{
                compte_voisins_vivants=compte_voisins_vivants_cyclique;

                    printf("mode cyclique \n");

            }
            break;
           }
           
        case 'v': //touche v pour activer/desactiver le vieillissement 
        {
            getchar();
            if (vie == immortel)
            {
                vie=mortel;
                printf("le vieillissement est activee\n");
            }
           else{
               vie=immortel;
               printf("le vieillissement est desactive\n");
           }
            break;
        }
        case 'o':// touche o pour chercher si la colonie est oscillante
        {
            periode=recherche_oscillation(g,100);
            if (periode==0) printf("La colonie n'est pas oscillante \n ");
            else printf("La colonie est oscillante de periode : %d \n",periode);
            while(getchar() != '\n');
            printf("\n\e[%dA",3);
            break;
        } 
           
            default : 
            { // touche non traitée
                printf("\n\e[1A");
                break;
            }
        }
        c = getchar(); 
    }
    return; 
}
