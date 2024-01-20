#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#define N 35

#define Fenetre_width 700
#define Fenetre_height 1000
#define LONGUEUR_CASE 50
#define LARGEUR_CASE 35

int click_case_x(int i);
int click_case_y(int j);

int crea_plat(SDL_Rect cases[LONGUEUR_CASE][LARGEUR_CASE]);
int affectation_cases(int liste_biome[N][N],SDL_Rect cases[LONGUEUR_CASE][LARGEUR_CASE]);
int fonction_rand_biome (int biome,int i,int j);
SDL_Renderer* afficher_plateau(SDL_Window *window,SDL_Renderer * renderer,SDL_Texture *texture,SDL_Rect cases[LONGUEUR_CASE][LARGEUR_CASE],int biome[N][N]);

#endif
