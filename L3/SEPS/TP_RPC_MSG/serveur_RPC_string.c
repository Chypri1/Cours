#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

#include <messages.h>
#include <bib_string_serveur.h>



/* 
 * serveur RPC des fonctions sur les strings 
 */

int 
main( int nb_arg , char * tab_arg[] )
{     
 
     /*-----*/

     if( nb_arg != 1 )
     {
	  fprintf( stderr, "usage : %s\n" , tab_arg[0] );
	  exit(-1);
     }

     /***********/
     /* A FAIRE */
     /***********/
 
}
