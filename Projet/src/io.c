/**
 * @file io.c
 * @author Lis Ambre
 * @brief fonction d'affichage de grille et de debut jeu cairo
 * @version 3.0
 * @date 06-03-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "../include/io.h"
#include "../include/io_txt.h"

int(*compte_voisins_vivants) (int,int,grille);

void (*vie) (int,int,grille);
static int temps_evolution=0;

int *tempsEvolution;
/**
 * @brief affichage d'une grille avec cairo
 * 
 * @param g grille
 */
void affiche_cairo_grille (cairo_surface_t *surface,grille g){
	
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 255, 255, 255);
	cairo_rectangle(cr, 0, 410, SIZEX, SIZEY);
	cairo_fill(cr);
	
	
	// variables
	int i,j;
	int periode=0;
	float abs, ord, lgr=SIZEX/g.nbc, lrg=(SIZEY - 100)/g.nbl, age;
	char tps[6];
	char prd[6];
	sprintf(tps,"%d",temps_evolution);
	sprintf(prd,"%d",periode);
	
	
	// grille
	cairo_set_line_width(cr, 1.0);
	for (i=0; i<g.nbl; ++i){
		for (j=0; j<g.nbc; ++j){
			abs = lgr*j;
			ord = lrg*i;
			cairo_rectangle(cr, abs, ord, lgr - 5, lrg - 5);
			if (viable(i,j,g)){
				if (est_vivante(i,j,g)){
					age = 0.1 * g.cellules[i][j];
					cairo_set_source_rgb(cr, age, 0.8 - age, 0.2);
					//couleur du rectangle
					cairo_fill(cr);
				}
				else{
					
					cairo_set_source_rgb(cr, 0, 255, 50); //couleur du background
					cairo_fill(cr);
				}
			}
			else{
				cairo_set_source_rgb(cr, 0.7, 1, 1); 
				cairo_fill(cr);
			}
		}
	}

//affichages
	// temps
	cairo_set_source_rgb(cr,0.0,0.0,0.0);
	cairo_move_to(cr,5.0,SIZEY-75);
	cairo_show_text(cr, "Temps : ");
	cairo_show_text(cr, tps);
	
	// voisinnage
	cairo_set_source_rgb(cr,0.0,0.0,0.0);
	cairo_move_to(cr,5.0,SIZEY-60);
	if (compte_voisins_vivants == compte_voisins_vivants_cyclique)
		cairo_show_text(cr, "Voisinnage cyclique");
	else cairo_show_text(cr, "Voisinnage non-cyclique");
	
	// vielillissement
	cairo_set_source_rgb(cr,0.0,0.0,0.0);
	cairo_move_to(cr,5.0,SIZEY-45 );
	if (vie == immortel)
		cairo_show_text(cr, "Vieillissement : OFF");
	else cairo_show_text(cr, "Vieillissement : ON");
	
	// oscillation
	cairo_set_source_rgb(cr,0.0,0.0,0.0);
	cairo_move_to(cr,5.0,SIZEY-30 );
	if (periode<0){
		cairo_show_text(cr, "Pas d'oscillation ");
		
	}
	else{
		cairo_show_text(cr, "Oscillation : periode de ");
		cairo_show_text(cr, prd);
	}


	// destroy cairo mask
	cairo_destroy(cr); 
	
}



 int (*compte_voisins_vivants) (int, int, grille);
/**
 * @brief debute le jeu avec cairo
 * 
 * @param g pointeur vers une grille
 * @param gc pointeur vers une grille
 */
void debut_jeu_cairo(grille *g, grille *gc, Display* dpy, cairo_surface_t *cs){

	grille greset;
	alloue_grille(g->nbl, g->nbc, &greset);
	copie_grille(*g,greset);
	XEvent e;
	char* touche;
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1){
			affiche_cairo_grille(cs,*g);
		}
		else if(e.type==ButtonPress){
			if(e.xbutton.button==3) break;
			else if (e.xbutton.button==1){
				evolue(g,gc);
				temps_evolution++;
				affiche_cairo_grille(cs,*g);
			}
		}
		else if (e.type==KeyPress){
			touche = XKeysymToString(XkbKeycodeToKeysym(dpy, e.xkey.keycode, 0, 0));
			switch(touche[0]){
				case 'v' : // vieillissement ON/OFF
				
					if (vie == immortel)
            				{
                				vie=mortel;
           				}				
           				else{
               				vie=immortel;
           				}
					affiche_cairo_grille(cs,*g);
					break;
					
				case 'c' : // voisinnage cyclique/non-cyclique
				
					if (compte_voisins_vivants==compte_voisins_vivants_cyclique){
                			compte_voisins_vivants=compte_voisins_vivants_non_cyclique;
            				}
            				else{
               			compte_voisins_vivants=compte_voisins_vivants_cyclique;
					affiche_cairo_grille(cs,*g);
					}
					break;
				
				case 'n': //demande à l’utilisateur un chemin de fichier pour charger une nouvelle grille dynamiquement
				{
					
					char nom[50];
					printf("Entrez le nom de la nouvelle grille à charger: \n");
					scanf("%s",nom);
					temps_evolution=0;
					libere_grille(g);
					libere_grille(gc);
					init_grille_from_file(nom,g);
					alloue_grille(g->nbl, g->nbc, gc);
					affiche_cairo_grille(cs,*g);
					break;
				}
				case 'o' : //teste si une colonie est oscillante ou non
				{	
					recherche_oscillation(g,50);	
					affiche_cairo_grille(cs,*g);
					break;
				}
				default :
					break;
			}
		}
	}
}


         

