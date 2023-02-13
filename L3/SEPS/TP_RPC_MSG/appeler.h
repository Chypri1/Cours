#ifndef _APPELER_H_
#define _APPELER_H_



#include <strings.h>
#include <sys/msg.h>
#include <messages.h>

extern cr_t appeler( key_t num_bib ,		/* Numero de la bibliotheque appelee, Adresse du serveur */
		     int num_fonc,		/* Numero de la fonction appelee */
		     char * p_donnees ,		/* Pointeur sur les donnees */
		     char * p_resultats )  ;	/* Pointeur sur le resultat */

#endif
