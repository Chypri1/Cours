#include <stdio.h>


#include <bib_tab.h>
#include <bib_int.h>
#include <appeler.h>

extern
cr_t min( char * p_donnees, char * p_resultats )
{
  bib_int_donnees_t nombres ;
  cr_t cr ;
  
  int nb = ((bib_tab_donnees_t *)p_donnees)->nb ;
  if( nb <= 0 )
    return(ERR_BIB_TAB_NB) ;
  
  int * vecteur = ((bib_tab_donnees_t *)p_donnees)->t ;
  int i = 0 ;
  (*(bib_tab_resultats_t *)p_resultats) = vecteur[0] ;
  for( i=1 ; i<nb ; i++ )
    {
      nombres.d1 = (*(bib_tab_resultats_t *)p_resultats) ;
      nombres.d2 = vecteur[i] ;
      if( ( cr = appeler(  BIB_INT_NUM , 
			   5 , /* fonction min */
			   (char *)&nombres ,
			   p_resultats ) ) )
	return(cr) ; 
    }
  return(OK) ; 
}

extern
cr_t max( char * p_donnees, char * p_resultats )
{
  bib_int_donnees_t nombres ;
  cr_t cr ;
  
  int nb = ((bib_tab_donnees_t *)p_donnees)->nb ;
  if( nb <= 0 )
    return(ERR_BIB_TAB_NB) ;
  
  int * vecteur = ((bib_tab_donnees_t *)p_donnees)->t ;
  int i = 0 ;
  (*(bib_tab_resultats_t *)p_resultats) = vecteur[0] ;
  for( i=1 ; i<nb ; i++ )
    {
      nombres.d1 = (*(bib_tab_resultats_t *)p_resultats) ;
      nombres.d2 = vecteur[i] ;
      if( ( cr = appeler(  BIB_INT_NUM , 
			   6 , /* fonction max */
			   (char *)&nombres ,
			   p_resultats ) ) )
	return(cr) ; 
    }

  return(OK) ; 
}
