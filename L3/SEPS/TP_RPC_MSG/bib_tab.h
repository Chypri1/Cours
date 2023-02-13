#ifndef _BIB_TAB_H_
#define _BIB_TAB_H_

#include <commun.h>

/* 
 * Numero de la bibliotheque des tab 
 * sert egalement d' Adresse/type du serveur RPC gerant les fonctions des tab
 */
#define BIB_TAB_NUM     33	


/* Type des donnees des fonctions tab */
#define BIB_TAB_TAILLE 64 

typedef struct bib_tab_donnees
{
     int nb ;
     int t[BIB_TAB_TAILLE] ;
} bib_tab_donnees_t ;

/* Type des resultats des fonctions tab */
typedef int bib_tab_resultats_t ;

/* Numero des fonctions 
 * 0 --> min 
 * 1 --> max 
 */

#endif
