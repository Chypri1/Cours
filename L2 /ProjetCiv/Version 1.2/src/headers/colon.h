
#ifndef _COLON_H_
#define _COLON_H_

/* structure colon */

typedef struct colon_t{
  int x;
  int y;
  int etat_cons;
}colon_t;

/*
 *fonction pour le colon
 *
 */
int est_libre(int biome[N][N]);
void supp_image_colon(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture *texture);
colon_t * crea_colon(int i,int j);
void mvt_colon(SDL_Rect case_plateau,colon_t * colon,int x,int y);
void affiche_colon(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,colon_t *colon, SDL_Texture* texture);
#endif