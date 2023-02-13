

#include <stdio.h>
#include <math.h>
#include "../lib/source.h"

/*Fonction qui permet de faire le decodage arithmetique*/
int decodage_arithmetique(double borne_finale[2],hash tab_symbole[N],double message_compresse,int taille_message,int nb_symboles){
    int i;
    double tempo;
    char message[N];
    printf("taille=%i\n",taille_message);
    for(i=0;i<taille_message;i++){

        for(int j=0;j<nb_symboles;j++){
            if (message_compresse >= tab_symbole[j].BI && message_compresse < tab_symbole[j].BS){
                printf("Valeur du message compresse compris dans l'intervalle [%lf,%lf] de la lettre %c\n",tab_symbole[j].BI,tab_symbole[j].BS,tab_symbole[j].symbole);
                *(message+i)=tab_symbole[j].symbole;
                tempo=(double)tab_symbole[j].cpt/taille_message;
                message_compresse= (message_compresse- tab_symbole[j].BI) /tempo;
                printf("Apres calcul, nouvelle valeur du message_compresse : %lf\n",message_compresse);
                break;
            }
        }
    }
    printf("Mot decode : ");
    for(i=0;i<taille_message;i++){
        printf("%c",*(message+i));
    }
    printf("\nFIN DU DECODAGE");
return 0;

}