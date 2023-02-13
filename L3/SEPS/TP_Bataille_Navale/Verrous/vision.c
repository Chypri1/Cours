#include <stdio.h>
#include <commun.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <mer.h>
#include <time.h>

/*--------------------* 
 * Main demon 
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
     char nomprog[256] ;
 
     /*----------*/

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );


     printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );
     //J'ouvre le fichier mer 
     int fd=0;
     if((fd=open(fich_mer, O_RDONLY , 0644 ))==-1)
     {
          fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_mer);
          exit(-1);
     }
     //Création d'une variable de la structure verrou que je mettrai en écriture 
     struct flock verrou;
     verrou.l_whence=0;
     //Création d'une variable de la structure stat pour avoir la date de modification du fichier mer
     struct stat vision;
     time_t timestamp = 0;
     int no_err = CORRECT ;
     int nb_bateaux;

     if( (no_err = mer_afficher(fd) )) 
     {
          fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
	     nomprog , no_err );
          exit(no_err) ;
     }
     //Ma boucle se termine lorsqu'il n'y a plus qu'un bateau sur la mer    
     while(nb_bateaux!=1)
     {
          stat(fich_mer,&vision); //J'actualise à chaque tour de boucle la variable vision pour avoir la date de modification
          if(timestamp<vision.st_mtime) //Puis je compare si du coup le fichier a été modifié
          {
               //Je pose un verrou en lecture sur tout le fichier juste le temps d'afficher la mer avec la fonction mer_afficher
               verrou.l_type=F_RDLCK;
               verrou.l_start=0;
               verrou.l_len=0;
              fcntl(fd,F_SETLKW,&verrou);
               timestamp=vision.st_mtime;
               if( (no_err = mer_afficher(fd) )) 
               {
                    fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
                    nomprog , no_err );
                    exit(no_err) ;
               }
               mer_nb_bateaux_lire(fd,&nb_bateaux);
               //Ensuite je débloque le verrou 
               verrou.l_type=F_UNLCK;
               verrou.l_start=0;
               verrou.l_len=0;
               fcntl(fd,F_SETLKW,&verrou);
          }
          mer_nb_bateaux_lire(fd,&nb_bateaux);
     }
               if(nb_bateaux==1)
                    if( (no_err = mer_afficher(fd) )) 
                    {    
                    fprintf( stderr, "%s : erreur %d dans mer_afficher\n",
                    nomprog , no_err );
                    exit(no_err) ;
                    }
     close(fd);
     
     printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

     exit(0);
}
