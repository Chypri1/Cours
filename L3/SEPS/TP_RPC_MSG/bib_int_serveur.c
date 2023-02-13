#include <stdio.h>

#include <bib_int.h>


extern
cr_t plus( char * p_donnees, char * p_resultats )
{
     int d1 = ((bib_int_donnees_t *)p_donnees)->d1 ;
     int d2 = ((bib_int_donnees_t *)p_donnees)->d2 ;
     (*(bib_int_resultats_t *)p_resultats) = d1 + d2 ;
     return(OK);
}

extern
cr_t moins( char * p_donnees, char * p_resultats )
{
     int d1 = ((bib_int_donnees_t *)p_donnees)->d1 ;
     int d2 = ((bib_int_donnees_t *)p_donnees)->d2 ;
     (*(bib_int_resultats_t *)p_resultats) = d1 - d2 ;
     return(OK);
}


extern
cr_t prod( char * p_donnees, char * p_resultats )
{
     int d1 = ((bib_int_donnees_t *)p_donnees)->d1 ;
     int d2 = ((bib_int_donnees_t *)p_donnees)->d2 ;
     (*(bib_int_resultats_t *)p_resultats) = d1 * d2 ;
     return(OK);
}

extern
cr_t quot( char * p_donnees, char * p_resultats )
{
     int d1 = ((bib_int_donnees_t *)p_donnees)->d1 ;
     int d2 = ((bib_int_donnees_t *)p_donnees)->d2 ;
     (*(bib_int_resultats_t *)p_resultats) = d1 / d2 ;
     return(OK);
}

extern
cr_t reste( char * p_donnees, char * p_resultats )
{
     int d1 = ((bib_int_donnees_t *)p_donnees)->d1 ;
     int d2 = ((bib_int_donnees_t *)p_donnees)->d2 ;
     (*(bib_int_resultats_t *)p_resultats) = d1 % d2 ;
     return(OK);
}

extern
cr_t min( char * p_donnees, char * p_resultats )
{
     int d1 = ((bib_int_donnees_t *)p_donnees)->d1 ;
     int d2 = ((bib_int_donnees_t *)p_donnees)->d2 ;
     (*(bib_int_resultats_t *)p_resultats) = ( d1 < d2 ? d1 : d2 ) ;
     return(OK);
}

extern
cr_t max( char * p_donnees, char * p_resultats )
{
     int d1 = ((bib_int_donnees_t *)p_donnees)->d1 ;
     int d2 = ((bib_int_donnees_t *)p_donnees)->d2 ;
     (*(bib_int_resultats_t *)p_resultats) = ( d1 > d2 ? d1 : d2 ) ;
     return(OK);
}
