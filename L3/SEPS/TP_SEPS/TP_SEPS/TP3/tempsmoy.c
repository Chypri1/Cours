/*         TP3 SE&PS        */
/* tempsmoy.c Comte Clément */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int ExecuteCommande(int nbExec, char * commande){
/* Execution de la commande 'commande' nbExec fois en série
 * Retourne:
 *       0 si tout se passe bien   
 *       1 si le fils d'éxécution n'a pas été créé                         
 *      -1 si la commande n'a pas été trouvée               
 *      le cr du fils si la commande à été intérrompue par un exit ou un signal
 */

    int cr = 0;

    for(int i = 0; i < nbExec; i++){
        switch (fork())
        {
            case -1:
                return 1;
            case 0:
                execlp(commande, commande, NULL);
                exit(-1);
            default: wait(&cr);
            
        }
        
        if(cr) return cr;

    }

    return cr;
}

void PrintError(int cr){
/* Affiche en fonction de cr l"eereur correspondante */

    int signal = cr;
    int exitCode = cr>>( ( sizeof(int)/2 )* 4 );

    if(exitCode == 255)
        fprintf(stderr, "Erreur : La commande n'a pas été trouvée !\n");
    else if(exitCode)
        fprintf(stderr, "Erreur : Exit avec code erreur : %i\n", exitCode);
    else
        fprintf(stderr, "Erreur : Signal reçu : %i\n", signal);

}

long TimeDiff(struct timeval start, struct timeval end){
/* Calcule et renvoie la différence en µs entre start et end */
    return (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);

}

int RecherchePID(pid_t pid, pid_t pids[], int taille_pids){
/* Recherche le pid dans le tableau pids et renvoie le premier indice trouvé */

    for(int i = 0; i < taille_pids; i++){
        if(pids[i] == pid) return i;
    }

    return -1;
}

int compareInt(const int * a, const int * b){
/* fonction de comparaison pour le qsort */
    if(*a == *b) return 0;
    return (*a > *b? 1: -1);
}

int main(int argc, char * argv[]){

    char proc[strlen(argv[0])]; //nom de la commande actuel
    strcpy(proc, argv[0]);

    int nbProcessus, nbExec, cr, moy, index, afficheFin = 1;
    int tube[2];
    char commande[strlen(argv[2])]; //nom de la commande à éxécuter

    if(argc < 4){
        printf("./%s [nb exec] [commande] [nb proc]\n", proc);
        return 1;
    }
    
    nbExec = atoi(argv[1]); //nombre d'éxécution de la commande par processus
    nbProcessus = atoi(argv[3]); //nombre de processus fils à lancer
    int fdPoubelle = open("/dev/null", O_WRONLY); //ouverture de la poubelle
    strcpy(commande, argv[2]);

    //initialisation du tube
    pipe(tube);

    pid_t pids[nbProcessus];
    struct timeval start, end;
    long tmp;
    int tempsExec[nbProcessus];
    int tempsMoy[nbProcessus];
    pid_t pid;

    for(int i = 0; i < nbProcessus; i++){
        switch(pids[i] = fork()){

            case -1:
                printf("Erreur: fork() n'as pas pu créer un fils !\n");
                break;
            case 0:
                dup2(fdPoubelle, 1); //redirection de la sortie standard vers la poubelle pour les fils
                close(tube[0]); //fermeture en lecture du tube
                gettimeofday(&start, NULL);
                cr = ExecuteCommande(nbExec, commande);
                gettimeofday(&end, NULL);

                if(cr){ //si il y a une erreur
                    PrintError(cr);
                    cr = 1;
                }else{ //sinon calcule la moyenne de temps d'éxécution et envoie dans le tube
                    tmp = TimeDiff(start, end);
                    write(tube[1], &tmp, sizeof(int));
                    cr = 0;
                }

                close(tube[1]); //fermeture du tube en écriture
                exit(cr);

        }

    }

    close(tube[1]);


    while((pid = wait(&cr)) != -1){ //attente de tout les fils

        if(cr == 0){ //si il n'y a pas d'erreur recherche du pid puis ajout du temps moyen dans le tableau
            index = RecherchePID(pid, pids, nbProcessus);
            read(tube[0], &tempsExec[index], sizeof(int));
            tempsMoy[index] = tempsExec[index]/nbExec;
        }else{ //si il y a eu erreur on affiche pas le temps d'éxécution
            afficheFin = 0;
        }
    
    }

    if(afficheFin){
        qsort(tempsMoy, nbProcessus, sizeof(int), compareInt); //tri du tableau de moyenne par ordre croissant

        //affichage du tableau
        for(int i = 0; i < nbProcessus; i++){
            printf("tab[%i]: %i\n", i, tempsMoy[i]);
        }

        //affichage du temps d'éxécution
        if(nbProcessus%2==1){
            printf("\n Le temps moyen d'éxécution de la commande %s sur %i processus éxécuter %i fois est de %iµs\n", commande, nbProcessus, nbExec, tempsMoy[nbProcessus/2]);
        }else{
            moy = (tempsMoy[nbProcessus/2] + tempsMoy[nbProcessus/2-1]) / 2;
            printf("\n Le temps moyen d'éxécution de la commande %s sur %i processus éxécuter %i fois est de %iµs\n", commande, nbProcessus, nbExec, moy);
        }
    }

    return 0;
}