#ifndef _BIB_TAB_SERVEUR_H_
#define _BIB_TAB_SERVEUR_H_

#include <bib_tab.h>

extern cr_t min( char * p_donnees, char * p_resultats )  ;
extern cr_t max( char * p_donnees, char * p_resultats ) ;

#define BIB_TAB_NB_FONCTIONS 2
cr_t (*bib_tab_tab_fonctions[BIB_TAB_NB_FONCTIONS])(char * , char * ) = { min , max } ;

#endif


