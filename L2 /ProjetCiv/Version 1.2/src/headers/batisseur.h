#ifndef _BATISSEUR_H_
#define _BATISSEUR_H_

/* srtucture batisseur */
typedef struct batisseur_t{
  int x;
  int y;
  int nb_coup;
}batisseur_t;

/*
  *
  * fonction pour le batisseur
  *
*/

void supp_image_batisseur(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture);
void affiche_batisseur(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,batisseur_t * batisseur);
batisseur_t * crea_batisseur(int i,int j);
void mvt_batisseur(SDL_Rect case_plateau,batisseur_t* batisseur,int x,int y);


#endif