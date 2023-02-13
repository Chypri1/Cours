#ifndef _BIB_STRING_SERVEUR_H_
#define _BIB_STRING_SERVEUR_H_

#include <bib_string.h>

extern cr_t concat( char * p_donnees, char * p_resultats )  ;
extern cr_t translate( char * p_donnees, char * p_resultats ) ;

#define BIB_STRING_NB_FONCTIONS 2
cr_t (*bib_string_tab_fonctions[BIB_STRING_NB_FONCTIONS])(char * , char * ) = { concat , translate } ;

#endif


