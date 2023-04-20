#include "../lib/gold.h"

/*Fonction qui permet d'obtenir le code Gold*/
void codeur_gold(int n,int resultat1[(int)pow(2,n)-1],int resultat2[(int)pow(2,n)-1]){
    int gold[(int)pow(2,n)-1];
    printf("\tDEMARRAGE DU CODEUR GOLD\n");
    printf("1er code a longueur maximale : \n");
    for(int i=0;i<(int)pow(2,n)-1;i++){ //J'affiche le 1er code L.M
        printf("%i ",resultat1[i]);
    }
    printf("\n2eme code a longueur maximale : \n");
    for(int i=0;i<(int)pow(2,n)-1;i++){ //Ensuite j'affiche le 2ème code L.M
        printf("%i ",resultat2[i]);
    }
    printf("\nCode final :\n");
    for(int i=0;i<(int)pow(2,n)-1;i++){ //Enfin j'effectue le XOR entre le 1er et le 2eme code L.M et je l'affiche
        gold[i]=(resultat1[i]+resultat2[i])%2;
        printf("%i ",gold[i]);
    }
    printf("\n\t FIN DU CODEUR GOLD\n");
}