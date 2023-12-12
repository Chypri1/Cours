package fr.soprasteria.tdd.tp;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Jeu {

	private Case grille[][];
	private List<Joueur> listeJoueur ;
	private int tour;
	
	// constructeurs
	
	public Jeu(Case[][] grille) {
		this.grille = grille;
		this.listeJoueur = new ArrayList<Joueur>();
		listeJoueur.add(new Joueur(Case.JAUNE));
		listeJoueur.add(new Joueur(Case.ROUGE));
		this.tour = 1;
	}
	
	public Jeu() {
		this.grille = new Case[6][7];
		this.listeJoueur = new ArrayList<Joueur>();
		listeJoueur.add(new Joueur(Case.JAUNE));
		listeJoueur.add(new Joueur(Case.ROUGE));
		this.tour = 1;
	}
	
	// getter et setter 

	public Case[][] getGrille() {
		return grille;
	}
	
	public List<Joueur> getListeJoueur() {
		return listeJoueur;
	}

	public void setListeJoueur(List<Joueur> listeJoueur) {
		this.listeJoueur = listeJoueur;
	}

	public int getTour() {
		return tour;
	}

	public void setTour(int tour) {
		this.tour = tour;
	}

	public void setGrille(Case[][] grille) {
		this.grille = grille;
	}
	
	
	// méthode d'instance  
	
	public boolean estVide() {
		return true; // véifier que toutes les cases sont Case.VIDE
	}

	public void ajoutPion(int colonne, Joueur joueur) {
		for(int ligne = 0; ligne<6; ligne++) {
			if(grille[ligne][colonne] == null) {
				grille[ligne][colonne] = joueur.getCase();
			}
		}
		tour++;
	}
	
	private boolean estRemplie() {
		for (int ligne = 0;ligne<6;ligne++) {
			for(int colonne = 0; colonne<7;colonne++) {
				if(grille[ligne][colonne] == Case.VIDE) {
					return false;
				}
			}
		}
			
		return true;
	}
	
	public void jouer()
	{
		
		while ( this.estRemplie()) {
			Scanner sc = new Scanner(System.in);
			int colonne = sc.nextInt();
			int numeroJoueur = (this.tour)%2;
			Joueur joueur = this.getListeJoueur().get(numeroJoueur);
			ajoutPion(colonne, joueur);
			if(gagnant(joueur)) {
				break;
			}
		}
	}

    
	private boolean gagnant(Joueur joueur) {
        // Vérifier les lignes
    	Case couleur = joueur.getCase();
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (grille[i][j] == couleur &&
                    grille[i][j + 1] == couleur &&
                    grille[i][j + 2] == couleur &&
                    grille[i][j + 3] == couleur) {
                    return true;
                }
            }
        }

        // Vérifier les colonnes
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                if (grille[i][j] == couleur &&
                    grille[i + 1][j] == couleur &&
                    grille[i + 2][j] == couleur &&
                    grille[i + 3][j] == couleur) {
                    return true;
                }
            }
        }

        // Vérifier les diagonales (\)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (grille[i][j] == couleur &&
                    grille[i + 1][j + 1] == couleur &&
                    grille[i + 2][j + 2] == couleur &&
                    grille[i + 3][j + 3] == couleur) {
                    return true;
                }
            }
        }

        // Vérifier les diagonales (/)
        for (int i = 0; i < 3; i++) {
            for (int j = 3; j < 7; j++) {
                if (grille[i][j] == couleur &&
                    grille[i + 1][j - 1] == couleur &&
                    grille[i + 2][j - 2] == couleur &&
                    grille[i + 3][j - 3] == couleur) {
                    return true;
                }
            }
        }

        return false;
    }
}
