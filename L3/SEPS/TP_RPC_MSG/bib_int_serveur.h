#ifndef _BIB_INT_SERVEUR_H_
#define _BIB_INT_SERVEUR_H_

#include <bib_int.h>

extern cr_t plus( char * p_donnees, char * p_resultats )  ;
extern cr_t moins( char * p_donnees, char * p_resultats ) ;
extern cr_t prod( char * p_donnees, char * p_resultats )  ;
extern cr_t quot( char * p_donnees, char * p_resultats )  ;
extern cr_t reste( char * p_donnees, char * p_resultats ) ;
extern cr_t min( char * p_donnees, char * p_resultats )   ;
extern cr_t max( char * p_donnees, char * p_resultats ) ;

#define BIB_INT_NB_FONCTIONS 7
cr_t (*bib_int_tab_fonctions[BIB_INT_NB_FONCTIONS])(char * , char * ) = { plus , moins , prod , quot , reste , min , max } ;

#endif


