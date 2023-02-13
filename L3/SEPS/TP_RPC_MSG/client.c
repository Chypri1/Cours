#include <stdio.h>
#include <stdlib.h>

#include <bib_int.h>
#include <bib_string.h>
#include <bib_tab.h>

#include <appeler.h>

int 
main( int nb_arg , char * tab_arg[] )
{     
  key_t num_bib ;
  int choix_bib = 0 ;
  int num_fonc ;
  cr_t cr ;

  /*-----*/

  if( nb_arg != 1 )
    {
      fprintf( stderr, "usage : %s \n" , tab_arg[0] );
      exit(-1);
    }

  num_bib = 0 ;
  choix_bib = 0 ; 
  while(1)
    {       
      /* Saisie d'un message */
      do
	{
	  printf(" Liste des bibliotheques\n" ) ;
	  printf("  - Entiers --> 1\n" ) ;
	  printf("  - Strings --> 2\n" ) ;
	  printf("  - Tableau --> 3\n" ) ; 
	  printf(" Choix de la bibliotheque : ");
	  fflush( stdout );
	  scanf( "%d" , &choix_bib );
	  switch( choix_bib )
	    {
	    case 0 :
	      printf(" Arret client\n" ) ;
	      exit(0) ; 
	    case 1 :
	      num_bib = BIB_INT_NUM ;
	      break ;
	    case 2 :
	      num_bib = BIB_STRING_NUM ;
	      break ;
	    case 3 :
	      num_bib = BIB_TAB_NUM ;
	      break ;
	    default :
	      printf(" Choix bibliotheque incorrect %d (doit etre dans [1..3])\n" , choix_bib ) ;
	      break ; 
	    }
	}while( ( choix_bib < 1 ) || (choix_bib > 3 ) ) ;

      printf(" Saisie du numero de la fonction : ");
      fflush( stdout );
      scanf( "%d" , &num_fonc );

      switch( num_bib )
	{
	case BIB_INT_NUM :
	  {

	    bib_int_donnees_t d ;
	    bib_int_resultats_t r ;
	    
	    printf(" Saisie entier 1 : ");
	    fflush( stdout );
	    scanf( "%d" , &d.d1 );
	    
	    printf(" Saisie entier 2 : ");
	    fflush( stdout );
	    scanf( "%d" , &d.d2 );
	    
	    if( (cr = appeler(  num_bib , 
				num_fonc,
				(char *)&d ,
				(char *)&r ) ) )
	      {
		print_cr( cr ) ;
	      }
	    else
	      {
		printf(" Resultat = %d\n" , r );
	      }

	    break ; 
	  }
	  
	  /* ----------*/
	  
	case BIB_STRING_NUM :
	  {
	    bib_string_donnees_t d ;
	    bib_string_resultats_t r ;
	    
	    printf(" Saisie chaine de car. 1 : ");
	    fflush( stdout );
	    scanf( "%s" , d.s1 );
	    
	    printf(" Saisie chaine de car. 2 : ");
	    fflush( stdout );
	    scanf( "%s" , d.s2 );

	    if( num_fonc == 1 )
	      {
		printf(" Saisie chaine de car. 3 : ");
		fflush( stdout );
		scanf( "%s" , d.s3 );	
	      }
	    
	    if( (cr = appeler(  num_bib , 
				num_fonc,
				(char *)&d ,
				(char *)&r ) ) )
	      {
		print_cr( cr ) ;
	      }
	    else
	      {
		printf(" Resultat = %s\n" , r.r );
	      }

	    break ; 
	  }
	  
	  /* ----------*/
	  
	  case BIB_TAB_NUM :
	  {
	    bib_tab_donnees_t d ;
	    bib_tab_resultats_t r ;
	    int i ;
	    
	    printf(" Saisie d'un tableau :\n");
	    printf("  - nb elements : ");
	    fflush( stdout );
	    scanf( "%d" , &d.nb );

	    for(i=0 ; i<d.nb ; i++ )
	      {
		printf(" - element %d : " , i );
		fflush( stdout );
		scanf( "%d" , &d.t[i] );
	      }
	    
	    if( (cr = appeler(  num_bib , 
				num_fonc,
				(char *)&d ,
				(char *)&r ) ) )
	      {
		print_cr( cr ) ;
	      }
	    else
	      {
		printf(" Resultat = %d\n" , r );
	      }

	    break ; 
	  }
	  
	  /* ----------*/
	  
	default :
	  {
	    printf( "Erreur , numero de bibliotheque inconnue %d\n" , num_bib ) ;
	    exit(1) ;
	  }
	}

    }
  exit(0);
}
