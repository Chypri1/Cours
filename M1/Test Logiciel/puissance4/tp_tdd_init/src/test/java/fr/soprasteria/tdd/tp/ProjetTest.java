package fr.soprasteria.tdd.tp;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class ProjetTest {
	
	Jeu jeu;
	
	@BeforeEach
	void setup() {
		this.jeu = new Jeu();
	}
	
	@Test
	void testVide() {
		
		
	}
	
	@Test
	void testGrilleVide() {
		assertTrue(jeu.estVide());
	}
	
	@Test
	void testAjoutPion() {
		Joueur joueur1 = jeu.getListeJoueur().get(0);
		System.out.println(joueur1);
		jeu.ajoutPion(3, joueur1);
		assertEquals(jeu.getGrille()[0][3],Case.JAUNE);
	}

}
