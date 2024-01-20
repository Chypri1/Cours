#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

#include "headers/admin_SDL.h"


/**
 *\file admin_SDL.c
 * \brief Création du module SDL
 * \author Pierre Maël Geoffrey
 * \version 1.0
 * \date 19/04/2021
*/


/* Création de la SDL
Initialisation de la SDL.*/


/*Lancement SDL*/
void SDL_initialisation() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");
}

/*Message d'erreur:
Conceptualisation d'une circonstance d'erreur.*/

void SDL_ExitWithError(const char* message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


/**
* \fn void clean_ressources(SDL_Window *w,SDL_Renderer *r,SDL_Texture *t)
* \param w Récupère la fenêtre déjà initialisé
* \param r Récupère la rendu déjà initialisé
* \param t Récupère la texture déjà initialisé
* \brief Destruction des textures et rendus ainsi que de la fenêtre
*/


void clean_ressources(SDL_Window *w,SDL_Renderer *r,SDL_Texture *t)
{
    if(t != NULL)
        SDL_DestroyTexture(t);
    if(r != NULL)
        SDL_DestroyRenderer(r);
    if(w != NULL)
        SDL_DestroyWindow(w);
}

/**
* \fn SDL_AfficherUneImage(SDL_Renderer *renderer,SDL_Surface *image,SDL_Texture *texture,SDL_Rect rectangle)
* \param renderer Rendu d'affichage déjà initialisé
* \param image Récupère l'image déjà initialisé
* \param texture Récupère la texture déjà initialisé
* \param rectangle objet de type SDL_Rect déjà initialisé
* \brief Permet l'affichage d'une image et opère les cas d'erreurs éventuels
*/


void SDL_AfficherUneImage(SDL_Renderer *renderer,char *image1,SDL_Texture *texture,SDL_Rect rectangle){
    SDL_Surface *image = IMG_Load(image1);
    if(image ==NULL){
        clean_ressources(NULL,renderer,texture);
        SDL_ExitWithError("Impossible de charger l'image");
    }
    SDL_Surface *convertedSurface = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA8888, 0);
    texture= SDL_CreateTextureFromSurface(renderer,convertedSurface);
     if(texture ==NULL){
        clean_ressources(NULL,renderer,texture);
        SDL_ExitWithError("Impossible de creer la texture");
    }
    if(SDL_RenderCopy(renderer,texture,NULL,&rectangle)!=0){
        clean_ressources(NULL,renderer,texture);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }
    clean_ressources(NULL,NULL,texture);
    SDL_FreeSurface(image);
}

