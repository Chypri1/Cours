#include <stdio.h>
#include <string.h>

#include <bib_string.h>


extern
cr_t concat( char * p_donnees, char * p_resultats )
{
  char * s1 = ((bib_string_donnees_t *)p_donnees)->s1 ;
  char * s2 = ((bib_string_donnees_t *)p_donnees)->s2 ;
  char * r  = ((bib_string_resultats_t *)p_resultats)->r ;
  strcpy ( r , s1 ) ;
  strcat ( r , s2 ) ;
  return(OK);
}

extern
cr_t translate( char * p_donnees, char * p_resultats )
{
  char * donnee    = ((bib_string_donnees_t *)p_donnees)->s1 ;
  char * tr1       = ((bib_string_donnees_t *)p_donnees)->s2 ;
  char * tr2       = ((bib_string_donnees_t *)p_donnees)->s3 ;
  char * resultat  = ((bib_string_resultats_t *)p_resultats)->r ;
  int i_tr = 0 ; 
  int l_tr = strlen( tr1 ) ;

  if( strlen( tr2 ) != l_tr )
    return(ERR_BIB_STRING_TR) ;
  
  char * c = NULL ; 
     
  strcpy( resultat , donnee ) ;
     
  for( i_tr=0 ; i_tr<l_tr ; i_tr++ )
    {
      c = strchr( resultat , tr1[i_tr]);
      while( c != NULL )
	{
	  c[0] = tr2[i_tr] ; 
	  c = strchr( c+1 , tr1[i_tr]);
	}
    }
     
  return(OK);     
}
