#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/admin_SDL.h"
#include "headers/plateau.h"
#include "headers/menu.h"
#include "headers/civilisation.h"

#include "headers/arm_long.h"


/*
  *
  * fonction pour le arm_long
  *
*/



void supp_image_arm_long(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture){
      SDL_FreeSurface;
      SDL_Surface *herbe;
      herbe=IMG_Load("./image/herbe.png");
      SDL_AfficherUneImage(renderer,herbe,texture,case_plateau);
}


void affiche_arm_long(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,arm_long_t* arm_long){
      SDL_Texture * texture;
      SDL_Surface *image_arm_long;
      int i=arm_long->x;
      int j=(arm_long->y)-1;
      image_arm_long=IMG_Load("./image/archer.png");
      SDL_AfficherUneImage(renderer,image_arm_long,texture,plateau[i][j]);

}

arm_long_t * crea_arm_long(int i,int j){
    arm_long_t * arm_long=malloc(sizeof(arm_long_t));

    arm_long->x=i;
    arm_long->y=j;
    arm_long->pdv=3;
    arm_long->att=1;
    arm_long->def=3;
    //affiche_arm_long(plateau);
    printf("position arm_long :");
    printf(" x=%d y=%d\n",arm_long->x,arm_long->y);
    return(arm_long);
}


void mvt_arm_long(SDL_Rect case_plateau,arm_long_t * arm_long,int x,int y){ //x et y viennent des fonctions clics

  SDL_Renderer *renderer;
  SDL_Texture * texture;

  do{
  /* clic ou appel de la fonction mvt_arm_long*/

  }while((((arm_long->x)-x)>1)|| (((arm_long->y)-y)>1) );
      /* refaire */
      arm_long->x=x;
      arm_long->y=y;
      supp_image_arm_long(case_plateau,renderer,texture);
    //  affiche_arm_long(plateau);
}