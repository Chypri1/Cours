#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/admin_SDL.h"
#include "headers/plateau.h"
#include "headers/menu.h"
#include "headers/civilisation.h"

#include "headers/batisseur.h"



/*
*
*fonction batisseur
*
*/


void supp_image_batisseur(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture){
      //SDL_FreeSurface;
      SDL_Surface *herbe;
      herbe=IMG_Load("./image/herbe.png");
      SDL_AfficherUneImage(renderer,herbe,texture,case_plateau);
}


void affiche_batisseur(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE],SDL_Renderer *renderer,batisseur_t* batisseur){
      SDL_Texture * texture;
      SDL_Surface *image_batisseur;
      int i=batisseur->x;
      int j=(batisseur->y)-1;
      image_batisseur=IMG_Load("./image/batisseur.png");
      SDL_AfficherUneImage(renderer,image_batisseur,texture,plateau[i][j]);

}

batisseur_t * crea_batisseur(int i,int j){
    batisseur_t * batisseur;
    batisseur=malloc(sizeof(batisseur_t));
    batisseur->x=i;
    batisseur->y=j;
    batisseur->nb_coup=3;

    printf("position batisseur :");

    return(batisseur);
}


void mvt_batisseur(SDL_Rect case_plateau,batisseur_t * batisseur,int x,int y){ //x et y viennent des fonctions clics

  SDL_Renderer *renderer;
  SDL_Texture * texture;

  do{
  /* clic ou appel de la fonction mvt_batisseur*/

  }while((((batisseur->x)-x)>1)|| (((batisseur->y)-y)>1) );
      /* refaire */
      batisseur->x=x;
      batisseur->y=y;
    //  supp_image_batisseur(plateau,renderer,texture);
    //  affiche_batisseur(plateau);
}