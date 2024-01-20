#ifndef _ADMIN_SDL_H_
#define _ADMIN_SDL_H_
void SDL_ExitWithError(const char* message);
void SDL_initialisation();
void clean_ressources(SDL_Window *w,SDL_Renderer *r,SDL_Texture *t);
void SDL_AfficherUneImage(SDL_Renderer *renderer,char *image,SDL_Texture *texture,SDL_Rect rectangle);


#endif