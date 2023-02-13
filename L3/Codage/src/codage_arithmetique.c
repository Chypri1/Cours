
#include <stdio.h>
#include <math.h>

#include "../lib/source.h"

 /* listage avec un case des lettres 
    puis reconstitution en probabilité 
    passage des probas en binaire 
    renvoie du message    
*/

/*Fonction qui permet de faire le codage arithmetique*/
int codage_arithmetique(double borne_finale[2], hash tab_symbole[N],int * nb_symboles){ 
    char message_arithmetique[N];
    int i,index,cpt=0,nb_let ;
    double tempo;
    booleen estDeja=FAUX; //si la lettre est déjà dans le tableau sans_occu
    printf("Saisir un message pour arithmetique (Appuyez sur entrée pour finir votre message!): \n");
    scanf("%s",message_arithmetique);
    printf("Votre message : %s\n",message_arithmetique);

    for(int k=0;message_arithmetique[k]!='\0';k++){
        tab_symbole[k].symbole='\t';  //Je met le symbole \t jusqu'a k fois pour pouvoir comparer avec le message et par conséquent prendre chacun des symboles sans occurences
    }
    for(nb_let=0;message_arithmetique[nb_let]!='\0';nb_let++){
        estDeja=FAUX;
        //Je vérifie si le symbole est compris dans le tableau de symbole 
        for(int j=0;message_arithmetique[j]!='\0';j++){
            if(message_arithmetique[nb_let]==tab_symbole[j].symbole){ //si il est compris je place le booleen estDeja à vrai
                estDeja=VRAI;
                break;
            }
        }
        //si le symbole n'était pas compris dans le tableau de symbole je le met dans le tableau
        if(estDeja==FAUX){
            tab_symbole[cpt].symbole=message_arithmetique[nb_let];
            tab_symbole[cpt].cpt=1;
            cpt++;
        }
        else{ //sinon j'incrémente le cpt d'occurence de ce symbole
            for(index=0;tab_symbole[index].symbole!=message_arithmetique[nb_let];index++);
            tab_symbole[index].cpt++;
        }
    }
    *(nb_symboles)=cpt; //nombre
    
    //Affichage du nombre d'occurence de chaque lettre ainsi que leurs intervalles
    for(i=0;i<cpt;i++){
        if(i==0){
            tab_symbole[i].BI=0;
            tab_symbole[i].BS=(double)tab_symbole[i].cpt/nb_let;
        }
        else{
            tab_symbole[i].BI=tab_symbole[i-1].BS;
            tab_symbole[i].BS=tab_symbole[i-1].BS+(double)tab_symbole[i].cpt/nb_let;
        }
        printf(" nb_occu pour %c: %i  intervalle=[%lf,%lf]\n",tab_symbole[i].symbole,tab_symbole[i].cpt,tab_symbole[i].BI,tab_symbole[i].BS);
    }

    printf("\n\n");

    //Compression du message
    for (i=0;message_arithmetique[i]!='\0';i++){

        // valeur temporaire pour pouvoir calculer borne_finale[0] avec l'ancien borne_finale[1]  
        tempo=borne_finale[1];
        for(index=0;tab_symbole[index].symbole!=message_arithmetique[i];index++);
        //                 borne inf             borne sup - borne inf =proba de la suite de lettre            borne sup = proba d'une lettre  
        borne_finale[1] = borne_finale[0] + (tempo-borne_finale[0]) *tab_symbole[index].BS;
    
        borne_finale[0] = borne_finale[0] + (tempo-borne_finale[0]) *tab_symbole[index].BI;
        printf("borne inf : %lf  borne sup : %lf \n",borne_finale[0],borne_finale[1]);
    }
    printf("Le mot compresse est donc compris entre les bornes %lf et %lf\n",borne_finale[0],borne_finale[1]);
    printf("\n");
    return i;
}