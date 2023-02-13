#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

// ./navire ../mer.txt A 50
/* 
 *  Programme principal 
 */
 /*
  LE BATEAU SE DEPLACE ET TIRE
    energie<SEUIL
    #define BATEAU_TAILLE  4
    #define BATEAU_SEUIL_BOUCLIER 10
    #define BATEAU_MAX_ENERGIE 500
    #define BATEAU_DELAI_VAINQUEUR 5
 */

//Fonction qui enlève le verrou
void verrou_deblocage(int fd,struct flock verrou,int start,int len){
  verrou.l_type=F_UNLCK;
  verrou.l_start=start;
  verrou.l_len=len;
  fcntl(fd,F_SETLKW,&verrou);
}

//Fonction qui utilise le verrou en écriture
void verrou_ecriture(int fd,struct flock verrou,int start,int len){
  verrou.l_type=F_WRLCK;
  verrou.l_start=start;
  verrou.l_len=len;
  fcntl(fd,F_SETLKW,&verrou);
}

//Fonction qui utilise le verrou en écriture
void verrou_lecture(int fd,struct flock verrou,int start,int len){
  verrou.l_type=F_RDLCK;
  verrou.l_start=start;
  verrou.l_len=len;
  fcntl(fd,F_SETLKW,&verrou);
}

