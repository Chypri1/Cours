#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include <string.h>



#define VRAI 1
#define FAUX 0
/*!
 * \file peinture.c
 * \brief programme à réaliser 
 */



/*!
 * \enum direction_s
 * \brief Valeurs des directions 
 * \typedef direction_t
 * \brief Type des directions
 */
typedef enum direction_s
  {
    HAUT , /*!< vers le haut */
    BAS , /*!< vers le bas */
    DROITE , /*!< à droite */
    GAUCHE /*!< à gauche */
  } direction_t ;

/*!
 * \enum vitesse_s
 * \brief Valeurs théoriques des vitesses 
 * \typedef vitesse_t
 * \brief Type des vitesses
 */
typedef enum vitesse_s
  {
    LENTE ,  /*!< 1000000 &micro;s */
    MOYENNE , /*!< 500000 &micro;s */
    RAPIDE /*!<    250000 &micro;s */
  } vitesse_t ;

/*! indicateur d'arret pour stopper la peinture du mur */
int arret = 0 ;
int tube[2];
bool PLEIN =FAUX;
/*! indicateur d'arret pour stopper la peinture du mur */
direction_t Direction = DROITE ;

/*!
 * \fn void stop( int sig )
 * \brief Handler pour arrêter coorectement la peinture dans la fonction mur
 */
static
void stop( int sig )
{
  arret = 1 ;
}

static void HandlerPeinture(int sig){
  read(tube[0],&Direction,sizeof(direction_t));
}

/*!
 * \fn int pinceau()
 * \brief Foncton à faire pour guider le pinceau
 */



static
int pinceau()
{  
  while(!arret){
    switch(getchar()){
      case 'z' :Direction=HAUT;break;
      case 'q':Direction=GAUCHE;break;
      case 's' :Direction=BAS;break;
      case 'd' :Direction=DROITE; break;
    }
    write(tube[1],&Direction,sizeof(direction_t));
    kill(getppid(),SIGUSR2);
  }
  return(0) ; 
}



/*!
 * \fn int mur( const int hauteur, const int largeur , const vitesse_t vitesse )
 * \param[in] hauteur : hauteur du mur 
 * \param[in] largeur : largeur du mur
 * \param[in] vitesse : vitesse du pinceau
 * \return 0
 */


static
int mur( const int hauteur, const int largeur , const vitesse_t vitesse ) 
{
  WINDOW * fenetre ;
  int i = hauteur/2 ;
  int j = largeur/2 ;
  useconds_t tempo = 0 ;
  
  
  int mat[hauteur][largeur];
   for(int k=0;k<hauteur;k++){
    for(int l=0;l<largeur;l++)
      mat[i][j]=0;
  }
  mat[i][j]=1;


  switch( vitesse )
    {
    case LENTE   : tempo = 1000000 ; break ;
    case MOYENNE : tempo =  500000 ; break ;
    case RAPIDE  : tempo =  250000 ; break ;
    default : tempo = 0 ; break ;
    }

  initscr() ; 

  fenetre= newwin( hauteur , largeur , 0, 0 );
  noecho() ; 

  box( fenetre , '|' , '-' ) ;


  wrefresh(fenetre) ;
  echo() ;
  
  while( ! arret )
    {
      PLEIN=VRAI;
      mat[i][j]=1;
      switch(Direction)
	{
	case HAUT :
	  if( i > 1 ) i-- ; 
	  break ;
	case BAS :
	  if( i < hauteur-2 ) i++ ; 
	  break ;
	case DROITE :
	  if( j < largeur-3 ) j++ ;
	  break ;
	case GAUCHE :
	  if( j > 1 ) j-- ; 
	  break ;
	default :
	    break ;
	}

      wmove( fenetre , i , j );
      wattron( fenetre , A_STANDOUT );
      wprintw(fenetre, "  " );
      wattroff( fenetre , A_STANDOUT ) ;
      wrefresh(fenetre) ;

      usleep(tempo);
      for(int k=1;k<hauteur-2;k++){
        for(int l=1;l<largeur-3;l++)
          if(mat[k][l]==0)
            PLEIN=FAUX;
      }
      if(PLEIN==VRAI)
        kill(getpid(),SIGINT);
    }
  
  noecho() ;
  

  wclear( fenetre ) ; 
  box( fenetre , '.' , '.' ) ;
  wrefresh( fenetre ) ;

  mvwprintw( fenetre , hauteur/2 , 1 , "Fin !!!" ) ; 
  wrefresh(fenetre) ;
  sleep(2) ; 


  endwin() ; 


  return(0) ; 
}
/*!
 * \brief programme principal 
 */
int
main( int argc , char * argv[] )
{
  if( argc != 4 )
    {
      printf(" usage : %s <Hauteur> <Largeur> <Vitesse>\n" , argv[0] ) ;
      printf("         avec <Vitesse> : L --> Lente\n" ) ;
      printf("         avec <Vitesse> : M --> Moyenne\n" ) ;
      printf("         avec <Vitesse> : R --> Rapide\n" ) ;
      exit(0);
    }

  /* Capture des arguments du Main */
  int H , L ;
  useconds_t V = 0 ;
  if( sscanf( argv[1] , "%d" , &H ) != 1 )
    {
      fprintf( stderr , "%s : mauvaise valeur pour la Hauteur [%s]\n" , argv[0] , argv[1] ) ;
      exit(1) ;
    }
  if( sscanf( argv[2] , "%d" , &L ) != 1 )
    {
      fprintf( stderr , "%s : mauvaise valeur pour la Largeur [%s]\n" , argv[0] , argv[2] ) ;
      exit(1) ;
    }
  if( strchr( "LMR", argv[3][0] ) == NULL )
    {
      fprintf( stderr , "%s : mauvaise valeur pour la vitesse [%s] (L,M ou R)\n" , argv[0] , argv[3] ) ;
      exit(1) ;
    }

  switch(argv[3][0])
    {
    case 'L' : V = LENTE   ; break ;
    case 'M' : V = MOYENNE ; break ;
    case 'R' : V = RAPIDE  ; break ;
    default : break ;
    }
  
  arret = 0 ;
  signal( SIGINT , stop ) ;
  pipe(tube);
  switch(fork()){
    case -1: 
      perror("erreur fork");
      exit(-1);
    case 0:
      close(tube[0]);
      pinceau();
      exit(0);
    default:
      close(tube[1]);
      signal(SIGUSR2,HandlerPeinture);
      mur( H , L , V ) ;
      exit(1);
  }  
}
