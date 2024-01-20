#ifndef _GUERRIER_H_
#define _GUERRIER_H_

/* structure guerrier classique */
typedef struct guerrier{
  int x;
  int y;
  int pdv;
  int att;
  int def;
}guerrier_t;
/*
  *
  * fonction pour le guerrier
  *
*/

void supp_image_guerrier(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture);
void affiche_guerrier(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,guerrier_t* guerrier);
guerrier_t * crea_guerrier(int i,int j);
void mvt_guerrier(SDL_Rect case_plateau,guerrier_t * guerrier,int x,int y);

#endif