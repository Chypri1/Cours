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

/*--------------------* 
 * Main demon 
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
     char nomprog[256] ;
     int fd;/*----------*/

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );


     printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );

     /***********/
     /* A FAIRE */
     /***********/
     fd=open(fich_mer , O_RDWR , 0644);
     struct stat vision;
     stat(fich_mer,&vision);
     time_t * actual_time;

     //premier terminal pour init et second pour afficher 
     // penser à detruire le fichier texte
     mer_afficher(fd);

     while(1){
           
          stat(fich_mer,&vision);  //rafraichissement du stat de vision
          if(vision.st_mtime==actual_time){ //si derniere modif de vision == temps actuel
               mer_afficher(fd); //aficher plateau
               actual_time=vision.st_mtime;
          }
         
     }

     close(fd);

     printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

     exit(0);
}
