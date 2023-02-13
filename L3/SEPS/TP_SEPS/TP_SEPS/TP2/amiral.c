/* 
 * Programme pour processus navire-amiral :
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#include <mer.h>
#include <bateaux.h>

#define SIG_GAGNER SIGUSR1
#define SIG_TIR_POSSIBLE SIGUSR2

/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

char Nom_Prog[256] ;
bateaux_t * listeBateaux;
int fd_mer;
int JeuEnCours, Demarre;

/*
 * FONCTIONS LOCALES
 */

void DeplacementNavireHandler(int sig, siginfo_t * sig_info, void * null){
     
     bateau_t * bateau;
     int pid = sig_info->si_pid;
     int nb_bateau;
     mer_nb_bateaux_lire(fd_mer, &nb_bateau);

     booleen_t boule;

     coords_t * coordonnees;
     coord_t coordonnees_tir;

     int indiceBateau = bateaux_pid_seek(listeBateaux, pid);
     int indiceBateauCible;

     /*
      * Si le bateau existe on le récupère dans la liste
      * Sinon on le créer
      */
     if(indiceBateau == -1){

          if((listeBateaux->nb + 'A') > 'Z'){
               printf("ERREUR - Il y a trop de bateaux sur la mer ! pid navire : %d\n", pid);
               kill(pid, SIGQUIT);
               return;
          }
          bateau = bateau_new(NULL, listeBateaux->nb + 'A', pid);
          if(mer_bateau_initialiser(fd_mer, bateau) != ERREUR){
          
               bateaux_bateau_add(listeBateaux, bateau);
               printf("Bateaux créer : ajout dans la liste\n");
               indiceBateau = bateaux_pid_seek(listeBateaux, pid);

               mer_nb_bateaux_ecrire(fd_mer, ++nb_bateau);
               if(nb_bateau >= 2 && Demarre == 0) Demarre = 1;

          }else{
               printf("ERREUR - Le bateau n'a pas pu être initialisé ! pid navire : %d\n", pid);
               kill(pid, SIGQUIT);
               return;
          }

     }

     bateau = bateaux_bateau_get(listeBateaux, indiceBateau);

     /* Si la partie a démarrer et qu'il n'y a plus qu'un bateau le bateau gagne*/
     if(nb_bateau < 2 && Demarre){
          printf("Navire %c gagne !\n", bateau->marque);
          JeuEnCours = 0;
          kill(pid, SIG_GAGNER);
          return;
     }

     /*Déplacement du bateau*/
     mer_voisins_rechercher(fd_mer, bateau, &coordonnees);
     mer_bateau_deplacer(fd_mer, bateau, coordonnees, &boule);

     /*
      * Recherche d'une cible
      * Si une cible est trouvé :
      *  - envoie du signal SIG_TIR_POSSIBLE (SIGUSR2)
      */
     mer_bateau_cible_acquerir(fd_mer, bateau, &boule, &coordonnees_tir);
     if(boule == VRAI){
          indiceBateauCible = bateaux_coord_seek(listeBateaux, coordonnees_tir);
          if(indiceBateauCible >= 0){
               printf("Pid receveur tir : %d\n", bateaux_bateau_get(listeBateaux, indiceBateau)->pid);
               kill(bateaux_bateau_get(listeBateaux, indiceBateau)->pid, SIG_TIR_POSSIBLE);
          }
     }

     system("clear");
     printf("Démarré : %d\n", Demarre);
     mer_afficher(fd_mer);

}

void CoulerNavireHandler(int sig, siginfo_t * sig_info, void * null){
     
     int nb_bateau;
     int indiceBateau = bateaux_pid_seek(listeBateaux, sig_info->si_pid);
     bateau_t * bateau = bateaux_bateau_get(listeBateaux, indiceBateau);

     mer_bateau_couler(fd_mer, bateau);
     bateaux_bateau_del(listeBateaux, indiceBateau);
     
     mer_nb_bateaux_lire(fd_mer, &nb_bateau);
     mer_nb_bateaux_ecrire(fd_mer, --nb_bateau);

     system("clear");
     mer_afficher(fd_mer);

}

/*
 * Programme Principal
 */
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;

     /*----------*/

     /* 
      * Capture des parametres 
      */

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer> \n", 
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( Nom_Prog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );
     
     listeBateaux = bateaux_new();

     /*
      * Affichage pid bateau amiral 
      */
     
     printf(" PID bateau amiral = %d\n" , getpid() ) ;

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());
 
     /*Ouverture du fichier mer*/
     fd_mer = open(fich_mer, O_RDWR);

     JeuEnCours = 1;
     Demarre = 0;

     struct sigaction sig_action_deplacement, sig_action_tir, restoreSIGUSR1, restoreSIGUSR2;

     /* Capture du signal de déplacment de navire (SIGUSR1) */
     sig_action_deplacement.sa_flags = SA_SIGINFO;
     sig_action_deplacement.sa_sigaction = DeplacementNavireHandler;
     sigemptyset(&sig_action_deplacement.sa_mask);
     sigaddset(&sig_action_deplacement.sa_mask, SIGUSR2);

     sigaction(SIGUSR1, &sig_action_deplacement, &restoreSIGUSR1);

     /* Capture du signal de tir de navire (SIGUSR2) */
     sig_action_tir.sa_flags = SA_SIGINFO;
     sig_action_tir.sa_sigaction = CoulerNavireHandler;
     sigemptyset(&sig_action_tir.sa_mask);
     sigaddset(&sig_action_tir.sa_mask, SIGUSR1);

     sigaction(SIGUSR2, &sig_action_tir, &restoreSIGUSR2);


     /* Boucle infini en l'attente de signaux */
     while(JeuEnCours);

     printf("\n\n\t----- Fin du jeu -----\n\n");

     sigaction(SIGUSR1, &restoreSIGUSR1, NULL);
     sigaction(SIGUSR2, &restoreSIGUSR2, NULL);

     exit(0);
}

