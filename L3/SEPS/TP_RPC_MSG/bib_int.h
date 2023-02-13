#ifndef _BIB_INT_H_
#define _BIB_INT_H_

#include <commun.h>

/* 
 * Numero de la bibliotheque des int 
 * sert egalement d' Adresse/type du serveur RPC gerant les fonctions des int
 */
#define BIB_INT_NUM     11	


/* Type des donnees des fonctions int */
typedef struct bib_int_donnees
{
     int d1 ;
     int d2 ;
} bib_int_donnees_t ;

/* Type des resultats des fonctions int */
typedef int bib_int_resultats_t ;

/* Numero des fonctions 
 * 0 --> plus 
 * 1 --> moins 
 * 2 --> prod
 * 3 --> quot 
 * 4 --> reste 
 * 5 --> min 
 * 6 --> max 
 */

#endif
