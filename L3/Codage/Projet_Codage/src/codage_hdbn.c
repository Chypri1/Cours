#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/source.h"

/*Fonction qui permet de faire le codage HDBn*/
int Codage_HDBn(int tab_message[N], int n){
    char message_binaire[N];
    
    int Pol=0;
    int compt_0=0;
    int polarite_viol=-1;
    int dernier_1;
    int i;
    printf("saisir un message en binaire supposé correct(Appuyez sur entrée pour finir votre message!): \n");
    scanf("%s",message_binaire);
    printf("version caractère : %s\n",message_binaire);
    printf("version chiffre :");

    for(i=0;message_binaire[i]!='\0';i++){
        tab_message[i] = message_binaire[i] -'0';
        printf("%i",tab_message[i]);
    }
    printf("\n");
    
    
    printf(" ");
    for(i=0;message_binaire[i]!='\0';i++){

        printf("%i ",tab_message[i]);

        if(tab_message[i]==1 ){ 
            tab_message[i]=pow(-1,Pol);
            Pol++;
            dernier_1=tab_message[i];
            compt_0=0;
        }
        else {
            compt_0++;
            if(compt_0==n+1){
                if (polarite_viol == 1){
                    if(dernier_1==1){    // si le bit-n est à 1 alors il passe à -1 et le bit actuelle passe à -1 
                        tab_message[i]=-1;
                        tab_message[i-n] =-1;
                    }
                    else{                   //sinon le bit actuelle passe à -1
                        tab_message[i]=-1;
                        Pol++;
                    }
                    polarite_viol =-1;         // le bit  de viol passe à l'inverse soit -1 dans ce cas 
                }
                else {                              
                    if(dernier_1==-1){
                        tab_message[i-n] = 1;
                        tab_message[i]=1;
                    }
                    else {
                        tab_message[i]=1;
                        Pol++;
                    }
                    polarite_viol =1;
                } 
                compt_0=0 ;
            }
        }
    }
    printf("\n");
    for(i=0;message_binaire[i]!='\0';i++){
        
        if(tab_message[i]== -1)
            printf("%i",tab_message[i]);
        else
            printf(" %i",tab_message[i]);
    }
    
    printf("\n");
    return i;
}






// bit de viol et condition


/*
if (polarite_viol == 1){
    if(resultat_message[i-n]==1){
        resultat_message[i-n] = -1;
        resultat_message[i]=-1;
    else 
        resultat_message[i]=-1
    }
    polarite_viol =-1
else 
     if(resultat_message[i-n]==-1){
        resultat_message[i-n] = 1;
        resultat_message[i]=1;
    else 
        resultat_message[i]=1
    }

}

*/

