#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/admin_SDL.h"
#include "headers/menu.h"
#include "headers/plateau.h"
#include "headers/jeu.h"
#include "headers/ville.h"

/*
*
*fonction ville
*
*/

void affiche_ville(SDL_Rect cases[LONGUEUR_CASE][LARGEUR_CASE],ville_t *ville,SDL_Renderer *renderer,SDL_Texture* texture){
  char *image_ville=NULL;


  int i=(ville->x);
  int j=(ville->y)-1;


  SDL_Rect rectangle = cases[4][3]; 
  image_ville="./image/ville1.png";
  SDL_AfficherUneImage(renderer,image_ville,texture,rectangle);
  SDL_RenderPresent(renderer);
  printf("ville_affiché ! \n");
}


ville_t * crea_ville(int i,int j){
    ville_t * ville=malloc(sizeof(ville_t));

     ville->x=i;
     ville->y=j;
     ville->culture=1;
     ville->sciences=5;
     ville->niveau_ville=5;
     ville->nom_ville="FRONTIER";
  printf("position ville :");
    printf(" x=%d y=%d\n",ville->x,ville->y);
    return(ville);
}





void dest_ville(SDL_Rect case_plateau,ville_t * ville,int x,int y){ //x et y viennent des fonctions clics

  SDL_Renderer *renderer;
  SDL_Texture * texture;

    clean_ressources(NULL,NULL,texture);

}
