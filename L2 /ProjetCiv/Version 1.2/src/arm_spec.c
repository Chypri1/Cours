#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/admin_SDL.h"
#include "headers/plateau.h"
#include "headers/menu.h"
#include "headers/civilisation.h"


#include "headers/arm_spec.h"


/*
  *
  * fonction pour le arm_spec
  *
*/



void supp_image_arm_spec(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture){
      SDL_FreeSurface;
      SDL_Surface *herbe;
      herbe=IMG_Load("./image/herbe.png");
      SDL_AfficherUneImage(renderer,herbe,texture,case_plateau);
}


void affiche_arm_spec(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,arm_spec_t* arm_spec){
      SDL_Texture * texture;
      SDL_Surface *image_arm_spec;
      int i=arm_spec->x;
      int j=(arm_spec->y)-1;
      image_arm_spec=IMG_Load("./image/nombre_tour.png");
      SDL_AfficherUneImage(renderer,image_arm_spec,texture,plateau[i][j]);

}

arm_spec_t * crea_arm_spec(int i,int j){
    arm_spec_t * arm_spec=malloc(sizeof(arm_spec_t));

    arm_spec->x=i;
    arm_spec->y=j;
    arm_spec->pdv=3;
    arm_spec->att=1;
    arm_spec->def=3;
    //affiche_arm_spec(plateau);
    printf("position arm_spec :");
    printf(" x=%d y=%d\n",arm_spec->x,arm_spec->y);
    return(arm_spec);
}


void mvt_arm_spec(SDL_Rect case_plateau,arm_spec_t * arm_spec,int x,int y){ //x et y viennent des fonctions clics

  SDL_Renderer *renderer;
  SDL_Texture * texture;

  do{
  /* clic ou appel de la fonction mvt_arm_spec*/

  }while((((arm_spec->x)-x)>1)|| (((arm_spec->y)-y)>1) );
      /* refaire */
      arm_spec->x=x;
      arm_spec->y=y;
      supp_image_arm_spec(case_plateau,renderer,texture);
  //    affiche_arm_spec(plateau);
}