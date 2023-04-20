#include "../lib/jpl.h"

/*La fonction qui permet d'obtenir le code JPL*/
void codeur_jpl(int n,int m,int p,int L1,int L2,int L3,int resultat1[L1],int resultatJPL2[L2],int resultatJPL3[L3]){
    int i;
    int L=L1*L2*L3;
    int jpl[L];
    int cpt1=0,cpt2=0;
    printf("\tDEMARRAGE DU CODEUR JPL\n");
    printf("Longueur L=L1.L2.L3 = %i\n",L);
    //Je fais d'abord le XOR entre le 1er code L.M et le 2eme code L.M
    for(i=0;i<L2*L1;i++){
        jpl[i]=(resultat1[cpt1]+resultatJPL2[cpt2])%2;
        cpt1++;
        cpt2++;
        if(cpt1==L1)
            cpt1=0;
        if(cpt2==L2)
            cpt2=0;    
    }
    cpt1=0;
    cpt2=0;
    //Puis je fais le XOR entre le résultat d'avant et le 3eme code L.M
    for(i=0;i<L;i++){
        jpl[i]=(jpl[cpt1]+resultatJPL3[cpt2])%2;
        cpt1++;
        cpt2++;
        if(cpt1==(L2*L1)-1)
            cpt1=0;
        if(cpt2==L3)
            cpt2=0;
    }
    //Enfin j'affiche le résultat    
    for(i=0;i<L;i++){
        printf("%i",jpl[i]);
        if(i%15==0) //par paquet de 15 pour que ce soit plus lisible
            if(i==0)
                printf("\n");
    }
    printf("\n\t FIN DU CODEUR JPL\n");

}



