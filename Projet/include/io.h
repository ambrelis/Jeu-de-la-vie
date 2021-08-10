#ifndef __IO_H
#define __IO_H
#define XK_LATIN1

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>
#include "grille.h"
#include "jeu.h"

#define SIZEX 400
#define SIZEY 400 + 100



/** 
 * \brief affichage d'une grille (mode graphique)
 * \relatesalso grille
 * \param surface surface cairo à peindre
 * \param g grille à afficher
 * \param periode periode d'oscillation de la grille
 */
void affiche_cairo_grille(cairo_surface_t *surface, grille g);

/** 
 * \brief débute une partie (mode graphique)
 * \param g grille du jeu
 * \param gc grille tampon (nécessaire pourla fonction \c evolue)
 * \param dpy display X11 (fenetre du jeu)
 * \param cs surface cairo à peindre
 */
void debut_jeu_cairo(grille* g, grille* gc, Display* dpy, cairo_surface_t *cs);

#endif
