#include <stdio.h>
#include <math.h>

#include "../lib/source.h"

/*Fonction qui permet de faire le codage binaire*/
void codage_binaire(int tab_message[N],int * taille){
    char message_binaire[N];
    int Pol=0;
    int i;
    booleen isCorrect=VRAI;

    do{
        isCorrect=VRAI;
        printf("Saisir un message en binaire (Appuyez sur entree pour finir votre message!): \n");
        scanf("%s",message_binaire);
        for(int j=0;message_binaire[j]!='\0';j++){
            if(!isdigit(message_binaire[j])){
               isCorrect=FAUX;
               break; 
            }
        }
    }while(isCorrect==FAUX);
    printf("Votre message : \n");    
    for(i=0;message_binaire[i]!='\0';i++){
        tab_message[i] = message_binaire[i] -'0';
        printf("%i ",tab_message[i]);
    }

    
    for(int j=0;message_binaire[j]!='\0';j++){
        if(tab_message[j]==1 ){ 
            Pol++;
            tab_message[j]=pow(-1,Pol);
        }
    }
    
    printf("\n");
    printf("version finale : \n");
    for(int v=0;message_binaire[v]!='\0';v++){
        printf("%i ",tab_message[v]);
    }
    printf("\n");
    *(taille)=i;
}