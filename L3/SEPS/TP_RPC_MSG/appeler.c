#include <appeler.h>

extern
cr_t appeler( key_t num_bib , 
	      int num_fonc,
	      char * p_donnees ,
	      char * p_resultats ) 
{
  /***********/
  /* A FAIRE */
  /***********/
  int msgid=(msgset(num_bib,0666)); 
  demande_t d;// a revoir la struct
  resultats_t r; // a revoir la struct
  /* appel de la fonction */
  d.type=num_bib;// a voir combien vaut serveur
  d.corps.pid=getpid();
  d.corps.numfonc=num_fonc;
  msgcpy(d.corps.donnees,p_donnees, TAILLE_MESSAGE);// voir pour taille-message et o.corps.données
  msgsnd(msgid,&d,sizeof(d),0);//corps demande_t a voir 
  msgrcv(msgid,&r,sizeof(r),getpid(),0);// corps_resulats_t a voir
  msgcpy(p_resultats,r.corps.resultats,TAILLE_DONNEES)// voir TAILLE_DONNEES et pour r

  return(OK) ; 
}
