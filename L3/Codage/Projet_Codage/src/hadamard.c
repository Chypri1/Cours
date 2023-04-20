#include "../lib/source.h"
#include "../lib/hadamard.h"


//Cette fonction retourne la puissance de la matrice 
int puissance_matrice()
{
    int puissance=0;
    for(;nb_utilisateurs>pow(2,puissance);puissance++);
    return puissance;
}
/*Fonction qui retourne la longueur de la matrice*/
int longueur_matrice()
{
    return (int)pow(2,puissance_matrice());
}


//Cette fonction génère la matrice de façon récursif
void generation_matrice(int matrice[longueur_matrice()][longueur_matrice()],int taille_matrice)
{
    if(taille_matrice==0){ //si la matrice est de longueur 1
        matrice[0][0]=1;
    }
    else 
        {
            generation_matrice(matrice,taille_matrice-1); //appel récursif
            int position=(int)pow(2,taille_matrice);
            for(int i=0;i<position;i++) //Ecriture des valeurs de la matrice
            {
                for(int j=0;j<position;j++)
                {
                    if(i>=position/2 && j>=position/2) //Ecriture en bas à droite
                        matrice[i][j]=-matrice[i][j-position/2];
                    else if(i>=position/2) //Ecriture en bas à gauche
                            matrice[i][j]=matrice[i-position/2][j];
                        else if(j>=position/2) //Ecriture en haut à droite
                                matrice[i][j]=matrice[i][j-position/2];
                }
            }

        }
}
/*Fonction qui permet d'afficher la matrice en paramètre*/
void affiche_matrice(int matrice[longueur_matrice()][longueur_matrice()])
{
    printf("\n");
    for(int i=0;i<longueur_matrice();i++){
        for(int j=0;j<longueur_matrice();j++){
            if(j==0)
                printf("[");
            if(matrice[i][j]==1)
            	printf(" %i",matrice[i][j]);
            else printf("%i",matrice[i][j]);
            if(j!=longueur_matrice()-1)
                printf(",");
        }
        printf("]\n");
    }
}
/*Fonction qui permet de générer une séquence pour un utilisateur*/
void generation_sequence(int matrice[longueur_matrice()][longueur_matrice()],int taille_message,int tab_sequence_etal[nb_utilisateurs][taille_message*longueur_matrice()],int element,int num_sequence,int positionX,int positionCourant){
	printf("\n");
	int position=positionCourant;
	for(int j=0;j<longueur_matrice();j++){
		if(element==0)
			tab_sequence_etal[positionX][position]=matrice[num_sequence][j]*(-1);
		else tab_sequence_etal[positionX][position]=matrice[num_sequence][j];
		position++;
	}
}
/*Grande fonction qui permet de faire la séquence d'étalonnement*/
void initialisation_sequences(int matrice[longueur_matrice()][longueur_matrice()])
{
    int i=0;
    int j=0;
    int num_sequence[nb_utilisateurs];
    int taille_message=0;
    booleen correct=VRAI;
    do
    {
        printf("Saisissez une taille de message : ");
        scanf("%i",&taille_message);
    }while(taille_message<1); //Petite vérification pour que la taille des messages soient supérieur à 1
    char message_binaire[taille_message];
    int tab_message[nb_utilisateurs][taille_message];    
    int code_etalonne[taille_message*longueur_matrice()];
    for(int l=0;l<taille_message*longueur_matrice();l++)
        code_etalonne[l]=0;
    for(;i<nb_utilisateurs;i++)
    {
        do
        {
            printf("Utilisateur %i Quelle sequence de la matrice voulez-vous ?(entre 1 et %i):  ",i+1,longueur_matrice());
            scanf("%i",&num_sequence[i]);
        }while(num_sequence[i]<1 || num_sequence[i]>longueur_matrice()); //Je demande à l'utilisateur une séquence de la matrice
        printf("\n");
        do
        {
            correct=VRAI;
            printf("Veuillez ecrire votre message binaire de taille %i :\n",taille_message);
            scanf("%s",message_binaire);
            printf("\n");
            for(j=0;message_binaire[j]!='\0';j++)
            {
                if(message_binaire[j]!='0' && message_binaire[j]!='1')
                    correct=FAUX;
                tab_message[i][j] = message_binaire[j] -'0';
            }
        }while(strlen(message_binaire)!=taille_message || correct==FAUX); //Petite vérification pour que le message soit bien une suite de nombre binaire
        printf("\n");
        

    }
    int tab_sequence_etal[nb_utilisateurs][longueur_matrice()*taille_message];
    int positionCourant=0;
    for(i=0;i<nb_utilisateurs;i++)//Je génère une séquence pour chaque utilisateur
    {
        for(j=0;j<taille_message;j++)
        {
        	generation_sequence(matrice,taille_message,tab_sequence_etal,tab_message[i][j],num_sequence[i]-1,i,positionCourant);
        	positionCourant+=longueur_matrice();
        }
        positionCourant=0;
    }
    printf("Codage du message code avec les sequences choisis :\n");
    for(i=0;i<nb_utilisateurs;i++)
    {
    	printf("utilisateur %i :",i+1);
        for(j=0;j<taille_message*longueur_matrice();j++)
        {
            if(tab_sequence_etal[i][j]==1)
        	    printf(" %i",tab_sequence_etal[i][j]);
            else 
                printf("%i",tab_sequence_etal[i][j]);
            code_etalonne[j]+=tab_sequence_etal[i][j];
        }
        printf("\n");
    }
    printf("Code apres etalonnement : \n");
    for(i=0;i<taille_message*longueur_matrice();i++) //J'effectue ensuite la séquence d'étalonnement avec toutes les séquences
    {
        printf("%i",code_etalonne[i]);
        if(i!=taille_message*longueur_matrice()-1)
            printf(",");
    }
}


int main()
{
    do{
    printf("Bonjour, Veuillez saisir le nombre d'utilisateurs : ");
    scanf("%i",&nb_utilisateurs);
    }while(nb_utilisateurs<=0);
    printf("taille matrice =%i\n",puissance_matrice());
    printf("Generation de la matrice Hadamard en fonction du nb d'utilisateur de longueur %i\n",longueur_matrice());
    int matrice[longueur_matrice()][longueur_matrice()];
    generation_matrice(matrice,puissance_matrice());
    affiche_matrice(matrice);
    initialisation_sequences(matrice);
    return 0;
}
