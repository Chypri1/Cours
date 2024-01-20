#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/admin_SDL.h"
#include "headers/plateau.h"
#include "headers/menu.h"
#include "headers/guerrier.h"

#include "headers/civilisation.h"
/*
*
*fonction guerrier
*
*/

void supp_image_guerrier(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture){
      SDL_FreeSurface;
      SDL_Surface *herbe;
      herbe=IMG_Load("./image/herbe.png");
      SDL_AfficherUneImage(renderer,herbe,texture,case_plateau);
}


void affiche_guerrier(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,guerrier_t* guerrier){
      SDL_Texture * texture;
      SDL_Surface *image_guerrier;
      int i=guerrier->x;
      int j=(guerrier->y)-1;
      image_guerrier=IMG_Load("./image/guerrier.png");
      SDL_AfficherUneImage(renderer,image_guerrier,texture,plateau[i][j]);

}

guerrier_t * crea_guerrier(int i,int j){
    guerrier_t * guerrier=malloc(sizeof(guerrier_t));

    guerrier->x=i;
    guerrier->y=j;
    guerrier->pdv=3;
    guerrier->att=1;
    guerrier->def=3;
    //affiche_guerrier(plateau);
    printf("position guerrier :");
    printf(" x=%d y=%d\n",guerrier->x,guerrier->y);
    return(guerrier);
}


void mvt_guerrier(SDL_Rect case_plateau,guerrier_t * guerrier,int x,int y){ //x et y viennent des fonctions clics

  SDL_Renderer *renderer;
  SDL_Texture * texture;

  do{
  /* clic ou appel de la fonction mvt_guerrier*/

  }while((((guerrier->x)-x)>1)|| (((guerrier->y)-y)>1) );
      /* refaire */
      guerrier->x=x;
      guerrier->y=y;
      supp_image_guerrier(case_plateau,renderer,texture);
    //  affiche_guerrier(plateau);
}
