#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>


#include "headers/admin_SDL.h"
#include "headers/menu.h"
#include "headers/plateau.h"
#include "headers/jeu.h"


/**
 *\file main.c
 * \brief Programme principal
 * \author Pierre Maël Cyprien
 * \version 1.0
 * \date 01/02/2022
*/

/**
* \fn int main(int argc, char* argv[])
* \param argc Récupère le nombre d'arguments
* \param argv Met les arguments dans un tableau accessible
* \brief Initialisation des variables telles que la hauteur et la largeur, nécessaires à la taille de la fenêtre. Ensuite initialisation de chaque rectangle que ce soit pour les boutons, le personnage et le rendu. \n
        Création d'une fenêtre et d'un rendu. \n
        Appel des fonctions des autres fichiers. \n
        Condition pour garder la fenêtre ouverte, attente des événements résultants du joueur.
*/


int main(int argc, char* argv[])
{

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    int liste_cases[N][N];
    SDL_Rect cases[LONGUEUR_CASE][LARGEUR_CASE];

    int height = 1000;
    int width = 700;
    
    SDL_Rect fenetre_surface;
    fenetre_surface.x = 0;
    fenetre_surface.y = 0;
    fenetre_surface.w = height;
    fenetre_surface.h = width;

    SDL_Rect rectangle_restart;
    rectangle_restart.x = (height / 2 / 4);
    rectangle_restart.y = (width / 3 * 2);
    rectangle_restart.w = 100;
    rectangle_restart.h = 50;

    SDL_Rect rectangle_continuer;
    rectangle_continuer.x = (height / 2 - LARGEUR_CASE);
    rectangle_continuer.y = (width / 3 * 2);
    rectangle_continuer.w = 100;
    rectangle_continuer.h = 50;

    SDL_Rect rectangle_quit;
    rectangle_quit.x = (height / 2 * 1.5);
    rectangle_quit.y = (width / 3 * 2);
    rectangle_quit.w = 100;
    rectangle_quit.h = 50;

    SDL_Rect rect_trajan;
    rect_trajan.x = 137.5;
    rect_trajan.y = 50;
    rect_trajan.w = 150;
    rect_trajan.h = 150;

    SDL_Rect rect_pierre;
    rect_pierre.x = 425;
    rect_pierre.y = 50;
    rect_pierre.w = 150;
    rect_pierre.h = 150;

    SDL_Rect rect_Barberousse;
    rect_Barberousse.x = 712.5;
    rect_Barberousse.y = 50;
    rect_Barberousse.w = 150;
    rect_Barberousse.h = 150;




    int x = 0, y = 0;

    int civilization=0;

    /*Lancement SDL*/
    SDL_initialisation();
    window = SDL_CreateWindow("Civianus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, 0);

    if (window == NULL)
        SDL_ExitWithError("Impossible de creer la fen�tre");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de creer le rendu");
    }
    SDL_Surface* fond = IMG_Load("/allemagne.png");
    if(fond==NULL){
        printf("l'image n'est pas chargée \n");
    }
    SDL_Texture* fond_Texture = SDL_CreateTextureFromSurface(renderer, fond);
    SDL_FreeSurface(fond);
    //menu(window, renderer, rectangle_restart, rectangle_continuer, rectangle_quit, fenetre_surface);
    SDL_RenderPresent(renderer);

    SDL_bool program_launched = SDL_TRUE;



    printf(" c'est alleé jusqué là");


    while (program_launched) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            
            switch (event.type)
            {
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;

            case SDL_MOUSEBUTTONDOWN: /* Relâchement d'un clique*/
                program_launched =SDL_FALSE;
                break;

            default:
                break;
            }
        }
    }



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;

}
