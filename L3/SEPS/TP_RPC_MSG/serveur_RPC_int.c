#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

#include <messages.h>
#include "bib_int_serveur.h"


/* 
 * serveur RPC des fonctions sur les entiers 
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
     int num_fonc;

     bib_int_donnees_t dem;
     bib_int_resultats_t res;
     int num_bib=atoi(argv[1]);
     int msgid=mesgset(num_bib,0666 | IGR_CREAT);
     while(1){
          msgrcv(msgid,&dem,sizeof(int),num_fonc,0);// revoir BIB_INT_SERVEUR 
          res=bib_int_tab_fonctions[num_fonc](dem,res);
          msgsnd(msgid,&res,sizeof(int))
     }
     

}
