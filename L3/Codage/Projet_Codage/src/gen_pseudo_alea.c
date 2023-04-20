#include "../lib/longueur_max.h"
#include "../lib/gold.h"
#include "../lib/jpl.h"
#include "../lib/source.h"

/*Calcule du pgcd (plus grand diviseur commun). utiliser pour savoir si les deux nombres passé en paramètre sont premier entre eux si la 
fonction renvoie 1 ou -1*/
int pgcd(int a,int b){
	int res=0;
	int i=0;
	for(i=1; i <=a && i <=b; ++i)
    {
        if(a%i==0 && b%i==0)
            res = i;
    }
	return res;
}

/*Fonction qui permet de lire dans un fichier contenant tous les polynomes en rapport avec sa longueur n et tous ces polynomes sont stockés
dans la matrice en paramètre pour que par la suite l'utilisateur choisisse un de ces polynomes*/
int remplir_matrice_polynome(int matrice[N][N],int n)
{
	FILE * fichier=NULL;
	int ligne=1;
    char a;
    char mot[TAILLE_MOT];
    int cpt=0;
	int h=0;
	int t=1;
    fichier= fopen("lib/polynome.txt","r");
    if(fichier ==NULL){
        printf("Ouverture du fichier polynome.txt a echoué");
    }
    else
    {
		rewind(fichier);
		while(!feof(fichier) && ligne<n){
			fscanf(fichier,"%c",&a);
			if(a=='\n'){
				ligne+=1;
			}
			else
				if(ligne+1==n){
					mot[cpt]=a;
					cpt++;
				}
		}
    }
	//mot[cpt-1]='\0';
	cpt=0;
	for(int i=0; mot[i]!='\0';i++){
		if(mot[i]=='|'){
			matrice[cpt][h+1]=n+1;
			cpt++;
			h=0;
			t=1;
		}else{
			if(mot[i]==','){
				t=1;
				h++;
			}
			else
				if(mot[i]>='0' && mot[i]<='9'){					
					if(t==1){
						matrice[cpt][h]=mot[i] -'0';
						t=10;
					}
					else{
						matrice[cpt][h]=matrice[cpt][h]*t + mot[i]-'0';
						t*=10;
					}
				}
		}
		
	}
	h++;
	matrice[cpt][h]=n+1;
	cpt++;
	for(int i=0;i<cpt;i++){
		printf("polynome %i : [",i+1);
		for(int j=0;matrice[i][j]!=n+1;j++){
			printf("%i",matrice[i][j]);
			if(matrice[i][j+1]!=n+1){
				printf(",");
			}
		}
		printf("]\n");

	}

    fclose(fichier);
	return cpt;
}

/*Fonction qui demande à l'utilisateur le nombre d'étage qu'il souhaite*/
int saisie_nb_etages()
{
	int n=0;
	int i;
	booleen isCorrect=VRAI;
	char message[N];
		do{
		isCorrect=VRAI;
		printf("\nCombien voulez-vous d'etages ? (max = 34): ");
		scanf("%s",message);
		for(i=0;message[i]!='\0';i++)
			if(!isdigit(message[i]))
			{
				isCorrect=FAUX;
				break;
			}
		n=atoi(message);
	}while(isCorrect==FAUX || n<2 ||n>34); //Petite étape de vérification pour voir si le nombre d'étage est bien un entier
	n=atoi(message);
	printf("\nLe nombre d'etages est egal a %i\n",n);
	return n;
}

/*Fonction qui demande à l'utilisateur le vecteur qu'il souhaite*/
void saisie_vecteur(int n,int vecteur[n]){
	int taille_vecteur=0;
	int i;
	booleen isCorrect=VRAI;
	char message[N];
		do{
			isCorrect=VRAI;
			taille_vecteur=0;
			printf("\nQuel vecteur voulez-vous(suite de nombre binaire de longueur %i) : ",n);
			scanf("%s",message);
			for(i=0;message[i]!='\0';i++){
				if(!isdigit(message[i]) || message[i]>'1' || message[i]<'0')
				{
					isCorrect=FAUX;
					break;
				}else taille_vecteur++;	
				if(message[i]=='1')
					vecteur[i]=1;
				if(message[i]=='0')
					vecteur[i]=0;

			}
		}while(isCorrect==FAUX || taille_vecteur!=n); //Petite étape de vérification pour voir si le vecteur est bien une suite de nombre binaire
		printf("\nLe vecteur est : ");
		for(int j=0; j<taille_vecteur;j++) //Affichage du vecteur
			printf("%i",vecteur[j]);
	
	}

