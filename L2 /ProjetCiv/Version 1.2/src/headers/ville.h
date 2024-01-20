#ifndef _VILLE_H_
#define _VILLE_H_

/* srtucture ville avec avantage */
typedef struct ville{
  int x;
  int y;
  int culture;
  int sciences;
  int niveau_ville;
  char*  nom_ville;
}ville_t;
/*
  *
  * fonction pour la ville
  *
*/
void affiche_ville(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],ville_t *ville,SDL_Renderer *renderer, SDL_Texture* texture);
ville_t * crea_ville(int i,int j);

#endif
