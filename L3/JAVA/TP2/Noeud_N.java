
import java.util.ArrayList;
import java.util.Collections;

class Noeud_N extends Noeud{

    Noeud_N pere;
    ArrayList<Noeud_N> enfant;
/**
 * Constructeur de la classe Noeud_N
 * @param valeur valeur à stocker dans le noeud
 * @param pere référence vers le noeud père
 */
    public Noeud_N(Object valeur, Noeud_N pere){
        super(valeur, pere);
        this.enfant = new ArrayList<Noeud_N>();
    }


/**
 * Récupère la liste des fils
 * @return la liste des fils de Noeud_N
 */
    public ArrayList<Noeud_N> getEnfant(){
        return enfant;
    }

/**
 * Ajoute un fils à Noeud_N
 * @param n Noeud_N à ajouter en tant que fils
 */
    public void addEnfant(Object n){
        this.enfant.add(new Noeud_N (n,this));
    }


/**
 * Enlève un noeud de Noeud_N
 * @param noeud Noeud_N à enlever
 */
    public void enlever(Noeud_N noeud){
        if(this.rechercher(noeud)){
            for(Noeud_N n:noeud.enfant){  
                noeud.pere.addEnfant(n);
            }
            noeud.pere.enfant.remove(noeud);
        } 
    }
/**
 * Recherche un noeud dans les fils de Noeud_N
 * @param noeud Noeud_N à rechercher
 * @return vrai si le noeud est trouvé, faux sinon
 */
     public boolean rechercher(Object val){
        for(Noeud_N n:this.enfant){
            if(n.compareTo(val)== 0){
                return true;
            }
        }
            for(Noeud_N n:this.enfant)
                n.rechercher(val);
        return false;
    }

/**
 * Hauteur de l'arbre
 * @return hauteur de l'arbre
 */
    public int hauteur(){
        return(this.hauteurBis(0));
    }

    // hauteur de l'arbre en récursif
    private int hauteurBis(int hauteur){
        ArrayList<Integer> liste_max= new ArrayList<>();
        if(this.enfant.size()== 0){
            return hauteur;
        }
        for(Noeud_N n:this.enfant){
            liste_max.add( n.hauteurBis(hauteur+1));
        }
        return(Collections.max(liste_max));
    }


  public void afficher(){
    System.out.println(this.valeur);
  }

    protected void parcours_prefixe(){
        this.afficher();
        for(Noeud_N n:this.enfant){
            n.parcours_prefixe();
        }
    }

    protected void parcours_postfixe(){
        for(Noeud_N n:this.enfant){
            n.parcours_postfixe();
        }
        this.afficher();
    }


}