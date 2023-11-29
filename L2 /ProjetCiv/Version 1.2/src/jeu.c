
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "headers/admin_SDL.h"
#include "headers/plateau.h"
#include "headers/menu.h"
#include "headers/structure_jeu.h"
#include "headers/jeu.h"
#include "headers/bandeau_action.h"
#include "headers/mouvement_personnage.h"



int  jeu(int civilization,SDL_Window* window, SDL_Renderer* renderer,int liste_cases[N][N]){

    civilization_t *civ;
  SDL_initialisation();
     SDL_Rect cases[LONGUEUR_CASE][LARGEUR_CASE];
     SDL_Texture * texture=NULL;
     int height = 1000;
     int width = 700;

     int nb_ville=0,nb_colon=0,nb_batisseur=0,nb_guerrier=0,nb_arm_long=0;


    SDL_Rect passer_tour={LONGUEUR_CASE,0,LONGUEUR_CASE,LARGEUR_CASE};
    SDL_Surface *image=IMG_Load("../image/fond.jpg");
    SDL_AfficherUneImage(renderer,image,texture,passer_tour);
    SDL_Rect rectangle_quit={0,0,LONGUEUR_CASE,LARGEUR_CASE};
    crea_plat(cases);
    SDL_bool program_launched = SDL_TRUE;
    int x,y,numx,numy;
    SDL_Event event;

    ville_t* ville[N];
    batisseur_t *batisseur[N];
    colon_t *colon[N];
    guerrier_t *guerrier[N];
    arm_long_t *archer[N];

    ville[nb_ville]=crea_ville(4,4);
    affiche_ville(cases,ville,renderer);
    int tour=1;
    int choix = 0 ;
    int reset=0;

     while(program_launched){
        while (SDL_PollEvent(&event))
           {
            switch (event.type)
            {
              case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;

              case SDL_MOUSEBUTTONDOWN:
                /*faire toutes les actions*/
                x = event.button.x;  /*récupération de la position de la souris*/
                y = event.button.y;
                printf("coord : x=%d, y=%d \n", x, y);
                numx = click_case_x(x);
                numy = click_case_y(y);
                printf("case : i=%d, j=%d \n", numx, numy);

                for(int i =0;i< N;i++){ /* changer le N en une fonction qui retourne le max des valeurs */

                  /*fonction_bandeau_superieur*/
                  if(numx==ville[i]->x && numy==ville[i]->y && ville[i]!= NULL){
                      reset = 0 ;
                      int choix=fonction_bandeau_ville(cases,renderer,ville);
                      if(choix == 1){
                        colon[nb_colon] = crea_colon(ville[0]->x+1,ville[0]->y);
                        affiche_colon(cases,renderer,colon);
                        nb_colon++;
                        reset = 1;
                      }
                      else if(choix == 2)
                      {
                        batisseur[nb_batisseur]=crea_batisseur(4,6); /*  revoir les coordonnées d'apparition*/
                        affiche_batisseur(cases,renderer,batisseur[nb_batisseur]);
                        nb_batisseur++;
                        reset = 1;
                      }
                      else if (choix == 3)
                      {
                        guerrier[nb_guerrier]=crea_guerrier(1,5); /* revoir les coordonnées d'apparition*/
                        liste_cases[1][5]=40;
                        affiche_guerrier(cases,renderer,guerrier[nb_guerrier]);
                        nb_guerrier++;
                        reset = 1;
                      }
                    }

                  /* possibilité pour le colon */
                  if(colon[i] != NULL){
                      if(numx==colon[i]->x && numy==colon[i]->y){
                      reset = 0 ;
                      choix=fonction_bandeau_colon(cases,renderer,colon[i],liste_cases);
                        if(choix == 1){
                          ville[nb_ville] = crea_ville(colon[i]->x,colon[i]->y);
                          affiche_ville(cases,ville[nb_ville],renderer);
                          colon[nb_colon]=NULL;
                          nb_ville++;
                          nb_colon--;
                          reset = 1;
                        }
                        liste_cases[colon[i]->x][colon[i]->y]=50;/* ajout de la ville sur la sauvegarde*/
                      }
                  }

                  /*pour un batisseur*/
                  if(batisseur[i] != NULL){
                    if(numx==batisseur[i]->x && numy==batisseur[i]->y){
                      choix = 0 ;
                      int choix=fonction_bandeau_batisseur(cases,renderer,batisseur[i],liste_cases);

                      if(choix==1){
                      //  fonction_afficher_ferme(/*peut etre changer le plateau pour un réaffichage après*/);
                        batisseur[i]->nb_coup=batisseur[i]->nb_coup-1;
                        civ->nb_ferme=(civ->nb_ferme)+1;
                        liste_cases[batisseur[i]->x][batisseur[i]->y]=65;
                        if(batisseur[i]->nb_coup == 0)
                          batisseur[i]=NULL;
                        nb_batisseur--;
                      }
                      else if(choix == 2)
                      {
                        batisseur[i]->nb_coup=batisseur[i]->nb_coup-1;
                          civ->nb_biblio=(civ->nb_biblio)+1;
                          liste_cases[batisseur[i]->x][batisseur[i]->y]=70;
                        if(batisseur[i]->nb_coup == 0)
                          batisseur[i]=NULL;
                        nb_batisseur--;
                      }
                    }
                      /* pour un guerrier  */
                  }

                  if(guerrier[i] != NULL){
                    if(numx==guerrier[i]->x && numy==guerrier[i]->y){
                      reset = 0 ;
                      choix=fonction_bandeau_guerrier(cases,renderer,guerrier[i],liste_cases);
                        if(choix == 1){       /* revoir les actions du guerrier*/
                        }
                    }
                  }



                  if((x > passer_tour.x && x<( passer_tour.x + passer_tour.w) && y> passer_tour.y && y < ( passer_tour.y +  passer_tour.h))){
                      printf("tour n° :%d\n\n",tour);
                          //civ=fin_tour_civ(civ);
                          affectation_cases(liste_cases,cases);
                          printf("affectation faite",civ->nb_ferme);
                          tour++;

                      break; /*clic pour passer au tour suivant pas le choix*/
                  }
                  if (x > rectangle_quit.x && x<(rectangle_quit.x + rectangle_quit.w) && y>rectangle_quit.y && y < (rectangle_quit.y + rectangle_quit.h))
                  {
                    printf("\n programme quitté\n");
                    program_launched = SDL_FALSE;
                    break;
                  }

                  default:break;

                }

              }

          }

      }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;

    }