int
main( int nb_arg , char * tab_arg[] )
{
  char fich_mer[128] ;
  case_t marque = MER_CASE_LIBRE ;
  char nomprog[128] ;
  float energie = 0.0 ;

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
  //Pour enlever 5% d'énergie lors d'un déplacement
  float dep=energie*0.05;
  printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n ", nomprog , marque , getpid() );
  //Ouverture du fichier
  int fd=open(fich_mer,O_RDWR, 0644);

  //Création du verrou
  struct flock verrou;
  verrou.l_whence=SEEK_SET;

  //Création des variables nécessaires à la création d'un bateau
  booleen_t touche=FAUX;
  booleen_t deplacement =VRAI;
  booleen_t acquisition ;
  int no_err = CORRECT ;
  //Création des coordonnées
  coord_t *liste_voisins;
  coord_t coord;
  coord_t cible;
  bateau_t * bateau=bateau_new(NULL,marque,getpid());
  //Je pose un verrou en écriture sur tout le fichier pour mettre le bateau sur la mer lorsque j'utilise mer_bateau_initialiser 
  verrou_ecriture(fd,verrou,0,0);
  //Je met le bateau sur la mer et je vérifie que la mer ait assez de place pour placer le bateau
  if(no_err=mer_bateau_initialiser(fd,bateau))
  {
	  fprintf( stderr, "%s : erreur %d dans mer_bateau_initialiser\n",
		   nomprog , no_err );
	  if( no_err == ERREUR ) //Si la mer n'a plus de place je détruit l'objet bateau puis je fait un exit pour fermer le processus
	    {
	      fprintf( stderr, "\t(mer_bateau_initialiser n'a pas pu placer le bateau \"%c\" dans la mer)\n" ,
		       bateau_marque_get(bateau) );
	    }
    bateau_destroy(&bateau);
	  exit(no_err) ;
	}
  //Puis je débloque le verrou
  verrou_deblocage(fd,verrou,0,0);
  //le nombre de bateaux dans la mer
  int nb_bateaux;
  mer_nb_bateaux_lire(fd,&nb_bateaux); //Lecture du nombre de bateaux sur la mer
  mer_nb_bateaux_ecrire(fd,(nb_bateaux+1)); //Incrémentation du nombre de bateaux sur la mer  

  while(bateau!=NULL)
  {
    sleep(1.5);
    mer_nb_bateaux_lire(fd,&nb_bateaux); //Lecture du nombre de bateaux sur la mer
    mer_bateau_est_touche(fd,bateau,&touche); //regarde si il a été touché
    if(touche) //
      if(energie<=BATEAU_SEUIL_BOUCLIER)
      {
        mer_bateau_couler(fd,bateau); //si il a été touché on coule le bateau càd on enlève le bateau du fichier mer
        mer_nb_bateaux_ecrire(fd,(nb_bateaux-1)); //Décrémente le nombre de bateaux sur la mer
        bateau_destroy(bateau); //on détruit l'objet bateau je ne sais pas si faut le détruire vu qu'on ferme le processus après
        exit(0); //et on ferme le programme
      }
    mer_nb_bateaux_lire(fd,&nb_bateaux); //Lecture au cas où un bateau a coulé
    printf("nb_bateaux=%i\n",nb_bateaux);
    //si le bateau est le seul sur la mer
    if(nb_bateaux==1)
    {
      printf("\n");
      bateau_printf( bateau ); 
      printf("le bateau %i de marque %c a gagné \n",getpid(),bateau_marque_get(bateau));
      //mer_nb_bateaux_ecrire(fd,(nb_bateaux-1));//Décrémente le nombre de bateaux je le met uniquement pour qu'il se finisse
      exit(0); //et je ferme le programme
    }  
    //deplacement
    if(energie>BATEAU_SEUIL_BOUCLIER)
    { 
      if( (no_err = mer_voisins_rechercher( fd,bateau,&liste_voisins )) ) //Je recherche les voisins que je met dans une liste de voisins
	    {
	      fprintf( stderr, "%s : erreur %d dans mer_voisins_rechercher\n",nomprog , no_err );
	      exit(no_err) ;
	    }
      //Application du verrou en mode écriture sur le fichier pour chaque case de la liste de voisins
      //Vu que le bateau peut se déplacer en verticale je prend chaque case de la liste de voisins et je lui met un verrou à tel position de longueur 1
      for(int ind_coord=0 ; ind_coord<coords_nb_get(liste_voisins); ind_coord++ )
      {
        coord = coords_coord_get(liste_voisins, ind_coord);
        verrou_ecriture(fd,verrou,coord_position_get(coord),1);
      }
      if( (no_err = mer_bateau_deplacer( fd,bateau,liste_voisins,&deplacement )) ) //Deplacement du bateau sur la mer 
	    {
	      fprintf( stderr, "%s : erreur %d dans mer_bateau_deplacer\n",nomprog , no_err );
	      exit(no_err) ;
	    }
      //J'enlève le verrou de la même manière qu'en écriture en faisant case par case
      for(int ind_coord=0 ; ind_coord<coords_nb_get(liste_voisins) ; ind_coord++ )
      {
        coord = coords_coord_get(liste_voisins, ind_coord);
        verrou_deblocage(fd,verrou,coord_position_get(coord),1);
      }

      coords_destroy(&liste_voisins); //je détruis la liste de voisins
      
      if( deplacement )
      {
	      printf( "Deplacement reussi\n");
        energie-=dep; //je décrémente de 5% l'énergie lors d'un déplacement réussi
        printf("Energie restant= %f\n",energie);
      }
      else
	      printf(" Deplacement impossible\n");
    }
    //tir

   	    if( (no_err = mer_bateau_cible_acquerir( fd,bateau,&acquisition,&cible )) ) //Vérifie si la cible est dans un bateau si c'est le cas acquisition renvoie VRAI
	      {
	        fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_acquerir\n",nomprog , no_err );
	        exit(no_err) ;
	      }
        if( acquisition ) //Le bateau tire si acquisition est vrai
	      {
	        printf("Acquisition d'une cible par le bateau \n");
	        bateau_printf( bateau );
	        printf( "\n-->La cible choisie est la case ");
	        coord_printf( cible );
  	      printf( "\n\n");
          verrou_ecriture(fd,verrou,coord_position_get(cible),1); //Je verrouille en écriture la case de la cible 
	        if( (no_err = mer_bateau_cible_tirer( fd,cible)) )
	        {
	          fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_tirer\n",nomprog , no_err );
	          exit(no_err) ;
	        }
          verrou_deblocage(fd,verrou,coord_position_get(cible),1); //Puis je débloque la case de la cible
	      }
	      else
	      {
	        printf("Pas d'acquisition de cible pour le bateau \n");
	        bateau_printf( bateau );
	        printf( "\n");
	      }

  }
  close(fd);
  /***********/
  /* 
  */
  /***********/

  printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ", 
	  nomprog , marque , getpid() );

  exit(0);
}
