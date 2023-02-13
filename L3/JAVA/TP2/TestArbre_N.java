public class TestArbre_N {
    public static void main(String[] toto){
        Noeud_N noeud=new Noeud_N(1,null);
        System.out.println("Affichage Préfixe de l'arbre :");
        noeud.afficher();
        System.out.println("Hauteur = "+noeud.hauteur());        
        System.out.println("Ajout de l'objet 2 dans l'arbre :");
        noeud.addEnfant(2);
        System.out.println("Ajout de l'objet 3 dans le sous_arbre contenant l'objet 2 :");
        noeud.getEnfant().get(2).addEnfant(3);
        System.out.println("Ajout de l'objet 4 dans le sous_arbre contenant l'objet 2 :");
        noeud.getEnfant().get(1).addEnfant(4);
        System.out.println("Ajout de l'objet 10 dans l'arbre :");
        noeud.addEnfant(10);
        System.out.println("Ajout de l'objet 666 dans le sous_arbre contenant l'objet 1 qui sera dans le sous_arbre contenant l'objet 1 :");
        noeud.getEnfant().get(1).getEnfant().get(1).addEnfant(666);
        System.out.println("Ajout de l'objet 632 dans le sous_arbre contenant l'objet 15 :");
        noeud.getEnfant().get(15).addEnfant(632);
        System.out.println("Ajout de l'objet 3000 dans l'arbre :");
        noeud.addEnfant(3000);
        System.out.println("Ajout de l'objet 12 dans le sous_arbre contenant l'objet 5 :");
        noeud.getEnfant().get(5).addEnfant(12);
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
        noeud.enlever(noeud.getEnfant().get(4));
        System.out.println("Affichage Largeur de l'arbre :");
        System.out.println("Le sous_arbre contenant l'objet 666 est-il dans l'arbre ? : "+noeud.rechercher(666));
        System.out.println("Le sous_arbre contenant l'objet 777 est-elle une feuille ? : "+noeud.rechercher(777));
        //System.out.println("Nombres de noeuds dans l'arbre : "+noeud.getNbrNoeuds());
    }
}