/*Fonction qui demande à l'utilisateur le polynome qu'il souhaite*/
int saisie_polynome(int n,int *polynome){

	int choix_polynome;
	int nb_elem; //nb_elem dans le polynome
	int i=0;
	booleen isCorrect=VRAI;
	char message[N];
	printf("\nVoici tous les polynomes disponibles pour n=%i : \n",n);
	int matrice_polynome[N][N];
	int max=remplir_matrice_polynome(matrice_polynome,n); //J'affiche tous les polynomes disponible pour n nombre d'étage
	do{
		isCorrect=VRAI;
		printf("Quelle polynome choisissez-vous (choisissez le numero)? : ");
		scanf("%s",message);
		for(int i=0;message[i]!='\0';i++)
			if(!isdigit(message[i]))
			{
				isCorrect=FAUX;
				break;
			}
		if(isCorrect==VRAI)
			choix_polynome=atoi(message);
	}while(choix_polynome<1 || choix_polynome>max || isCorrect==FAUX); //Petite étape de vérification pour voir si le choix est bien un nombre
	printf("Vous avez choisi le polynome n%i\n",choix_polynome);
	for(i=0;matrice_polynome[choix_polynome-1][i]!=n+1;i++){ //Affectation du polynome
		*(polynome+i)=matrice_polynome[choix_polynome-1][i];
	}
	return nb_elem=i;
}


int main(){

	//Je commence par demander à l'utilisateur de faire le premier code à longueur maximal
	int n=saisie_nb_etages();
	int L1=(int)pow(2,n)-1;
	int vecteur[n];
	saisie_vecteur(n,vecteur);
	int polynome[n];
	int nb_elem=saisie_polynome(n,polynome);
	int resultat1[L1];
	printf("Soit la longueur sequentielle L1 est egale à %i\n",L1);
	//utilisation du codeur à longueur maximal
	codeur_longueur_maximal(n,resultat1,polynome,vecteur,nb_elem); //la fonction qui est le codeur à longueur maximal
	int choix;
	printf("\nQuel type de codeur voulez-vous ?");
	printf("\n1 : Codeur Gold");
	printf("\n2 : Codeur JPL ");
	printf("\n3 : Quittez ");
	do{printf("\nPour choisir entre les trois,Taper 1, 2 ou 3 : ");
		scanf("%i",&choix);
	}while(choix<1 || choix>3);
	if(choix==1){
		//Utilisation du codeur Gold
		printf("Pour utiliser le codeur Gold il faudra effectuer un autre code a longueur maximal avec le meme nombre d'étage n.\n");
		saisie_vecteur(n,vecteur);
		nb_elem=saisie_polynome(n,polynome);
		int resultat2[L1];
		codeur_longueur_maximal(n,resultat2,polynome,vecteur,nb_elem);	//le deuxième code à longueur maximal
		codeur_gold(n,resultat1,resultat2); //la fonction qui est le codeur Gold
	}
	else if(choix==2){
	//Utilisation du codeur JPL 
		printf("Pour utiliser le codeur JPL il faudra effectuer deux autres codes a longueur maximal et que n,m et p soit premier entre eux\n");
		int m,p;
		//2eme code a longueur maximal
		printf("Procedure pour le deuxieme code L2 a longueur maximal : \n ");
		m=saisie_nb_etages();
		int L2=(int)pow(2,m)-1;
		printf("Soit la longueur sequentielle est egale à %i\n",L2);
		if(pgcd(L1,L2)!=1 && pgcd(L1,L2) !=-1)
		do{
			printf("La longueur sequentielle L2=%i est pas premier avec L1=%i veuillez refaire la procedure pour m.\n",L2,L1);
			m=saisie_nb_etages();
			L2=(int)pow(2,m)-1;
		}while(pgcd(L1,L2)!=1 && pgcd(L1,L2) !=-1); //Petite vérification pour savoir si L1 est premier avec L2
		saisie_vecteur(m,vecteur);
		nb_elem=saisie_polynome(m,polynome);
		int resultatJPL2[L2];
		codeur_longueur_maximal(m,resultatJPL2,polynome,vecteur,nb_elem);

		//3eme code a longueur maximal
		printf("Procedure pour le troisieme et dernier code a longueur maximal : \n ");
		p=saisie_nb_etages();
		int L3=(int)pow(2,p)-1;
		printf("Soit la longueur sequentielle L3 est egale à %i\n",L3);
		if(pgcd(L1,L3)!=1 && pgcd(L1,L3) !=-1 && pgcd(L2,L3)!=1 && pgcd(L2,L3) !=-1 )
		do{
			printf("La longueur sequentielle L3=%i est pas premier avec les deux autres longueurs L1=%i L2=%i  veuillez refaire la procedure pour p.\n",L3,L1,L2);
			p=saisie_nb_etages();
			L3=(int)pow(2,p)-1;
		}while(pgcd(L1,L3)!=1 && pgcd(L1,L3) !=-1 && pgcd(L2,L3)!=1 && pgcd(L2,L3) !=-1); //Petite vérification pour savoir si L3 est premier avec L2 et L1
		saisie_vecteur(p,vecteur);
		nb_elem=saisie_polynome(p,polynome);
		int resultatJPL3[L3];
		codeur_longueur_maximal(p,resultatJPL3,polynome,vecteur,nb_elem);

		codeur_jpl(n,m,p,L1,L2,L3,resultat1,resultatJPL2,resultatJPL3);//La fonction qui est le codeur JPL
	}
	else printf("A bientot ! \n");
	return 0;
}