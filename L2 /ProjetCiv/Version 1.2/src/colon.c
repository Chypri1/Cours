#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/admin_SDL.h"
#include "headers/plateau.h"
#include "headers/menu.h"
#include "headers/civilisation.h"

#include "headers/colon.h"


int coorx,coory;
/*
  *
  * fonction pour le colon
  *
  */

int est_libre(int liste_cases[coorx][coory]){
    if(liste_cases[coorx][coory]==1 || liste_cases[coorx][coory]==2)
        return(0);
    else
      return(1);
}


void supp_image_colon(SDL_Rect case_plateau,SDL_Renderer *renderer,SDL_Texture * texture){
      SDL_FreeSurface;
      SDL_Surface *herbe;
      herbe=IMG_Load("./image/herbe.png");
      SDL_AfficherUneImage(renderer,herbe,texture,case_plateau);
}


void affiche_colon(SDL_Rect plateau[LONGUEUR_CASE][LARGEUR_CASE], SDL_Renderer *renderer, colon_t *colon, SDL_Texture *texture) {
    char *image_colon = NULL;
    // int i = (colon)->x;
    // int j = (colon)->y - 1;
     int i = 5;
    int j = 3;

    // Vérifier que les indices sont dans les limites du tableau plateau
    if (i >= 0 && i < LONGUEUR_CASE && j >= 0 && j < LARGEUR_CASE) {
        printf("i:%d, j=%d \n", i, j);
        image_colon = "./image/colon.png";
        SDL_AfficherUneImage(renderer, image_colon, texture, plateau[i][j]);
    } else {
        printf("Indices hors limites\n");
    }
}


colon_t * crea_colon(int i,int j){
    colon_t * colon=malloc(sizeof(colon_t));

    colon->x=i;
    colon->y=j;
    colon->etat_cons=1;
    printf("position colon :");
    printf(" x=%d y=%d\n",colon->x,colon->y);
    return(colon);
}


void mvt_colon(SDL_Rect case_plateau,colon_t * colon,int x,int y){ //x et y viennent des fonctions clics

  SDL_Renderer *renderer;
  SDL_Texture * texture;

  do{
  /* clic ou appel de la fonction mvt_colon*/

  }while((((colon->x)-x)>1)|| (((colon->y)-y)>1) );
      /* refaire */
      colon->x=x;
      colon->y=y;
    /*  supp_image_colon(plateau,renderer,texture);
      affiche_colon(plateau);*/
}
