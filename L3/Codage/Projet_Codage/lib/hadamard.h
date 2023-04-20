#ifndef HADAMARD_H
#define HADAMARD_H
int nb_utilisateurs=0;
/*Cette fonction retourne la puissance de la matrice */
extern int puissance_matrice();
/*Fonction qui retourne la longueur de la matrice*/
extern int longueur_matrice();
/*Cette fonction génère une matrice de façon récursif*/
extern void generation_matrice(int matrice[longueur_matrice()][longueur_matrice()],int taille_matrice);
/*Fonction qui permet d'afficher la matrice en paramètre*/
extern void affiche_matrice(int matrice[longueur_matrice()][longueur_matrice()]);
/*Fonction qui permet de générer une séquence pour un utilisateur*/
extern void generation_sequence(int matrice[longueur_matrice()][longueur_matrice()],int taille_message,int tab_sequence_etal[nb_utilisateurs][taille_message*longueur_matrice()],int element,int num_sequence,int positionX,int positionCourant);
/*Grande fonction qui permet de faire la séquence d'étalonnement*/
extern void initialisation_sequences(int matrice[longueur_matrice()][longueur_matrice()]);
#endif