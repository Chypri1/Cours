#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

#include <sys/msg.h>
#include <messages.h>

/* Variable globales */
int Dossard ;
int file_id ;
int num_msg;

/* Handlers */
void SigintHandler(int sig){

  requete_t req;
  ack_t ack;

  int recu;

  req.type = PC_COURSE;
  req.corps.dossard = Dossard;
  req.corps.etat = ABANDON;
  req.corps.num_message = num_msg;

  do{
    /* Envoie du message d'abandon */
    msgsnd(file_id, &req, sizeof(req), 0);

    sleep(1);

    /* Confirmation */
    recu = msgrcv(file_id, &ack, sizeof(ack_t), Dossard, IPC_NOWAIT);

  }while(recu == -1);

  printf("Heho\n");

  /* Fin du coureur */
  if(ack.ack == ABANDON_ACK){
    printf("Coureur %i a abandonné !\n", Dossard);
    exit(0);
  }else{
    printf("Erreur!\n");
    exit(-1);
  }

}

/* Programme Principal */
int 
main( int nb_arg , char * tab_arg[] )
{     
  int file_cle;
  num_msg = 0;

  etat_coureur_t etat_c = EN_COURSE; //gérer fin de boucle

  requete_t req;
  reponse_t rep;

  /*-----*/

  Dossard = getpid() ; 

  if( nb_arg != 2 ){
    fprintf( stderr, "usage : %s <cle de file>\n" , tab_arg[0] );
    exit(-1);
  }

  if( sscanf( tab_arg[1] , "%d" , &file_cle) != 1 ){
    fprintf( stderr, "%s : erreur , mauvaise cle de file (%s)\n" , tab_arg[0]  , tab_arg[1] );
    exit(-2);
  }

  /* Récupération de la file de message */
  if((file_id = msgget(file_cle, 0)) == -1){
    perror("Erreur lors de la récupération de file !");
    exit(-3);
  }

  printf("Dossard coureur : %i \n", Dossard);

  /* Capture du signal SIGINT */
  struct sigaction sa_int;
  sa_int.sa_flags = 0;
  sa_int.sa_handler = SigintHandler;
  sigemptyset(&(sa_int.sa_mask));

  sigaction(SIGINT, &sa_int, NULL);

  req.type = PC_COURSE;
  req.corps.dossard = Dossard;
  req.corps.etat = EN_COURSE;

  /* Boucle de course */
  while(etat_c == EN_COURSE){

    req.corps.num_message = num_msg;

    /* Envoie d'une demande de déplacment */
    msgsnd(file_id, &req, sizeof(requete_t), 0);
    num_msg ++;

    if(msgrcv(file_id, &rep, sizeof(reponse_t), Dossard, IPC_NOWAIT) != -1){

      if(rep.corps.compte_rendu == OK){
        etat_c = rep.corps.etat;
      }else if(rep.corps.compte_rendu == ERR_NUM_MESSAGE){
        printf("Numero de message incorrect ! \n");
        kill(Dossard, SIGINT);
      }

      /* Affiche du parcours */
      messages_afficher_parcours(&rep);

    }

    /* Attente avant prochain tour */
    messages_attendre_tour();

  }

  if(etat_c == ARRIVE) printf("Le coureur %d est arriver au bout de la course !\n", Dossard);
  if(etat_c == DECANILLE) printf("Le coureur %d s'est décanillé !\n", Dossard);
  
  exit(0);
}
