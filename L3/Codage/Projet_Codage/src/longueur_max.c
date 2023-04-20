#include "../lib/source.h"
#include "../lib/longueur_max.h"
#include <math.h>




/*Fonction qui permet d'obtenir le code à longueur maximal*/
void codeur_longueur_maximal(int n,int resultat[(int)pow(2,n)-1],int polynome[n],int vecteur[n],int nb_elem){
    int i,c,j;
    int bit_XOR=0;
    int longueur_seq=(int)pow(2,n)-1;
    printf("Nombre d'elements dans le polynome = %i\n",nb_elem);
    printf("\tDEMARRAGE DU CODEUR A LONGUEUR MAXIMALE\n");
    printf("COMBINAISON DES REGISTRES\n");//J'affiche chaque registre ainsi que le bit XOR pour voir le déroulement
    printf("registre 1 -> ");
        for(int v=0;v<n;v++){
            resultat[0]=vecteur[v];
            printf("%i ",resultat[0]);
        }
        printf("\n");
    for(i=1;i<longueur_seq;i++){
        for(c=0;c<nb_elem;c++){//Je calcule ici le bit_XOR en regardant dans le tableau de polynomes
            if(c==0)
            {
                bit_XOR=vecteur[polynome[c]-1];
            }
            else{
                bit_XOR=(bit_XOR+vecteur[polynome[c]-1])%2;
            }
        }
        printf("bit_XOR = %i\n",bit_XOR);
        for(j=n-1;j>0;j--){ //Décaler tous les nombres vers la droite
            if(j==n-1)
                resultat[i]=vecteur[j];
            vecteur[j]=vecteur[j-1]; 
        }
        vecteur[0]=bit_XOR;
        printf("registre %i -> ",i+1);
        for(int v=0;v<n;v++){ //J'affiche le registre
            printf("%i ",vecteur[v]);
        }
        printf("\n");
    }
    printf("CODE FINAL\n");
    for(int k=0;k<longueur_seq;k++){ //J'affiche le code a L.M obtenu
        printf("%i",resultat[k]);
    }
    printf("\n");
    printf("\n\t FIN DU CODEUR A LONGUEUR MAXIMALE\n");
}