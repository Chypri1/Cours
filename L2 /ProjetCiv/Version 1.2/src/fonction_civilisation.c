#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/admin_SDL.h"
#include "headers/plateau.h"
#include "headers/menu.h"
#include "headers/civilisation.h"

/*
 *fonction pour la civilization globale
 *
 */


 civilization_t * crea_civ(int civi){
     civilization_t * civ=malloc(sizeof(civilization_t));
     civ->civilization=civi;
     civ->sciences_globale=2;
     civ->nb_ferme=0;
     civ->nb_biblio=0;
     if(civi==1){
      civ->bonus_sciences=3;
      civ->bonus_culture=1;
    }
    else if(civi==2){
    civ->bonus_sciences=2;
    civ->bonus_culture=2;
  }
    else if(civi==3){
      civ->bonus_sciences=1;
      civ->bonus_culture=3;

    }

     return(civ);
 }

civilization_t *fin_tour_civ(civilization_t *civ){

civ->sciences_globale=(civ->sciences_globale)+(2*(civ->nb_biblio)*(civ->bonus_sciences));
civ->culture_globale=(civ->culture_globale)+(3*(civ->nb_ferme)*(civ->bonus_culture));
return(civ);
}




