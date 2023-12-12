package fr.soprasteria.tdd.tp;

public class Joueur {
	private Case case1;
	
	public Joueur(Case caseJoueur) {
		this.case1 = caseJoueur;	
	}
	
	public Case getCase() {
		return case1;
	}

	public void setCase(Case case1) {
		this.case1 = case1;
	}

	@Override
	public String toString() {
		return "Joueur [case1=" + case1 + "]";
	}
}
