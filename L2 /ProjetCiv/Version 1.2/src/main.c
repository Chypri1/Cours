#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

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
    SDL_Renderer* rendu_menu = NULL;
    SDL_Renderer* rendu_jeu = NULL;

    int liste_cases[N][N];
    SDL_Rect cases[LONGUEUR_CASE][LARGEUR_CASE];

    int height = 1000;
    int width = 700;
    
     SDL_Rect fenetre_surface;
    fenetre_surface.x = 0;
    fenetre_surface.y = 0;
    fenetre_surface.w = Fenetre_height;
    fenetre_surface.h = Fenetre_width;

    SDL_Rect rectangle_restart;
    rectangle_restart.x = 0;
    rectangle_restart.y = 0;
    rectangle_restart.w = 100;
    rectangle_restart.h = 50;


    SDL_Rect rectangle_continuer;
    rectangle_continuer.x = (Fenetre_height / 4);
    rectangle_continuer.y = (Fenetre_width / 3 * 2);
    rectangle_continuer.w = 100;
    rectangle_continuer.h = 50;

    SDL_Rect rectangle_quit;
    rectangle_quit.x = (Fenetre_height / 2 * 1.5);
    rectangle_quit.y = (Fenetre_width / 3 * 2);
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


    SDL_Texture *texture =NULL;

    int x = 0, y = 0;

    int civilization=0;

    /*Lancement SDL*/
     SDL_initialisation();
    window = SDL_CreateWindow("Civianus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, 0);

    if (window == NULL)
        SDL_ExitWithError("Impossible de creer la fen�tre");

    rendu_menu = SDL_CreateRenderer(window, -1, 2);

    if (rendu_menu == NULL) {
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de creer le rendu menu");
    }
    


    SDL_bool program_launched = SDL_TRUE;
    SDL_Event event;
    menu(window, rendu_menu);

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
                 x = event.button.x;  /*récupération de la position de la souris*/
                 y = event.button.y;
                if (x > rectangle_continuer.x && x<(rectangle_continuer.x + rectangle_continuer.w) && y>rectangle_continuer.y && y < (rectangle_continuer.y + rectangle_continuer.h)&& program_launched)
                {
                   SDL_RenderClear(rendu_menu);

                   // écran de chargement veuillez patienter 

                    SDL_Rect fond_chargement = {0, 0, Fenetre_height, Fenetre_width};
                    char* image = "./image/fond_chargement.jpg";
                    SDL_AfficherUneImage(rendu_menu,image,texture,fond_chargement);
                    SDL_RenderPresent(rendu_menu);


                    /*on met à null les coordonnées des boutons restart et quitter*/

                    rectangle_restart.x = 0;
                    rectangle_restart.y = 0;
                    rectangle_restart.w = 0;
                    rectangle_restart.h = 0;

                    rectangle_quit.x = 0;
                    rectangle_quit.y = 0;
                    rectangle_quit.w = 100;
                    rectangle_quit.h = 100;

                    rectangle_continuer.x = 0;
                    rectangle_continuer.y = 0;
                    rectangle_continuer.w = 0;
                    rectangle_continuer.h = 0;
                    
                    clean_ressources(NULL,rendu_menu,NULL);
                    rendu_jeu = SDL_CreateRenderer(window, -1, 2);
                    if (rendu_jeu == NULL) {
                        SDL_DestroyWindow(window);
                        SDL_ExitWithError("Impossible de creer le rendu jeu");
                    }

                    crea_plat(cases);
                    afficher_plateau(window,rendu_jeu, texture, cases,liste_cases);
                    SDL_RenderPresent(rendu_jeu); // nécessaure pour afficher le jeu et le plateau 
                
                    program_launched=jeu(civilization,window, rendu_jeu, texture, liste_cases);
                    break; /*attend qu'on ferme la fenetre*/

                }
                else 
                if ((x > rectangle_restart.x && x<(rectangle_restart.x + rectangle_restart.w)) && (y>rectangle_restart.y && y < (rectangle_restart.y + rectangle_restart.h)) && program_launched)
                {
                    SDL_RenderClear(rendu_menu);
                    rectangle_restart.x = 0;
                    rectangle_restart.y = 0;
                    rectangle_restart.w = 0;
                    rectangle_restart.h = 0;

                    rectangle_quit.x = 0;
                    rectangle_quit.y = 0;
                    rectangle_quit.w = 0;
                    rectangle_quit.h = 0;

                    rectangle_continuer.x = 0;
                    rectangle_continuer.y = 0;
                    rectangle_continuer.w = 0;
                    rectangle_continuer.h = 0;

                    civilization=menu_select(window, rendu_menu); /* choix du personnage */
                    SDL_RenderPresent(rendu_menu);

                    rectangle_quit.x = 0;
                    rectangle_quit.y = 0;
                    rectangle_quit.w = 100;
                    rectangle_quit.h = 100;

                    clean_ressources(NULL,rendu_menu,NULL);
                    rendu_jeu = SDL_CreateRenderer(window, -1, 2);
                    if (rendu_jeu == NULL) {
                        SDL_DestroyWindow(window);
                        SDL_ExitWithError("Impossible de creer le rendu jeu");
                    }
                    afficher_plateau(window,rendu_jeu, texture, cases,liste_cases);
                
                    program_launched=jeu(civilization,window, rendu_jeu, texture, liste_cases);
                    break; /*attend qu'on ferme la fenetre*/

                }
                else if (x > rectangle_quit.x && x<(rectangle_quit.x + rectangle_quit.w) && y>rectangle_quit.y && y < (rectangle_quit.y + rectangle_quit.h))
                {
                    program_launched = SDL_FALSE;
                }
                break;

            default:
                break;
            }
        }
    }

    clean_ressources(NULL,rendu_jeu,NULL);
    clean_ressources(window,NULL,NULL);
    SDL_Quit();

    return EXIT_SUCCESS;

}
