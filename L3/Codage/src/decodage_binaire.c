#include <stdio.h>

#include "../lib/source.h"

/*Fonction qui permet de faire le decodage binaire*/
void decodage_binaire(int message[N],int taille){
    
    printf("\n version decode : \n");
    for(int i=0;i<taille;i++){
        if(message[i]==-1)
            message[i]=1;
        printf("%i ",message[i]);
    }
    printf("\n");
}