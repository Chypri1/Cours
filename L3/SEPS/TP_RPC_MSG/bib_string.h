#ifndef _BIB_STRING_H_
#define _BIB_STRING_H_

#include <commun.h>

/* 
 * Numero de la bibliotheque des strings 
 * sert egalement d' Adresse/type du serveur RPC gerant les fonctions des strings
 */
#define BIB_STRING_NUM     22	


/* Type des donnees des fonctions string */
#define BIB_STRING_LG 64

typedef struct bib_string_donnees
{
  char s1[BIB_STRING_LG] ;
  char s2[BIB_STRING_LG] ;
  char s3[BIB_STRING_LG] ;
} bib_string_donnees_t ;

/* Type des resultats des fonctions string */
typedef struct bib_string_resultats
{
  char r[BIB_STRING_LG] ;
} bib_string_resultats_t ;

/* Numero des fonctions 
 * 0 --> concat
 * 1 --> translate
 */

#endif
