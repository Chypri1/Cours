#ifndef _ARM_SPEC_H_
#define _ARM_SPEC_H_
/* structure armée specifique */
typedef struct arm_spec{
  int x;
  int y;
  int pdv;
  int att;
  int def;
}arm_spec_t;



/*
  *
  * fonction pour le arm_spec
  *
*/
void supp_image_arm_spec(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture);
void affiche_arm_spec(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,arm_spec_t* arm_spec);
arm_spec_t * crea_arm_spec(int i,int j);
void mvt_arm_spec(SDL_Rect case_plateau,arm_spec_t * arm_spec,int x,int y);

#endif