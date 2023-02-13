#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

/* 
 *  Programme principal 
 */



 /*
    CONSTANTE 
    energie<SEUIL
    #define BATEAU_TAILLE  4
    #define BATEAU_SEUIL_BOUCLIER 10
    #define BATEAU_MAX_ENERGIE 500
    #define BATEAU_DELAI_VAINQUEUR 5
 */


int
main( int nb_arg , char * tab_arg[] )
{
  
  char fich_mer[128] ;
  case_t marque = MER_CASE_LIBRE ;
  char nomprog[128] ;
  float energie = 0.0 ;
  
  
  
  int fd,no_err;
  int couler=1,nb_bateau=0;
  coords_t * liste_voisins;
  coord_t cible,coord;
  booleen_t touche,deplacement,acquisition;


  /*----------*/

  strcpy( nomprog , tab_arg[0] ) ;

  if( nb_arg != 4 )
    {
      fprintf( stderr , "Usage : %s <fichier mer> <marque> <energie>\n", 
	       nomprog );
      exit(-1);
    }

  if( strlen(tab_arg[2]) !=1 ) 
    {
      fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
	       nomprog , tab_arg[2] );
      exit(-1) ;
    }


  strcpy( fich_mer , tab_arg[1] );
  marque = tab_arg[2][0] ;
  sscanf( tab_arg[3] , "%f" , &energie );
  
  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)getpid());

  

  /***********/
  /* A FAIRE */
  /***********/

  /* init du verrou*/
  fd=open(fich_mer,O_RDWR,0644);

  

  /*création bateau*/
  /* ouvrir un teminal pour chaque bateau ou ./lance_navires.sh <fichier mer> <nb_bateaux> <energie>*/
  bateau_t * bateau;
  bateau=bateau_new(NULL,marque,getpid());


  /* on vérifie que le bateau puisse se placer dans le plateau */
  if( (no_err = mer_bateau_initialiser( fd , bateau)) )
	{
	  fprintf( stderr, "%s : erreur %d dans mer_bateau_initialiser\n",
		   nomprog , no_err );
	  if( no_err == ERREUR ) //  si il y a une erreur on quitte et le bateau n'est pas créé 
	    {
	      fprintf( stderr, "\t(mer_bateau_initialiser n'a pas pu placer le bateau \"%c\" dans la mer)\n" ,
		       bateau_marque_get(bateau) );
	    }
	  exit(no_err) ;
	}


  /* lecture et écriture des bateaux dans le fichier */
  mer_nb_bateaux_lire(fd,&nb_bateau);
  mer_nb_bateaux_ecrire(fd,nb_bateau+1);

  /* création du verrou */
  struct flock verrou;
  
  while(couler){
    
    
    /* initialisation du bateau */
    verrou.l_type=F_WRLCK;
    verrou.l_start= coord_position_get((*(*bateau).corps->coords));
    fcntl(fd,F_SETLKW,&verrou);





    printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n ", 
	  nomprog , marque , getpid() );

    /* affichage du nombre de bateau au début de chaque tour */
    mer_nb_bateaux_lire(fd,&nb_bateau);
    printf("nb de bateaux au début de l'initialisation : %d\n",nb_bateau);



    /* verification si il y a un bateau gagnant */
    if(nb_bateau==1){
      printf("\n\n le bateau %c a gagné\n\n",marque);
      exit(0);
    }

    /* verification si le bateau est touche */
    mer_bateau_est_touche(fd, bateau,&touche);
    if((touche) && energie <= BATEAU_SEUIL_BOUCLIER){
      mer_bateau_couler(fd,bateau);
      mer_nb_bateaux_ecrire(fd,nb_bateau-1);
      bateau_destroy(&bateau);
      exit(0);
    }
    
    else if((touche) && energie >= BATEAU_SEUIL_BOUCLIER){
        /* si le bateau est touche mais qu'il y a de l'energie pour le bouclier */
      energie *=0.95;
    }
    

    else{
        /* déplacement d'un bateau */
      if( (no_err = mer_voisins_rechercher( fd,bateau,&liste_voisins )) ) //Je recherche les voisins que je met dans une liste de voisins
	    {
	      fprintf( stderr, "%s : erreur %d dans mer_voisins_rechercher\n",nomprog , no_err );
	      exit(no_err) ;
	    }


      /* on pose un verrou pour chaque voisin du bateau */
      for(int i=0;i<coords_nb_get(liste_voisins);i++){
        coord=coords_coord_get(liste_voisins,i);
        verrou.l_type=F_RDLCK;
        verrou.l_start=coord_position_get(coord);

        fcntl(fd,F_SETLKW,&verrou);
      }


      /* modification de l'état du verrou */
      verrou.l_type=F_WRLCK;
      verrou.l_start=coord_position_get(coord);
      fcntl(fd,F_SETLKW,&verrou);

      /* deplacement du bateau */
      if( (no_err = mer_bateau_deplacer( fd,bateau,liste_voisins,&deplacement )) ) //Deplacement du bateau sur la mer 
	    {
	      fprintf( stderr, "%s : erreur %d dans mer_bateau_deplacer\n",nomprog , no_err );
	      exit(no_err) ;
	    }     
      if(deplacement){ /* si le déplacement est vrai alors il pred de l'energie */
        energie *=0.95;
      } 


      /* puis déverrouillage des voisins de l'ancienne position du bateau */
      for(int i=0;i<coords_nb_get(liste_voisins);i++){
        coord=coords_coord_get(liste_voisins,i);
        verrou.l_type=F_UNLCK;
        verrou.l_start=coord_position_get(coord);

        fcntl(fd,F_SETLKW,&verrou);
      }

      /*verification si il existe une cible */
      if( (no_err = mer_bateau_cible_acquerir( fd,bateau,&acquisition,&cible )) ) //Vérifie si la cible est dans un bateau si c'est le cas acquisition renvoie VRAI
      {
        fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_acquerir\n",nomprog , no_err );
        exit(no_err) ;
      }   

      /* modification du verrou */
      verrou.l_type=F_WRLCK;
      verrou.l_start=coord_position_get(cible);
      fcntl(fd,F_SETLKW,&verrou);


      /* si il existe une cible alors il doit y avoir un tir */

      if(acquisition){
        if( (no_err = mer_bateau_cible_tirer( fd,cible)) )
	        {
	          fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_tirer\n",nomprog , no_err );
	          exit(no_err) ;
	        }        energie *=0.95;
      }
    } 

    printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ", 
      nomprog , marque , getpid() );

    
    /* deverrouillage du fichier entier */
    verrou.l_type= F_UNLCK;
    fcntl(fd,F_SETLKW,&verrou);
    sleep(1);
  }

  /* fermeture du fichier */
  close(fd);
  exit(0);
}
