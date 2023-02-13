public class TestArbre_binaire {
public static void main(String[] toto){
    Noeud_ab noeud=new Noeud_ab(1,null,null,null);
    System.out.println("Affichage Préfixe de l'arbre :");
    noeud.afficher();
    System.out.println("Hauteur = "+noeud.hauteur());        
    System.out.println("Ajout de l'objet 2 dans l'arbre :");
    noeud.ajout(2);
    System.out.println("Ajout de l'objet 3  dans l'arbre :");
    noeud.ajout(3);
    System.out.println("Ajout de l'objet 4  dans l'arbre :");
    noeud.ajout(4);
    System.out.println("Ajout de l'objet 10 dans l'arbre :");
    noeud.ajout(10);
    System.out.println("Ajout de l'objet 666  dans l'arbre :");
    noeud.ajout(666);
    System.out.println("Ajout de l'objet 632  dans l'arbre :");
    noeud.ajout(632);
    System.out.println("Ajout de l'objet 3000 dans l'arbre :");
    noeud.ajout(3000);
    System.out.println("Ajout de l'objet 12 dans l'arbre :");
    noeud.ajout(12);
    System.out.println("Affichage Préfixe de l'arbre :");
    noeud.parcours_prefixe();
    System.out.println("Affichage Postfixe de l'arbre :");
    noeud.parcours_postfixe();

    /* 
    System.out.println("Affichage Largeur de l'arbre :");
    noeud.affichageLargeur();
    */
    System.out.println("Hauteur : "+noeud.hauteur());
    System.out.println("Suppression de l'objet 425");
    noeud.enlever(632);
    System.out.println("Affichage Largeur de l'arbre :");
    System.out.println("Le sous_arbre contenant l'objet 666 est-il dans l'arbre ? : "+noeud.chercher(666));
    System.out.println("Le sous_arbre contenant l'objet 777 est-elle une feuille ? : "+noeud.chercher(777));
    //System.out.println("Nombres de noeuds dans l'arbre : "+noeud.getNbrNoeuds());
}

}
