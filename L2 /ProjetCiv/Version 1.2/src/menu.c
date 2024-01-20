#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "./headers/admin_SDL.h"
#include "./headers/menu.h"
#include "./headers/plateau.h"


/**
 *\file menu.c
 * \brief Création du menu de jeu
 * \author Pierre Maël
 * \version 1.0
 * \date 01/02/2022
*/

/**
* \fn void menu(SDL_Window* window, SDL_Renderer* renderer, SDL_Rect rectangle_restart, SDL_Rect rectangle_continuer, SDL_Rect rectangle_quit, SDL_Rect fenetre_surface)
* \param window Pointeur sur un objet de type SDL_Window
* \param renderer Pointeur sur un objet de type SDL_Renderer
* \param rectangle_restart Rectangle objet de type SDL_Rect déjà initialisé
* \param rectangle_continuer Rectangle objet de type SDL_Rect déjà initialisé
* \param rectangle_quit Rectangle objet de type SDL_Rect déjà initialisé
* \param fenetre_surface Récupération d'une surface déjà initialisée
* \brief Elaboration de trois rectangles dans lesquels ont été insérés les images des boutons "restart", "continuer" et "quit"
*/


void menu(SDL_Window* window, SDL_Renderer* renderer) {

    char* bouton_restart = NULL;
    SDL_Texture* texture = NULL;

    char* bouton_continuer = NULL;

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
    rectangle_continuer.x = (Fenetre_height / 2 / 2);
    rectangle_continuer.y = (Fenetre_width / 3 * 2);
    rectangle_continuer.w = 100;
    rectangle_continuer.h = 50;

    SDL_Rect rectangle_quit;
    rectangle_quit.x = (Fenetre_height / 2 * 1.5);
    rectangle_quit.y = (Fenetre_width / 3 * 2);
    rectangle_quit.w = 100;
    rectangle_quit.h = 50;

    char* bouton_quit = NULL;

    char* fond = "./image/fond.jpg";
    SDL_AfficherUneImage(renderer,fond,texture,fenetre_surface);
   
    bouton_restart ="./image/restart.png"; /*chargement de l'image du bouton restart*/
    SDL_AfficherUneImage(renderer,bouton_restart,texture, rectangle_restart);

    bouton_continuer = "./image/continuer.png"; /*chargement de l'image du bouton continuer*/
    SDL_AfficherUneImage(renderer,bouton_continuer,texture, rectangle_continuer);

    bouton_quit = "./image/quit.png";       /*chargement de l'image du bouton quitter*/
    SDL_AfficherUneImage(renderer,bouton_quit,texture, rectangle_quit);

    SDL_RenderPresent(renderer);
    clean_ressources(NULL,NULL,texture);
}



/**
* \fn void menu_select(SDL_Window* window, SDL_Renderer* renderer, SDL_Rect rect_trajan,SDL_Rect rect_pierre, SDL_Rect rect_Barberousse)
* \param window Pointeur sur un objet de type SDL_Window
* \param renderer Pointeur sur un objet de type SDL_Renderer
* \param rect_trajan Rectangle objet de type SDL_Rect déjà initialisé pour le choix de la civilization de trajan
* \param rect_pierre Rectangle objet de type SDL_Rect déjà initialisé pour le choix de la civilization de pierre Ier
* \param rect_Barberousse Rectangle objet de type SDL_Rect déjà initialisé pour le choix de la civilization de barberousse
* \brief Le joueur choisis une civilization parmis les trois proposés
*/



int menu_select(SDL_Window* window, SDL_Renderer* renderer)
{ /* faire la liste des civilisations disponibles + leur descrition et retourner la coordonnée du click souris pour sélectionner la civ*/
SDL_Event event;

int x = 0, y = 0;
SDL_Rect rectangle_continuer_trajan;
rectangle_continuer_trajan.x = 137.5;
rectangle_continuer_trajan.y = 50;
rectangle_continuer_trajan.w = 150;
rectangle_continuer_trajan.h = 150;

SDL_Rect rectangle_continuer_pierre;
rectangle_continuer_pierre.x = 425;
rectangle_continuer_pierre.y = 50;
rectangle_continuer_pierre.w = 150;
rectangle_continuer_pierre.h = 150;

SDL_Rect rectangle_continuer_barberousse;
rectangle_continuer_barberousse.x = 712.5;
rectangle_continuer_barberousse.y = 50;
rectangle_continuer_barberousse.w = 150;
rectangle_continuer_barberousse.h = 150;

SDL_Rect fenetre;
fenetre.x = 0;
fenetre.y = 0;
fenetre.w = Fenetre_height;
fenetre.h = Fenetre_width;

SDL_Texture* texture = NULL;
char *fond_fenetre = "./image/fond.jpg";
SDL_AfficherUneImage(renderer,fond_fenetre,texture, fenetre);


char *trajan_image = "./image/trajan.png";
SDL_AfficherUneImage(renderer,trajan_image,texture, rectangle_continuer_trajan);



char *pierre_image = "./image/pierre.png";
SDL_AfficherUneImage(renderer,pierre_image,texture, rectangle_continuer_pierre);


char *barberousse_image = "./image/allemagne.png";
SDL_AfficherUneImage(renderer,barberousse_image,texture, rectangle_continuer_barberousse);


SDL_bool program_launched = SDL_TRUE;
int civilisation=0, trouve=0;
while ((SDL_PollEvent(&event))||(trouve!=1)){
        switch (event.type){
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;

            case SDL_MOUSEBUTTONDOWN:   /* Relâchement d'un clique*/
                x = event.button.x;  /*récupération de la position de la souris*/
                y = event.button.y;
                if (x > rectangle_continuer_trajan.x && x<(rectangle_continuer_trajan.x + rectangle_continuer_trajan.w) && y>rectangle_continuer_trajan.y && y < (rectangle_continuer_trajan.y + rectangle_continuer_trajan.h)){
                    trouve=1;
                    return (civilisation=1);
                }
                else if (x > rectangle_continuer_pierre.x && x<(rectangle_continuer_pierre.x + rectangle_continuer_pierre.w) && y>rectangle_continuer_pierre.y && y < (rectangle_continuer_pierre.y + rectangle_continuer_pierre.h)){
                    trouve=1;
                    return (civilisation=2);
                }
                else if (x > rectangle_continuer_barberousse.x && x<(rectangle_continuer_barberousse.x + rectangle_continuer_barberousse.w) && y>rectangle_continuer_barberousse.y && y < (rectangle_continuer_barberousse.y + rectangle_continuer_barberousse.h)){
                    trouve=1;
                    return (civilisation=3);

                }
                break;

            default:
                break;
        }
    }
    SDL_RenderPresent(renderer);
    clean_ressources(NULL,NULL,texture);
    return 0;
}
