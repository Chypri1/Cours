#ifndef _ARM_LONG_H_
#define _ARM_LONG_H_

/* structure armée longue distance*/
typedef struct arm_long{
  int x;
  int y;
  int pdv;
  int att;
  int def;
}arm_long_t;


/*
  *
  * fonction pour le arm_long
  *
*/
void supp_image_arm_long(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture);
void affiche_arm_long(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,arm_long_t* arm_long);
arm_long_t * crea_arm_long(int i,int j);
void mvt_arm_long(SDL_Rect case_plateau,arm_long_t * arm_long,int x,int y);

#endif