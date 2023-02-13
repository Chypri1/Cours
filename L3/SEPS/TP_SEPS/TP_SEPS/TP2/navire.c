/* 
 * Programme pour processus navire :
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mer.h>
#include <bateaux.h>

/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

#define SIG_DEPLACER_BATEAU SIGUSR1
int Energie ; 
int EnVie;
pid_t pid_amiral ;

/*
 * Handlers 
 */

void QuitHandler(int sig){

  EnVie = 0;

}

void TirDessusHandler(int sigl){

  kill(pid_amiral, SIGUSR2);
  EnVie = 0;
  printf("Bateau coulé ! navire : %d\n", getpid());

}


/*
 * Programme Principal 
 */

int
main( int nb_arg , char * tab_arg[] )
{
  char nomprog[128] ;
  pid_t pid_bateau = getpid()  ;

  /*----------*/

  /* 
   * Capture des parametres 
   */

  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <pid amiral>\n", 
	       tab_arg[0] );
      exit(-1);
    }

  /* Nom du programme */
  strcpy( nomprog , tab_arg[0] );
  sscanf( tab_arg[1] , "%d" , &pid_amiral ) ; 

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)pid_bateau);


  /* Affectation du niveau d'energie */
  Energie = random()%BATEAU_MAX_ENERGIE ;
  
  printf( "\n\n--- Debut bateau [%d]---\n\n" , pid_bateau );

  /*
   * Deroulement du jeu 
   */

  int ignore = 1;
  EnVie = 1;

  struct sigaction sig_action_quit, sig_action_gagne, sig_action_tir, restoreSIGQUIT, restoreSIGUSR1, restoreSIGUSR2;

  /* Capture du signal pour gagner de navire (SIGUSR1) */
  sig_action_gagne.sa_flags = 0;
  sig_action_gagne.sa_handler = QuitHandler;
  sigemptyset(&sig_action_gagne.sa_mask);
  sigaddset(&sig_action_gagne.sa_mask, SIGUSR2);

  sigaction(SIGUSR1, &sig_action_gagne, &restoreSIGUSR1);

  /* Capture du signal de tir de navire (SIGUSR2) */
  sig_action_tir.sa_flags = 0;
  sig_action_tir.sa_handler = SIG_IGN;
  sigemptyset(&sig_action_tir.sa_mask);
  sigaddset(&sig_action_tir.sa_mask, SIGUSR1);

  sigaction(SIGUSR2, &sig_action_tir, &restoreSIGUSR2);

  /* Capture du signal SIGQUIT */
  sig_action_quit.sa_flags = 0;
  sig_action_quit.sa_handler = QuitHandler;
  sigemptyset(&sig_action_quit.sa_mask);
  sigaddset(&sig_action_quit.sa_mask, SIGUSR2|SIGUSR1);

  sigaction(SIGQUIT, &sig_action_quit, &restoreSIGQUIT);

  while(EnVie){

    sleep(random()%2);

    kill(pid_amiral, SIG_DEPLACER_BATEAU);
    Energie -= Energie*0.05;

    if(Energie < BATEAU_SEUIL_BOUCLIER && ignore==1){
      sig_action_tir.sa_handler = TirDessusHandler;
      sigaction(SIGUSR2, &sig_action_tir, NULL);
      ignore = 0;
    }

    printf("Energie navire %d : %d\n", getpid(), Energie);
  }

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  /* Remise en place des anciennes actions sur les signaux capturés */
  sigaction(SIGUSR1, &restoreSIGQUIT, NULL);
  sigaction(SIGUSR1, &restoreSIGUSR1, NULL);
  sigaction(SIGUSR1, &restoreSIGUSR2, NULL);

  exit(0);
}

