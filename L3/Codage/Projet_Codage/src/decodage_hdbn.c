
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "../lib/source.h"



/*Fonction qui permet de faire le decodage HDBn*/
int decodage_HDBn(int message[N],int n,int taille_message){

    /* LISTE DES ENTREES
		- message : Contient le message hdbn précedemment codé
        - n : Contient la taille de la zone de recherche 
	*/

	/* LISTE DES SORTIES
		- message_decode : Contient le message hdbn décodé 
	*/
	int message_decode[N];
	/* LISTE DES VARIABLES

		- compt_0 : Nombre de zéro à la suite que le message contient
	*/

    int i;
    int compt_0=0;
    polarite polarite_viol=POSITIF; // booleen 
	
    for(i=0;i<taille_message;i++){
        message_decode[i]=0;
    }
    
    for(i=0;i<taille_message;i++){


       
        if(message[i]==1){
            if(message[i-n]==1 && compt_0==(n-1) && polarite_viol){
                message_decode[i]=0;
                message_decode[i-n]=0;
                polarite_viol=NEGATIF;
            }
            /* condition  bizarre ou il n'y a pas de bit de bourrage*/
            else if(message_decode[i-n-1]==1 && compt_0>=(n-1) && polarite_viol){
                message_decode[i]=0;
                polarite_viol=NEGATIF;
            }

            else {
                message_decode[i]=1;
            }
            compt_0=0;
        }
        else if(message[i]==-1){
            if(message[i-n]==-1 && compt_0==(n-1) && !polarite_viol){
                message_decode[i]=0;
                message_decode[i-n]=0;
                polarite_viol=POSITIF;
            }
            /* condition  bizarre ou il n'y a pas de bit de bourrage*/
            else if(message_decode[i-n-1]==-1 && compt_0>=(n-1)  && !polarite_viol){
                message_decode[i]=0;
                polarite_viol=POSITIF;
            }

            else {
                message_decode[i]=1;
            }
            compt_0=0;
        }   
        else {
            compt_0++;
            message_decode[i]=0;
        }
        
    }




    printf("message decode :\n");
    for(i=0;i<taille_message;i++)
        printf(" %d",message_decode[i]);
    printf("\n");
    return 1;

}


