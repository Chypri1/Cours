#include <stdio.h>
#include <stdlib.h>
#include "../lib/codage_hdbn.h"
#include "../lib/codage_binaire.h"
#include "../lib/decodage_binaire.h"
#include "../lib/source.h"
#include "../lib/codage_arithmetique.h"
#include "../lib/decodage_arithmetique.h"
#include "../lib/decodage_hdbn.h"

int main()
{
    int message[N];
    int choix_n,choix_codage;
    double message_compresse;
    int taille_message;
    int nb_symboles;
    double borne_finale[2];
    hash tab_symbole[N];

    borne_finale[0]=(double)0;
    borne_finale[1]=(double)1;
    /*choix du type de codage */
    do{
        
        printf("1 pour codage arthmétique.\n");
        printf("2 pour le codage HDBn.");
        printf("vous devez choisir 1 ou 2 : \n");
        scanf("%i",&choix_codage);
    }while(choix_codage<1 || choix_codage >2);
    
    if(choix_codage==1){
        printf("vous avez choisi le codage Arithmétique.\n");
    
        taille_message=codage_arithmetique(borne_finale,tab_symbole,&nb_symboles); //Fonction qui fait le codage arithmétique


        printf("Passage au decodage \n");
        printf("\n");
        message_compresse =borne_finale[0];
        printf("Le message compresse etant compris dans un intervalle tres petit il sera automatiquement egale a la borne inferieur soit %lf\n",message_compresse);
        decodage_arithmetique(borne_finale,tab_symbole,message_compresse,taille_message,nb_symboles); //Fonction qui fait le decodage arithmetique
    }   

    /*second choix pour savoir si le codage est binaire simple ou plutôt HDBn */
    else   { 
        printf("Vous avez choisi le codage HDBn.\n");
        do{
        printf("Vous devez choisir un nombre entre 1 et n : \n");
        printf("Soit 1 pour le codage binaire ou entre 2 et n pour le codage HDBn.\n");
        scanf("%i",&choix_n);
        }while(choix_n<=0);
        if(choix_n==1){
            printf("Vous avez choisi le codage binaire.\n");
            codage_binaire(message,&taille_message);
            decodage_binaire(message,taille_message);
        }
        else{
            taille_message=Codage_HDBn(message,choix_n);
            printf("Passage au decodage : \n");
            decodage_HDBn(message,choix_n,taille_message);
        }
    }
    
   
    return 0;
}